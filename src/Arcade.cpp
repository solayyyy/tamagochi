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

    m_btnmj1Texture = loadTexture(renderer, "res/interface/btnminijeu1.png");


    if (m_buttonTexture) {
        btnCarte = new Bouton(300, 20, 80, 40, m_buttonTexture);
    }

    if (m_btnmj1Texture) {
        btnmj1 = new Bouton(50, 250, 300, 300, m_btnmj1Texture);
    }

    m_miniJeu = nullptr;
    m_isPlayingGame = false;
}


Arcade::~Arcade()
{
    if (background) {
        SDL_DestroyTexture(background);
    }
    if (m_buttonTexture) {
        SDL_DestroyTexture(m_buttonTexture);
    }
    
    if (m_btnmj1Texture) {
        SDL_DestroyTexture(m_btnmj1Texture);
    }
    
    if (btnCarte) {
        delete btnCarte;
    }
    
    if (btnmj1) {
        delete btnmj1;
    }
    
    
    if (m_miniJeu) {
        delete m_miniJeu;
    }


    
}

void Arcade::render(SDL_Renderer* renderer)
{   
    if (m_isPlayingGame && m_miniJeu) {
        // Afficher le mini-jeu
        m_miniJeu->render(renderer);
    } else {
        if (background) {
            SDL_RenderCopy(renderer, background, nullptr, nullptr);
        }

        if (btnCarte) {
            btnCarte->render(renderer);
        }

        if (btnmj1) {
            btnmj1->render(renderer);
        }
    }
}

void Arcade::handleEvents(SDL_Event& event){
    if (m_isPlayingGame && m_miniJeu) {
        // Le mini-jeu gère ses propres événements
        // Si le jeu est terminé et qu'on appuie sur ESC/RETURN
        if (m_miniJeu->isFinished()) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE || 
                    event.key.keysym.sym == SDLK_RETURN) {
                    // Quitter le mini-jeu
                    delete m_miniJeu;
                    m_miniJeu = nullptr;
                    m_isPlayingGame = false;
                    std::cout << "Retour au menu Arcade\n";
                }
            }
        }
            } else {
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;

        
                if (btnCarte && btnCarte->isClicked(mouseX, mouseY)) { 
                    requestTransition(SCENE_CARTE);
                }

                if (btnmj1 && btnmj1->isClicked(mouseX, mouseY)) {
                    std::cout << "Lancement du mini-jeu!\n";
                    m_miniJeu = new MiniJeu();
                    m_isPlayingGame = true;
        
        }
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