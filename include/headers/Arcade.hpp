#ifndef ARCADE_HPP
#define ARCADE_HPP

#include "Lieu.hpp"
#include <SDL.h>

class Arcade : public Lieu {
public:
    Arcade(SDL_Renderer* renderer);
    ~Arcade() override {}

    void handleEvents(SDL_Event& event) override;
    void update() override;
    void render(SDL_Renderer* renderer) override;

private:
    // Pointeur vers le renderer, stocké si besoin
    SDL_Renderer* m_renderer; 
};

#endif // ARCADE_HPP