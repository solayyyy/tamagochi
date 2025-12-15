#include "Init_SDL.hpp"
#include <iostream>

//Création des barres d'état de l'Animal.
void Barre_Etat(SDL_Renderer* renderer, int x, int y, int w, int h,
                float percent, SDL_Color color)
{
    percent = std::max(0.0f, std::min(100.0f, percent)); //oblige le compteur a ne pas dépasser 0 et 100.

    SDL_Rect bg = {x, y, w, h}; //Fond (couleur des barre)
    SDL_Rect fg = {x, y, int(w * (percent / 100.f)), h}; //barre remplie

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fond blanc 
    SDL_RenderFillRect(renderer, &bg);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255); // barre
    SDL_RenderFillRect(renderer, &fg);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // contour noir
    SDL_RenderDrawRect(renderer, &bg);
}

//initialisation de la librairie SDL avec création d'une fenêtre.
bool Init_SDL(SDL_Window** win, SDL_Renderer** ren) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "IMG_Init failed: " << IMG_GetError() << std::endl;
        return false;
    }

    *win = SDL_CreateWindow(
        "Jeu super chouette de Léane et Lilou",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        600, 500,
        SDL_WINDOW_SHOWN
    );

    if (!*win) {
        std::cout << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        return false;
    }

    *ren = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED);

    if (!*ren) {
        std::cout << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

//Netoyage des fenêtres.
void cleanup(SDL_Window* win, SDL_Renderer* ren) {

    if (ren) SDL_DestroyRenderer(ren);
    if (win) SDL_DestroyWindow(win);

    IMG_Quit();
    SDL_Quit();
}
