
#include "Maison.hpp"
#include "Statistique.hpp"
#include "Init_SDL.hpp"
#include <iostream>
#include <SDL_image.h>

Maison::Maison(SDL_Renderer* renderer, Animal* animal) : 
    m_animal(animal),
    btnCarte(nullptr),
    btnFaim(nullptr),
    m_buttonfaim(nullptr),
    m_buttonTexture(nullptr),
    m_background(nullptr)
{   
    m_background = loadTexture(renderer, "res/scene_chambre.png");
    if (!m_background) {
        std::cerr << "ERREUR chargement scene_chambre.png" << std::endl;
    }

    //Chargement des boutons ressources !
    m_buttonTexture = loadTexture(renderer, "res/interface/Fleche.png"); 
    m_buttonfaim = loadTexture(renderer, "res/interface/bouton_faim.png");
    m_buttonSoigner = loadTexture(renderer, "res/interface/kitdesoins.png");

    //Création d'une position pour les bouttons :
    if (m_buttonfaim) {
        btnFaim = new Bouton(80, 350, 40, 40, m_buttonfaim);
    }

    if (m_buttonSoigner) {
        btnSoigner = new Bouton(60, 390, 40, 40, m_buttonSoigner);
    }
    
    // Création du bouton Carte (flèche).
    if (m_buttonTexture){
        btnCarte = new Bouton(510, 10, 80, 80, m_buttonTexture); 
    }
}

//paramètre de destruction Texture plus objet
Maison::~Maison() {
    if (btnCarte) {
        delete btnCarte;
        btnCarte = nullptr;
    }

    if (btnFaim) {
        delete btnFaim;
        btnFaim = nullptr;
    }

    if (btnSoigner) {
        delete btnSoigner;
        btnSoigner = nullptr;
    }

    if (m_buttonTexture) {
        SDL_DestroyTexture(m_buttonTexture);
        m_buttonTexture = nullptr;
    }

    if (m_buttonfaim){
        SDL_DestroyTexture(m_buttonfaim);
        m_buttonfaim = nullptr;
    }

    if (m_buttonSoigner) {
        SDL_DestroyTexture(m_buttonSoigner);
        m_buttonSoigner = nullptr;
    }

    if (m_background) {
        SDL_DestroyTexture(m_background);
        m_background = nullptr;
    }
}

void Maison::handleEvents(SDL_Event& event) {
    // Logique de la Maison: 
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x = event.button.x;
        int y = event.button.y;

        if (btnCarte && btnCarte->isClicked(x, y)) {
            requestTransition(SCENE_CARTE);
        }

         if (btnFaim && btnFaim->isClicked(x, y)) {
            m_animal->getStats().setFaim(
            m_animal->getStats().getFaim() + 25);
    }

        if (btnSoigner && btnSoigner->isClicked(x, y)) {
            m_animal->getStats().setSante(
            m_animal->getStats().getSante() + 10);
        }
    
    }
}

void Maison::update() {
    // Logique de la Maison: 
    // Mettre à jour l'animation de l'animal dans cette scène
    if (m_animal) {
        m_animal->updateAnimation();
    }
}

void Maison::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, m_background, nullptr, nullptr);
    // 1. Dessiner le fond
    if (!m_background) {
        std::cerr << "DEBUG: m_background est NULL\n";
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);
        return;
    }

    SDL_RenderCopy(renderer, m_background, nullptr, nullptr);

    // 2. Dessiner l'animal
    if (m_animal) {
        m_animal->render(renderer);
    }
    // cadre
    SDL_Rect cadre = {50, 350, 500, 90};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &cadre);

    // Dessine le bouton
    if (btnCarte) {
        btnCarte->render(renderer);
    }
    
    if (btnFaim) {
        btnFaim->render(renderer);
    }

    if (btnSoigner) {
        btnSoigner->render(renderer);
    }
    // 3. Dessiner les boutons/menus spécifiques à la Maison

    // barres d'état
    Barre_Etat(renderer, 330, 360, 200, 10,
               m_animal->getStats().getFaim(), {255, 0, 0, 255});

    Barre_Etat(renderer, 330, 380, 200, 10,
               m_animal->getStats().getJoie(), {0, 255, 0, 255});

    Barre_Etat(renderer, 330, 400, 200, 10,
               m_animal->getStats().getSante(), {0, 0, 255, 255});

    Barre_Etat(renderer, 330, 420, 200, 10,
               m_animal->getStats().getEnergie(), {255, 255, 0, 255});


    //Contour du grand cadre en noir et affichage
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &cadre);
}

    // Fonction utilitaire pour le chargement (À déplacer dans un fichier utilitaire propre)
SDL_Texture* Maison::loadTexture(SDL_Renderer* renderer, const std::string& chemin) {
    SDL_Surface* surface = IMG_Load(chemin.c_str());
    if (!surface) {
        std::cerr << "Erreur chargement texture bouton: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}






// --- DESTRUCTEUR ---
