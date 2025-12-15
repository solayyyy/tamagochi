
#include "Maison.hpp"
#include <iostream>
#include <SDL_image.h>

Maison::Maison(SDL_Renderer* renderer, Animal* animal) : 
    m_animal(animal),
    btnCarte(nullptr),
    m_buttonTexture(nullptr),
    m_background(nullptr)
{
    // CHARGEMENT DES RESSOURCES DU BOUTON
    // (Assurez-vous que cette image existe)
    m_buttonTexture = loadTexture(renderer, "res/interface/btn_carte.png"); 
    m_background = loadTexture(renderer, "res/scene_chambre.png");
    
    // CRÉATION DE L'OBJET BOUTON
    // Le bouton est placé en haut à droite (par exemple)
    if (m_buttonTexture){
        btnCarte = new Bouton(300, 20, 80, 40, m_buttonTexture); 
    }
}
//paramètre de destruction
Maison::~Maison() {
    if (btnCarte) {
        delete btnCarte;
        btnCarte = nullptr;
    }

    if (m_buttonTexture) {
        SDL_DestroyTexture(m_buttonTexture);
        m_buttonTexture = nullptr;
    }

    if (m_background) {
        SDL_DestroyTexture(m_background);
        m_background = nullptr;
    }
}

void Maison::handleEvents(SDL_Event& event) {
    // Logique de la Maison: 
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

        // Exemple : si le clic est dans la zone du bouton "Arcade" (à définir)
        if (btnCarte && btnCarte->isClicked(mouseX, mouseY)) { 
            requestTransition(SCENE_CARTE);
        }
    // Par exemple, si on clique sur un bouton "Nourrir"
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
    // 1. Dessiner le fond
    if (!m_background) {
        std::cerr << "DEBUG: m_background est NULL\n";
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // rouge debug 🔴
        SDL_RenderClear(renderer);
        return;
    }
    if (m_background) {
        SDL_RenderCopy(renderer, m_background, NULL, NULL);
    } else {
        // Fond debug si texture absente 
        SDL_SetRenderDrawColor(renderer, 50, 50, 150, 255);
        SDL_RenderClear(renderer);
    }

    // 2. Dessiner l'animal
    if (m_animal) {
        m_animal->render(renderer);
    }
    // Dessine le bouton
    if (btnCarte) {
        btnCarte->render(renderer);
    }
}
    

    // 3. Dessiner les boutons/menus spécifiques à la Maison
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
