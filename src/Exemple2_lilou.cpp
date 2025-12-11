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
    SDL_Event evenement;

    //Dessin des boutons pour intéragir avec l'animal.(x, y, largeur, hauteur)
    SDL_Rect btnNourrir = {60, 360, 80, 20};
    SDL_Rect btnSoigner = {60, 390, 80, 20};

    // Timer
    static Uint32 lastTime = SDL_GetTicks();

    while (run) {

        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) run = false;
            if (evenement.type == SDL_KEYDOWN && evenement.key.keysym.sym == SDLK_ESCAPE) run = false;

            if (evenement.type == SDL_MOUSEBUTTONDOWN) {
                int mx = evenement.button.x; //coordonée de la souris au moment du clic pour intéragir.
                int my = evenement.button.y;

                // Nourriture
                if (mx >= btnNourrir.x && mx <= btnNourrir.x + btnNourrir.w &&
                    my >= btnNourrir.y && my <= btnNourrir.y + btnNourrir.h) {
                    stats.setFaim(stats.getFaim() + 25); //tout est ok alors ajouter +25 a la barre nourriture (Faim).
                }

                // Médicament
                if (mx >= btnSoigner.x && mx <= btnSoigner.x + btnSoigner.w &&
                    my >= btnSoigner.y && my <= btnSoigner.y + btnSoigner.h) {
                    stats.setSante(stats.getSante() + 10);
                }
            }
        }

        // Fonction qui effacer l'écran
        SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
        SDL_RenderClear(renderer);

        // Création du cadre qui entoure les boutons et les barres 
        SDL_Rect cadre = {50, 350, 500, 90};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &cadre);

        // Dessin des barres d'Etats
        Barre_Etat(renderer, 330, 360, 200, 10, stats.getFaim(), {255, 0, 0, 255});
        Barre_Etat(renderer, 330, 380, 200, 10, stats.getJoie(), {0, 255, 0, 255});
        Barre_Etat(renderer, 330, 400, 200, 10, stats.getSante(), {0, 0, 255, 255});
        Barre_Etat(renderer, 330, 420, 200, 10, stats.getEnergie(), {255, 255, 0, 255});

        // Affichage de l'animal
        monAnimal.render(renderer);

        // Dessin des boutons 
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &btnNourrir);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &btnNourrir);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderFillRect(renderer, &btnSoigner);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &btnSoigner);

        // Timer
        Uint32 currentTime = SDL_GetTicks();

        if (currentTime - lastTime >= 1000) { // Toutes les 1 seconde via currentTime qui récupère l'heure du programme
            stats.setFaim(stats.getFaim() - 1);
            stats.setJoie(stats.getJoie() - 0.5f);
            stats.setEnergie(stats.getEnergie() - 0.8f);

            //Si la faim atteint 0 l'animal perd petit a petit de la santé.
            if (stats.getFaim() <= 0) {
                stats.setSante(stats.getSante() - 0.5f);
            }

            lastTime = currentTime;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    cleanup(window, renderer);
    return 0;
}
