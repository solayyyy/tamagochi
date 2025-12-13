#include "Bouton.hpp"

Bouton::Bouton(int x, int y, int w, int h, SDL_Texture* texture)
    : m_texture(texture)
{
    m_rect = {x, y, w, h};
}

bool Bouton::isClicked(int mouseX, int mouseY) const {
    // Vérifie si les coordonnées (x, y) sont dans le rectangle (m_rect)
    return (mouseX >= m_rect.x && 
            mouseX <= m_rect.x + m_rect.w &&
            mouseY >= m_rect.y && 
            mouseY <= m_rect.y + m_rect.h);
}

void Bouton::render(SDL_Renderer* renderer) const {
    if (m_texture) {
        SDL_RenderCopy(renderer, m_texture, NULL, &m_rect);
    } 
    // Optionnel : Si pas de texture, on peut dessiner un rectangle de couleur
    /*
    else {
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Gris
        SDL_RenderFillRect(renderer, &m_rect);
    }
    */
}