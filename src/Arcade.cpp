#include "Arcade.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

Arcade::Arcade(SDL_Renderer* renderer)
{
    background = nullptr;

    SDL_Surface* surface = IMG_Load("res/interface/Fleche.png");
    if (!surface) {
        std::cerr << IMG_GetError() << std::endl; //std::cerr pour l'extraction des erreurs
        return;
    }

    background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    m_buttonTexture = loadTexture(renderer, "res/interface/btn_carte.png");


    if (m_buttonTexture) {
        btnCarte = new Bouton(300, 20, 80, 40, m_buttonTexture);
    }
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

    if (btnCarte) {
        btnCarte->render(renderer);
    }
}

void Arcade::handleEvents(SDL_Event& event){
    
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

    
        if (btnCarte && btnCarte->isClicked(mouseX, mouseY)) { 
            requestTransition(SCENE_CARTE);
        }
    
    }
}

void Arcade::update(){
    //Same que handleEvents
}

SDL_Texture* Arcade::loadTexture(SDL_Renderer* renderer, const std::string& chemin)
{
    SDL_Surface* surface = IMG_Load(chemin.c_str());
    if (!surface) {
        std::cerr << "Erreur chargement texture: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}