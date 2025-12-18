#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

#include "Init_SDL.hpp"
#include "Animal.hpp"
#include "Maison.hpp"
#include "Lieu.hpp"
#include "Arcade.hpp"
#include "Statistique.hpp"
#include "Carte.hpp"


void changeLieu(Lieu*& currentLieu, SceneType nextScene, SDL_Renderer* renderer, Animal* animal) {
    if (currentLieu) {
        // 1. DÉTRUIRE l'ancienne scène pour libérer la mémoire
        delete currentLieu;
        currentLieu = nullptr;
    }
    // 2. CRÉER la nouvelle scène en fonction du type demandé
    switch (nextScene) {
        case SCENE_MAISON:
            std::cout << "Chargement de la Maison..." << std::endl;
            // On suppose que la Maison a besoin du renderer et de l'animal
            currentLieu = new Maison(renderer, animal); 
            break;
        case SCENE_ARCADE:
            std::cout << "Chargement de l'Arcade..." << std::endl;
            // On suppose que l'Arcade n'a besoin que du renderer
            currentLieu = new Arcade(renderer); 
            break;
        case SCENE_CARTE:
            std::cout << "Chargement de la Carte..." << std::endl;
            //seulement le renderer
            currentLieu = new Carte(renderer);
            break;
        //case SCENE_BOUTIQUE:
          //  std::cout << "Chargement de la Boutique..." << std::endl;
            // On suppose que la Boutique a besoin du renderer et de l'animal pour les stats
          //  currentLieu = new Boutique(renderer, animal); 
           // break;
        default:
            // S'il y a une erreur ou SCENE_QUIT (géré par la boucle principale)
            break; 
    }
}

int main(int argc, char* argv[]) {

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    
    

    if (!Init_SDL(&window, &renderer))
    
        return -1;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    
    Lieu* m_currentLieu = nullptr;

    // Définition des chemins des 2 frames d'animation
    std::vector<std::string> chatFrames = {
        "res/Chat1/Chat1_frame1.png", // Frame 0
        "res/Chat1/Chat1_frame2.png"  // Frame 1
    };

    //Imporatatin de l'animal avec l'image 
    Animal monAnimal(
        "Pim",
        "Chat",
        "M",
        1,
        renderer,
        chatFrames
    );

    changeLieu(m_currentLieu, SCENE_MAISON, renderer, &monAnimal);

    //boucle du jeu
    bool run = true;
    SDL_Event event;

    //Dessin des boutons pour intéragir avec l'animal.(x, y, largeur, hauteur)
    

    // Timer
    static Uint32 lastTime = SDL_GetTicks();

    while (run) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) run = false;
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                run = false;

            if (m_currentLieu) {
                m_currentLieu->handleEvents(event);
            }
        }

        if (m_currentLieu) {
            m_currentLieu->update();
        }

        if (m_currentLieu && m_currentLieu->isTransitionPending()) {
            SceneType next = m_currentLieu->getNextScene();
            m_currentLieu->resetTransition();
            changeLieu(m_currentLieu, next, renderer, &monAnimal);
        }

        Uint32 now = SDL_GetTicks();
        if (now - lastTime >= 1000) {
            monAnimal.getStats().setFaim(monAnimal.getStats().getFaim() - 1);
            monAnimal.getStats().setJoie(monAnimal.getStats().getJoie() - 0.5f);
            monAnimal.getStats().setEnergie(monAnimal.getStats().getEnergie() - 0.8f);

            if (monAnimal.getStats().getFaim() <= 0) {
                monAnimal.getStats().setSante(
                    monAnimal.getStats().getSante() - 0.5f
                );
            }
            lastTime = now;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (m_currentLieu) {
            m_currentLieu->render(renderer);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    delete m_currentLieu;
    cleanup(window, renderer);
    return 0;
}