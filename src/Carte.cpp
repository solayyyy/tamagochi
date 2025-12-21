#include "Carte.hpp"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

Carte::Carte(SDL_Renderer* renderer){

    a_background = nullptr;

    SDL_Surface* surface = IMG_Load("res/scene_carte.png");
    if (!surface) {
        std::cerr << IMG_GetError() << std::endl; //std::cerr pour l'extraction des erreurs
        return;
    }

    a_background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    
    texBtnMaison = IMG_LoadTexture(renderer, "res/interface/btn_maison.png");
    texBtnArcade = IMG_LoadTexture(renderer, "res/interface/bouton_arcade.png");

    btnMaison = { 80, 150, 200, 200 };
    btnArcade = { 400, 300, 200, 200 };

}


Carte::~Carte()
{
    if(a_background){
        SDL_DestroyTexture(a_background);
    }
    SDL_DestroyTexture(texBtnMaison);
    SDL_DestroyTexture(texBtnArcade);
}

void Carte::render(SDL_Renderer* renderer){
    if (a_background){
        SDL_RenderCopy(renderer, a_background, nullptr, nullptr);
    }

    if (texBtnMaison) {
        SDL_RenderCopy(renderer, texBtnMaison, nullptr, &btnMaison);
    }

    if (texBtnArcade) {
        SDL_RenderCopy(renderer, texBtnArcade, nullptr, &btnArcade);
    }
}
void Carte::handleEvents(SDL_Event& event){
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mx = event.button.x;
        int my = event.button.y;

        // Retour Maison
        if (mx >= btnMaison.x && mx <= btnMaison.x + btnMaison.w &&
            my >= btnMaison.y && my <= btnMaison.y + btnMaison.h) {
            requestTransition(SCENE_MAISON);
            std::cout << "CLIC MAISON OK\n";
        }

        // Aller Arcade
        if (mx >= btnArcade.x && mx <= btnArcade.x + btnArcade.w &&
            my >= btnArcade.y && my <= btnArcade.y + btnArcade.h) {
            requestTransition(SCENE_ARCADE);
            std::cout << "CLIC ARCADE OK\n";
        }
    }
}

void Carte::update(){
    //Vide pour l'instant
}