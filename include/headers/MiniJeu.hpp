
#ifndef MINIJEU_HPP
#define MINIJEU_HPP

#include <SDL.h>
#include <vector>

// Structure pour les points de la grille
struct SnakePoint {
    int x, y;
};


class MiniJeu {
private:
    
    static const int CELL_SIZE = 20;
    static const int GRID_W = 30;  // 600 / 20
    static const int GRID_H = 25;  // 500 / 20
    static const int UPDATE_DELAY = 120;
    

    std::vector<SnakePoint> snakeBody;
    SnakePoint food;
    int snakeDirX;
    int snakeDirY;
    int gameScore;
    bool isGameOver;
    bool m_finished;
    
    Uint32 lastUpdate;
    
    
    void spawnFood();
    void updateSnake();
    void handleInput(SDL_Event& event);
    void renderGame(SDL_Renderer* renderer);

public:
    
    MiniJeu();
    ~MiniJeu();
    
    
    void init();
    bool update(SDL_Renderer* renderer, SDL_Event& event);
    void render(SDL_Renderer* renderer);
    bool isFinished() const { return m_finished; }
    int getScore() const { return gameScore; }
};

#endif // MINIJEU_HPP