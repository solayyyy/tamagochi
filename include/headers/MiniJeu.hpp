#ifndef MINIJEU_HPP
#define MINIJEU_HPP

#include <SDL.h>
#include <vector>

// Structure pour une pièce
struct Coin {
    int x, y;
    bool collected;
    
    Coin(int px, int py);
};

// Structure pour le joueur du mini-jeu
struct MiniPlayer {
    int x, y;
    int size;
    int speed;
    
    MiniPlayer();
    void move(const Uint8* keys, int screenW, int screenH);
    void draw(SDL_Renderer* renderer);
};

class MiniJeu {
public:
    MiniJeu();
    ~MiniJeu();
    
    // Retourne true si le jeu continue, false si terminé
    bool update(SDL_Renderer* renderer, SDL_Event& event);
    void render(SDL_Renderer* renderer);
    
    // Accesseurs
    int getScore() const { return m_score; }
    bool isFinished() const { return m_finished; }
    
private:
    MiniPlayer m_player;
    std::vector<Coin> m_coins;
    
    int m_score;
    int m_timeLeft;
    bool m_finished;
    bool m_running;
    
    Uint32 m_lastSecond;
    Uint32 m_lastCoinSpawn;
    
    const int SCREEN_W = 400;
    const int SCREEN_H = 480;
    
    // Fonctions utilitaires
    void spawnCoin();
    void checkCollisions();
    void drawCoin(SDL_Renderer* renderer, int x, int y);
    void drawDigit(SDL_Renderer* renderer, int digit, int x, int y);
    void drawNumber(SDL_Renderer* renderer, int number, int x, int y);
    void drawGameOver(SDL_Renderer* renderer);
};

#endif