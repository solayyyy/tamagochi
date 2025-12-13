#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

#include "Animal.hpp"
#include "Maison.hpp"
#include "Lieu.hpp"
#include "Arcade.hpp"

//initialisation

bool initialize_sdl_components(SDL_Window** window, SDL_Renderer** renderer);
void cleanup(SDL_Window* window, SDL_Renderer* renderer);


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

    // initialisation
    if (!initialize_sdl_components(&window, &renderer)) {
        // Le message d'erreur est affiché dans initialize_sdl_components
        cleanup(window, renderer); 
        return 1;
    }




    Lieu* m_currentLieu = nullptr;
    


    // pour eviter le flou comme pixel art
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"); 

    // Définition des chemins des 2 frames d'animation
    std::vector<std::string> chatFrames = {
        "res/Chat1/Chat1_frame1.png", // Frame 0
        "res/Chat1/Chat1_frame2.png"  // Frame 1
    };
    
    // créa objet
    
    Animal monAnimal(
        "Pim", 
        "Chat", 
        "M", 
        1, 
        renderer, 
        chatFrames
    );

    changeLieu(m_currentLieu, SCENE_MAISON, renderer, &monAnimal); //corriger et a voir.


    // Boucle du jeu
    bool running = true;
    SDL_Event event;

    while (running) {
        // Gérer les événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || 
                (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                running = false;
            }
            if (m_currentLieu) {
                m_currentLieu->handleEvents(event);
            }
        }
        if (m_currentLieu) {
            m_currentLieu->update();
        }

        if (m_currentLieu && m_currentLieu->isTransitionPending()) {
            SceneType nextScene = m_currentLieu->getNextScene();
            
            if (nextScene == SCENE_QUIT) {
                running = false; // Arrêter la boucle
            } else {
                // Changer la scène
                changeLieu(m_currentLieu, nextScene, renderer, &monAnimal);
            }
        }
        monAnimal.updateAnimation();

        // --- DESSIN ET RENDU --- (A modifier pour le fond et tout ça)
        
        // Fond blanc/gris
        SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
        SDL_RenderClear(renderer);

        // Afficher l'animal 
        monAnimal.render(renderer);


        //Afficher bg du lieu
        if (m_currentLieu) {
            m_currentLieu->render(renderer);
        }
        

        // Présenter le résultat à l'écran
        SDL_RenderPresent(renderer);

        // Limiter le FPS à 60 pour economiser ressource
        SDL_Delay(16);
    }

    // On nettoie tout
    cleanup(window, renderer);

    return 0;
}






//Fonctions (a voir pour deplacer dans un autre fichier style init)

bool initialize_sdl_components(SDL_Window** window, SDL_Renderer** renderer) {
    // 1. Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    // 1. Initialisation SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Erreur SDL_image: " << IMG_GetError() << std::endl;
        return false;
    }

    // 2. Création de la Fenêtre
    *window = SDL_CreateWindow(
        "Le jeu chouette de Lilou et Léane",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        400,  // Largeur
        500,  // Hauteur
        SDL_WINDOW_SHOWN
    );

    if (!*window) {
        std::cerr << "Erreur fenêtre: " << SDL_GetError() << std::endl;
        return false;
    }

    // 3. Création du Renderer
    *renderer = SDL_CreateRenderer(
        *window, 
        -1, 
        SDL_RENDERER_ACCELERATED
    );
    
    if (!*renderer) {
        std::cerr << "Erreur Renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    
    return true;
}

void cleanup(SDL_Window* window, SDL_Renderer* renderer) {
    // Nettoie les ressources dans l'ordre inverse de création
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    IMG_Quit();
    SDL_Quit();
}

