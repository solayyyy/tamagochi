#ifndef ARCADE_HPP
#define ARCADE_HPP

#include "Lieu.hpp"
#include <SDL.h>

class Arcade {
public:
    Arcade(SDL_Renderer* renderer);
    ~Arcade(); 

    void handleEvents(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);

private:
    SDL_Renderer* m_renderer = nullptr;
    SDL_Texture* background = "res/scène_arcade.png"; 
}
#endif // ARCADE_HPP