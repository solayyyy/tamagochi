#include "Arcade.hpp"
#include <iostream>
#include <SDL_image.h>


Arcade::Arcade(SDL_Renderer* renderer) : m_renderer(renderer) {

    SDL_Surface* surface = IMG_Load("res/scene_arcade.png");
    background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); 
}

Arcade::~Arcade() {
    SDL_DestroyTexture(background);
}

void Arcade::handleEvents(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_r) {
            // requestTransition(SCENE_MAISON);
        }
    }
}

void Arcade::update() {}

void Arcade::render(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, background, nullptr, nullptr); //nullptr signifie toute l'image et pour toute la fenetre
}