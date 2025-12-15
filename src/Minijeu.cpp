#include "MiniJeu.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

// ===== COIN =====
Coin::Coin(int px, int py) : x(px), y(py), collected(false) {}

// ===== MINI PLAYER =====
MiniPlayer::MiniPlayer() : x(200), y(220), size(8), speed(3) {}

void MiniPlayer::move(const Uint8* keys, int screenW, int screenH) {
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) x -= speed;
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) x += speed;
    if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) y -= speed;
    if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) y += speed;
    
    if (x < 0) x = 0;
    if (y < 20) y = 20;
    if (x > screenW - size) x = screenW - size;
    if (y > screenH - size) y = screenH - size;
}

void MiniPlayer::draw(SDL_Renderer* renderer) {
    SDL_Rect rect = {x, y, size, size};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
}

// ===== MINI JEU =====
MiniJeu::MiniJeu() 
    : m_score(0), m_timeLeft(30), m_finished(false), m_running(true)
{
    srand(time(NULL));
    m_lastSecond = SDL_GetTicks();
    m_lastCoinSpawn = SDL_GetTicks();
    
    // Spawn initial
    for (int i = 0; i < 5; i++) {
        spawnCoin();
    }
}

MiniJeu::~MiniJeu() {}

void MiniJeu::spawnCoin() {
    m_coins.push_back(Coin(
        rand() % (SCREEN_W - 10), 
        rand() % (SCREEN_H - 60) + 20
    ));
}

void MiniJeu::checkCollisions() {
    for (auto& coin : m_coins) {
        if (!coin.collected) {
            if (m_player.x < coin.x + 5 && 
                m_player.x + m_player.size > coin.x &&
                m_player.y < coin.y + 5 && 
                m_player.y + m_player.size > coin.y) {
                coin.collected = true;
                m_score++;
            }
        }
    }
}

bool MiniJeu::update(SDL_Renderer* renderer, SDL_Event& event) {
    if (m_finished) {
        // Attendre ESC ou RETURN pour fermer
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE || 
                event.key.keysym.sym == SDLK_RETURN) {
                return false; // Signale qu'on veut quitter
            }
        }
        return true;
    }
    
    if (!m_running || m_timeLeft <= 0) {
        m_finished = true;
        return true;
    }
    
    // Input
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    m_player.move(keys, SCREEN_W, SCREEN_H);
    
    // Timer
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - m_lastSecond >= 1000) {
        m_timeLeft--;
        m_lastSecond = currentTime;
    }
    
    // Spawn pièces
    if (currentTime - m_lastCoinSpawn >= 2000) {
        spawnCoin();
        m_lastCoinSpawn = currentTime;
    }
    
    // Collisions
    checkCollisions();
    
    return true;
}

void MiniJeu::drawCoin(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, x+2, y+0);
    SDL_RenderDrawPoint(renderer, x+1, y+1);
    SDL_RenderDrawPoint(renderer, x+2, y+1);
    SDL_RenderDrawPoint(renderer, x+3, y+1);
    SDL_RenderDrawPoint(renderer, x+0, y+2);
    SDL_RenderDrawPoint(renderer, x+1, y+2);
    SDL_RenderDrawPoint(renderer, x+2, y+2);
    SDL_RenderDrawPoint(renderer, x+3, y+2);
    SDL_RenderDrawPoint(renderer, x+4, y+2);
    SDL_RenderDrawPoint(renderer, x+1, y+3);
    SDL_RenderDrawPoint(renderer, x+2, y+3);
    SDL_RenderDrawPoint(renderer, x+3, y+3);
    SDL_RenderDrawPoint(renderer, x+2, y+4);
}

void MiniJeu::drawDigit(SDL_Renderer* renderer, int digit, int x, int y) {
    static const char* digits[10][5] = {
        {"111", "101", "101", "101", "111"}, // 0
        {"010", "110", "010", "010", "111"}, // 1
        {"111", "001", "111", "100", "111"}, // 2
        {"111", "001", "111", "001", "111"}, // 3
        {"101", "101", "111", "001", "001"}, // 4
        {"111", "100", "111", "001", "111"}, // 5
        {"111", "100", "111", "101", "111"}, // 6
        {"111", "001", "001", "001", "001"}, // 7
        {"111", "101", "111", "101", "111"}, // 8
        {"111", "101", "111", "001", "111"}  // 9
    };
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int row = 0; row < 5; row++) {
        for (int col = 0; col < 3; col++) {
            if (digits[digit][row][col] == '1') {
                SDL_RenderDrawPoint(renderer, x + col * 2, y + row * 2);
            }
        }
    }
}

void MiniJeu::drawNumber(SDL_Renderer* renderer, int number, int x, int y) {
    if (number == 0) {
        drawDigit(renderer, 0, x, y);
        return;
    }
    
    int digits[10];
    int count = 0;
    int temp = number;
    
    while (temp > 0) {
        digits[count++] = temp % 10;
        temp /= 10;
    }
    
    for (int i = count - 1; i >= 0; i--) {
        drawDigit(renderer, digits[i], x + (count - 1 - i) * 8, y);
    }
}

void MiniJeu::render(SDL_Renderer* renderer) {
    if (m_finished) {
        drawGameOver(renderer);
        return;
    }
    
    // Fond
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Zone de jeu
    SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
    SDL_Rect playArea = {0, 20, SCREEN_W, SCREEN_H - 20};
    SDL_RenderFillRect(renderer, &playArea);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &playArea);
    
    // Grille
    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
    for (int x = 0; x < SCREEN_W; x += 20) {
        SDL_RenderDrawLine(renderer, x, 20, x, SCREEN_H);
    }
    for (int y = 20; y < SCREEN_H; y += 20) {
        SDL_RenderDrawLine(renderer, 0, y, SCREEN_W, y);
    }
    
    // Pièces
    for (const auto& coin : m_coins) {
        if (!coin.collected) {
            drawCoin(renderer, coin.x, coin.y);
        }
    }
    
    // Joueur
    m_player.draw(renderer);
    
    // HUD
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect hudRect = {0, 0, SCREEN_W, 20};
    SDL_RenderFillRect(renderer, &hudRect);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 0, 19, SCREEN_W, 19);
    
    // Score
    drawNumber(renderer, m_score, 50, 5);
    
    // Temps
    drawNumber(renderer, m_timeLeft, SCREEN_W - 30, 5);
}

void MiniJeu::drawGameOver(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Cadre
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect frame = {50, 150, SCREEN_W - 100, 180};
    SDL_RenderDrawRect(renderer, &frame);
    
    // Score final
    drawNumber(renderer, m_score, SCREEN_W/2 - 20, 250);
    
    // Texte "PRESS ESC"
    SDL_Rect smallRect = {SCREEN_W/2 - 35, 290, 4, 8};
    for (int i = 0; i < 9; i++) {
        SDL_RenderFillRect(renderer, &smallRect);
        smallRect.x += 8;
    }
}