#include "Arcade.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

Arcade::Arcade(SDL_Renderer* renderer)
{
    background = nullptr;

    SDL_Surface* surface = IMG_Load("res/scene_arcade.png");
    if (!surface) {
        std::cerr << IMG_GetError() << std::endl; //std::cerr pour l'extraction des erreurs
        return;
    }

    background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Arcade::~Arcade()
{
    if (background) {
        SDL_DestroyTexture(background);
    }
}

void Arcade::render(SDL_Renderer* renderer)
{
    if (background) {
        SDL_RenderCopy(renderer, background, nullptr, nullptr);
    }
}

void Arcade::handleEvents(SDL_Event& event){
    //Vide pour l'instant mais apparement obligatoire pour une bonne compilation
}
void Arcade::update(){
    //Same que handleEvents
}