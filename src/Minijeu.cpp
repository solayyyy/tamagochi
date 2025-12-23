
#include <cstdlib>
#include <ctime>


MiniJeu::MiniJeu() 
    : snakeDirX(1), snakeDirY(0), gameScore(0), 
      isGameOver(false), m_finished(false), lastUpdate(0)
{
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }
    init();
}

MiniJeu::~MiniJeu() {
    // Rien à libérer
}



void MiniJeu::init() {
    snakeBody.clear();
    
    // Serpent de 3 segments au centre
    snakeBody.push_back({GRID_W / 2, GRID_H / 2});
    snakeBody.push_back({GRID_W / 2 - 1, GRID_H / 2});
    snakeBody.push_back({GRID_W / 2 - 2, GRID_H / 2});
    
    snakeDirX = 1;
    snakeDirY = 0;
    gameScore = 0;
    isGameOver = false;
    m_finished = false;
    
    spawnFood();
    lastUpdate = SDL_GetTicks();
}

bool MiniJeu::update(SDL_Renderer* renderer, SDL_Event& event) {
    // Si le jeu est terminé, attendre ESC ou SPACE
    if (isGameOver) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                m_finished = true;
                return false; // Quitter le jeu
            }
            if (event.key.keysym.sym == SDLK_SPACE || 
                event.key.keysym.sym == SDLK_RETURN) {
                init(); // Recommencer
            }
        }
        return true;
    }
    
    // Gestion des entrées
    handleInput(event);
    
    // Mise à jour du serpent
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastUpdate >= UPDATE_DELAY) {
        updateSnake();
        lastUpdate = currentTime;
    }
    
    return true;
}

void MiniJeu::render(SDL_Renderer* renderer) {
    renderGame(renderer);
}



void MiniJeu::spawnFood() {
    food.x = rand() % GRID_W;
    food.y = rand() % GRID_H;
}

void MiniJeu::updateSnake() {
    if (isGameOver) return;
    
    // Nouvelle position de la tête
    SnakePoint newHead;
    newHead.x = snakeBody[0].x + snakeDirX;
    newHead.y = snakeBody[0].y + snakeDirY;
    
    // Vérifier collision avec les murs
    if (newHead.x < 0 || newHead.x >= GRID_W || 
        newHead.y < 0 || newHead.y >= GRID_H) {
        isGameOver = true;
        return;
    }
    
    // Vérifier collision avec le corps
    for (size_t i = 0; i < snakeBody.size(); i++) {
        if (newHead.x == snakeBody[i].x && newHead.y == snakeBody[i].y) {
            isGameOver = true;
            return;
        }
    }
    
    // Ajouter la nouvelle tête
    snakeBody.insert(snakeBody.begin(), newHead);
    
    // Vérifier si on mange la nourriture
    if (newHead.x == food.x && newHead.y == food.y) {
        gameScore++;
        spawnFood();
    } else {
        snakeBody.pop_back();
    }
}

void MiniJeu::handleInput(SDL_Event& event) {
    if (event.type != SDL_KEYDOWN) return;
    
    switch (event.key.keysym.sym) {
        case SDLK_UP:
        case SDLK_z:
        case SDLK_w:
            if (snakeDirY == 0) {
                snakeDirX = 0;
                snakeDirY = -1;
            }
            break;
            
        case SDLK_DOWN:
        case SDLK_s:
            if (snakeDirY == 0) {
                snakeDirX = 0;
                snakeDirY = 1;
            }
            break;
            
        case SDLK_LEFT:
        case SDLK_q:
        case SDLK_a:
            if (snakeDirX == 0) {
                snakeDirX = -1;
                snakeDirY = 0;
            }
            break;
            
        case SDLK_RIGHT:
        case SDLK_d:
            if (snakeDirX == 0) {
                snakeDirX = 1;
                snakeDirY = 0;
            }
            break;
            
        case SDLK_ESCAPE:
            isGameOver = true;
            m_finished = true;
            break;
    }
}

void MiniJeu::renderGame(SDL_Renderer* renderer) {
    // Fond noir
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Grille
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    for (int x = 0; x <= GRID_W; x++) {
        SDL_RenderDrawLine(renderer, x * CELL_SIZE, 0, x * CELL_SIZE, GRID_H * CELL_SIZE);
    }
    for (int y = 0; y <= GRID_H; y++) {
        SDL_RenderDrawLine(renderer, 0, y * CELL_SIZE, GRID_W * CELL_SIZE, y * CELL_SIZE);
    }
    
    // Nourriture (jaune)
    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
    SDL_Rect foodRect = {
        food.x * CELL_SIZE + 2,
        food.y * CELL_SIZE + 2,
        CELL_SIZE - 4,
        CELL_SIZE - 4
    };
    SDL_RenderFillRect(renderer, &foodRect);
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 150, 255);
    SDL_Rect foodCenter = {
        food.x * CELL_SIZE + CELL_SIZE / 3,
        food.y * CELL_SIZE + CELL_SIZE / 3,
        CELL_SIZE / 3,
        CELL_SIZE / 3
    };
    SDL_RenderFillRect(renderer, &foodCenter);
    
    // Serpent
    for (size_t i = 0; i < snakeBody.size(); i++) {
        if (i == 0) {
            SDL_SetRenderDrawColor(renderer, 50, 205, 50, 255); // Tête
        } else {
            SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255); // Corps
        }
        
        SDL_Rect segmentRect = {
            snakeBody[i].x * CELL_SIZE + 1,
            snakeBody[i].y * CELL_SIZE + 1,
            CELL_SIZE - 2,
            CELL_SIZE - 2
        };
        SDL_RenderFillRect(renderer, &segmentRect);
        
        // Yeux sur la tête
        if (i == 0) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_Rect leftEye = {
                snakeBody[0].x * CELL_SIZE + 5,
                snakeBody[0].y * CELL_SIZE + 5,
                3, 3
            };
            SDL_Rect rightEye = {
                snakeBody[0].x * CELL_SIZE + CELL_SIZE - 8,
                snakeBody[0].y * CELL_SIZE + 5,
                3, 3
            };
            SDL_RenderFillRect(renderer, &leftEye);
            SDL_RenderFillRect(renderer, &rightEye);
        }
    }
    
    // Score (points blancs)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < gameScore && i < 30; i++) {
        SDL_Rect dot = {10 + i * 15, 10, 10, 10};
        SDL_RenderFillRect(renderer, &dot);
    }
    
    // Game Over
    if (isGameOver) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
        SDL_Rect overlay = {0, 0, GRID_W * CELL_SIZE, GRID_H * CELL_SIZE};
        SDL_RenderFillRect(renderer, &overlay);
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect gameOverBox = {150, 180, 300, 140};
        SDL_RenderFillRect(renderer, &gameOverBox);
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect innerBox = {155, 185, 290, 130};
        SDL_RenderDrawRect(renderer, &innerBox);
        
        
        
        // Score final
        for (int i = 0; i < gameScore && i < 15; i++) {
            SDL_Rect scoreDot = {220 + i * 12, 260, 8, 8};
            SDL_RenderFillRect(renderer, &scoreDot);
        }
        
        // Instructions
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        for (int i = 0; i < 11; i++) {
            SDL_Rect instructionDot = {210 + i * 12, 285, 8, 8};
            SDL_RenderFillRect(renderer, &instructionDot);
        }
    }
    
    SDL_RenderPresent(renderer);
}