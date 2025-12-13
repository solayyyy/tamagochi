#include "Arcade.hpp"
#include <iostream>

Arcade::Arcade(SDL_Renderer* renderer) : m_renderer(renderer) {
    // Initialisation basique si besoin
}

void Arcade::handleEvents(SDL_Event& event) {
    // Si une touche est pressée
    if (event.type == SDL_KEYDOWN) {
        // Si la touche est 'R' (Retour)
        if (event.key.keysym.sym == SDLK_r) {
            // Demande la transition vers la Maison
            requestTransition(SCENE_MAISON);
        }
    }
}

void Arcade::update() {
    // Rien à mettre à jour pour l'instant (pas d'animation dans cette scène)
}

void Arcade::render(SDL_Renderer* renderer) {
    // 1. Définir une couleur de fond différente pour l'Arcade (ex: Bleu)
    SDL_SetRenderDrawColor(renderer, 50, 50, 150, 255);
    SDL_RenderClear(renderer);

    // 2. (Si vous aviez une police) Afficher le texte "ARCADE" au centre
    // Pour l'instant, le fond bleu suffira à confirmer la transition.
}