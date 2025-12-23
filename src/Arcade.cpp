#include "Arcade.hpp"
#include "MiniJeu.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

Arcade::Arcade(SDL_Renderer* renderer)
{
    m_renderer = renderer;
    background = nullptr;

    SDL_Surface* surface = IMG_Load("res/scene_arcade.png");
    if (!surface) {
        std::cerr << IMG_GetError() << std::endl;
        return;
    }

    background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    m_buttonTexture = loadTexture(renderer, "res/interface/Fleche.png");
    m_btnmj1Texture = loadTexture(renderer, "res/interface/btnminijeu1.png");

    if (m_buttonTexture) {
        btnCarte = new Bouton(500, 250, 80, 40, m_buttonTexture);
    }

    if (m_btnmj1Texture) {
        btnmj1 = new Bouton(50, 250, 300, 300, m_btnmj1Texture);
    }
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
}

void Arcade::render(SDL_Renderer* renderer)
{   
     if (m_isPlayingGame && m_miniJeu) {
        std::cout << "Rendu du mini-jeu" << std::endl;
        
        // Le mini-jeu affiche son propre rendu
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

void Arcade::handleEvents(SDL_Event& event)

   
{
   if (m_isPlayingGame && m_miniJeu) {
        std::cout << "HandleEvents du mini-jeu" << std::endl;
        
        // Le mini-jeu gère l'événement
        m_miniJeu->update(m_renderer, event);
        
        // Vérifier si le jeu est terminé
        if (m_miniJeu->isFinished()) {
            int score = m_miniJeu->getScore();
            std::cout << "Score final: " << score << " pièces!\n";
            
            delete m_miniJeu;
            m_miniJeu = nullptr;
            m_isPlayingGame = false;
            std::cout << "Retour au menu Arcade\n";
        }
        
    } else {
        // Menu Arcade normal
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;

            if (btnCarte && btnCarte->isClicked(mouseX, mouseY)) { 
                requestTransition(SCENE_CARTE);
            }

            if (btnmj1 && btnmj1->isClicked(mouseX, mouseY)) {
                std::cout << "=== LANCEMENT DU SNAKE ===" << std::endl;
                m_miniJeu = new MiniJeu();
                m_isPlayingGame = true;
                std::cout << "m_isPlayingGame = " << m_isPlayingGame << std::endl;
            }
        }
    }
}

void Arcade::update()
{
    if (m_isPlayingGame && m_miniJeu) {
        std::cout << "Update du mini-jeu" << std::endl;
    }
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