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
    SDL_Texture* btnCarteTexture = nullptr;
    SDL_Texture* btnNourrirTexture = nullptr;
    SDL_Rect btnCarteRect = {160, 360, 80, 20};
    SDL_Rect btnNourrir = {300, 100, 80, 20};

    if (!Init_SDL(&window, &renderer))
    
        return -1;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    
    Lieu* m_currentLieu = nullptr;
    SDL_Surface* surfaceBtnCarte = IMG_Load("res/interface/btn_carte.png");
    if (!surfaceBtnCarte) {
        std::cerr << "Erreur chargement btn_carte.png : "
              << IMG_GetError() << std::endl;
    } else {
        btnCarteTexture = SDL_CreateTextureFromSurface(renderer, surfaceBtnCarte);
        SDL_FreeSurface(surfaceBtnCarte);
}

    SDL_Surface* surfaceBtnNourrir = IMG_Load("res/interface/bouton_faim.png");
    if (!surfaceBtnNourrir) {
        std::cerr << "Erreur chargement bouton_faim.png : "
              << IMG_GetError() << std::endl;
    } else {
        btnNourrirTexture = SDL_CreateTextureFromSurface(renderer, surfaceBtnNourrir);
        SDL_FreeSurface(surfaceBtnNourrir);
}

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
    Stats stats;

    //boucle du jeu
    bool run = true;
    SDL_Event evenement;

    //Dessin des boutons pour intéragir avec l'animal.(x, y, largeur, hauteur)
    //SDL_Rect btnNourrir = {60, 360, 80, 20};
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
            if (m_currentLieu) {
                m_currentLieu->handleEvents(evenement);
            }
        }
        
        
        if (m_currentLieu) {
            m_currentLieu->update();
        }

        if (m_currentLieu && m_currentLieu->isTransitionPending()) {

            SceneType nextScene = m_currentLieu->getNextScene();
            std::cout << "Transition vers scene: " << nextScene << std::endl;

            m_currentLieu->resetTransition();

            if (nextScene == SCENE_QUIT) {
                run = false;
            } else {
                changeLieu(m_currentLieu, nextScene, renderer, &monAnimal);
            }
        }

        
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

        // 1. Dessiner la scène EN PREMIER
        if (m_currentLieu) {
        m_currentLieu->render(renderer);
    }
        if (dynamic_cast<Maison*>(m_currentLieu)){
            if (btnCarteTexture) {
                SDL_RenderCopy(renderer, btnCarteTexture, nullptr, &btnCarteRect);

            }
            if (btnNourrirTexture) {
                SDL_RenderCopy(renderer, btnNourrirTexture, nullptr, &btnNourrir);

            }

            // cadre
            SDL_Rect cadre = {50, 350, 500, 90};

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &cadre);

            // barres d'état
            Barre_Etat(renderer, 330, 360, 200, 10, stats.getFaim(), {255, 0, 0, 255});
            Barre_Etat(renderer, 330, 380, 200, 10, stats.getJoie(), {0, 255, 0, 255});
            Barre_Etat(renderer, 330, 400, 200, 10, stats.getSante(), {0, 0, 255, 255});
            Barre_Etat(renderer, 330, 420, 200, 10, stats.getEnergie(), {255, 255, 0, 255});

            // boutons
            //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            //SDL_RenderFillRect(renderer, &btnNourrir);
            //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            //SDL_RenderDrawRect(renderer, &btnNourrir);

            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderFillRect(renderer, &btnSoigner);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &btnSoigner);

            //Contour du grand cadre en noir et affichage
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &cadre);
        }

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

        //Affichage du résultat sur l'écran
        SDL_RenderPresent(renderer);
        //Limite FPS à 60 pour économiser des ressources
        SDL_Delay(16);
    
}
    //tout netoyer
    if (btnCarteTexture)
        SDL_DestroyTexture(btnCarteTexture);

    delete m_currentLieu;
    cleanup(window, renderer);

    return 0;
}
