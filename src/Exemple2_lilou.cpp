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

#include "Animal.hpp"
#include "Statistique.hpp"

void Barre_Etat(SDL_Renderer* renderer, int x, int y, int w, int h, float percent, SDL_Color color) {
    percent = std::max(0.0f, std::min(100.0f, percent));

    SDL_Rect bg = {x, y, w, h};                                   // Fond
    SDL_Rect fg = {x, y, int(w * (percent / 100.f)), h};          // Barre remplie

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);          // Fond blanc
    SDL_RenderFillRect(renderer, &bg);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &fg);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);                // Contour Noir
    SDL_RenderDrawRect(renderer, &bg);
}

    //Initialisation SDL_image et SDL
bool Initialise_SDL(SDL_Window** win, SDL_Renderer** ren) {
    SDL_Init(SDL_INIT_VIDEO); //initialisation de la fenêtre
    IMG_Init(IMG_INIT_PNG); //et de l'image

    *win = SDL_CreateWindow("Super jeu de Léane et Lilou",
                            100, 100, 600, 500, 0);

    *ren = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED); //Dessin des barres grace a ça 

    return true;
}
//vider la mémoire après fermeture de la fenêtre
void cleanup(SDL_Window* win, SDL_Renderer* ren) {
    if (ren) SDL_DestroyRenderer(ren);
    if (win) SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!Initialise_SDL(&window, &renderer))
        return 1;

    //Imporatatin de l'animal avec l'image 
    Animal monAnimal(
        "Pim",
        "Chat",
        "M",
        1,
        renderer,
        "res/Chat1/Chat1_frame1.png"  
    );

    Stats stats;

    bool run = true;
    SDL_Event e;

    while (run) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) run = false;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) run = false;
        }

        // Fond gris clair
        SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
        SDL_RenderClear(renderer);

        //cadre autour des barre d'état
        SDL_Rect cadre = {50, 350, 500, 90};  
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &cadre);

        // Barre d'état (x, y, largeur, hauteur)
        Barre_Etat(renderer, 330, 360, 200, 10, stats.getFaim(),    {255,   0,   0, 255});
        Barre_Etat(renderer, 330, 380, 200, 10, stats.getJoie(),    {  0, 255,   0, 255});
        Barre_Etat(renderer, 330, 400, 200, 10, stats.getSante(),   {  0,   0, 255, 255});
        Barre_Etat(renderer, 330, 420, 200, 10, stats.getEnergie(), {255, 255,   0, 255});

        //Affichage 
        monAnimal.render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    cleanup(window, renderer);
    return 0;
}