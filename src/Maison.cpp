#include "Maison.hpp"
#include <iostream>
#include <SDL_image.h>

Maison::Maison(SDL_Renderer* renderer, Animal* animal) : 
    m_animal(animal), 
    m_arcadeButton(nullptr),
    m_buttonTexture(nullptr),
    m_background(nullptr)
{
    // CHARGEMENT DES RESSOURCES DU BOUTON
    // (Assurez-vous que cette image existe)
    m_buttonTexture = loadTexture(renderer, "res/interface/bouton_arcade.png"); 
    m_background = loadTexture(renderer, "res/bg_maison.png");
    
    // CRÉATION DE L'OBJET BOUTON
    // Le bouton est placé en haut à droite (par exemple)
    m_arcadeButton = new Bouton(300, 20, 80, 40, m_buttonTexture); 
}

void Maison::handleEvents(SDL_Event& event) {
    // Logique de la Maison: 
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;

        // Exemple : si le clic est dans la zone du bouton "Arcade" (à définir)
        if (m_arcadeButton && m_arcadeButton->isClicked(mouseX, mouseY)) {
            // 2. Si oui, demande la transition
            requestTransition(SCENE_ARCADE);
        }
    }
    // Par exemple, si on clique sur un bouton "Nourrir"
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
    SDL_RenderCopy(renderer, m_background, NULL, NULL); 

    // 2. Dessiner l'animal
    if (m_animal) {
        m_animal->render(renderer);
    }
    // Dessine le bouton
    if (m_arcadeButton) {
        m_arcadeButton->render(renderer);
    }
}
    


    // 3. Dessiner les boutons/menus spécifiques à la Maison
    // --- Fonction utilitaire pour le chargement (À déplacer dans un fichier utilitaire propre) ---
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


