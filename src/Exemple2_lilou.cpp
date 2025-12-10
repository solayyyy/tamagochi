/*//a mettre dans le main
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Cette partie définie les statistique de la fenêtre, le maximum de chaque classe liée a l'animal
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 500
#define MAX_STAT 100
#define STAT_DECAY_RATE 0.5f //ici c'est le temps de diminution des statistiques pour les animaux

*/

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <algorithm>
#include "Statistique.hpp"

//Dessin de la barre d'état des stats de l'animal
void drawStatBar(SDL_Renderer* renderer, int x, int y, int w, int h, float percent, SDL_Color color) {
    
    // Fond blanc
    SDL_Rect bgRect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &bgRect);

    // Création des Barres d'états colorées
    SDL_Rect fgRect = {x, y, static_cast<int>(w * (percent / 100.0f)), h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &fgRect);

    //contour des barres en noir
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &bgRect);
}

//Main du jeux 
int main(int argc, char* argv[]) {

    /*if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erreur SDL_Init: " << SDL_GetError() << std::endl;
        return 1;
    }
*/
    // Initialisation SDL_image  /  de ici !
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Erreur IMG_Init: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Tamagotchi Stats",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          600, 400, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Erreur SDL_CreateWindow: " << SDL_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Erreur SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    } //A ici a revoir !! 

    Stats stats; // Tes stats

    bool running = true;
    SDL_Event event;

    while (running) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        // Nettoyer l'écran
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Dessiner les barres de stats
        drawStatBar(renderer, 50, 50, 500, 30, stats.getFaim(),    {255, 0, 0, 255});    // rouge
        drawStatBar(renderer, 50, 100, 500, 30, stats.getJoie(), {0, 255, 0, 255});      // vert
        drawStatBar(renderer, 50, 150, 500, 30, stats.getSante(),   {0, 0, 255, 255});   // bleu
        drawStatBar(renderer, 50, 200, 500, 30, stats.getEnergie(), {255, 255, 0, 255}); // jaune

        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}