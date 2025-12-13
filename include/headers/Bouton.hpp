#ifndef BOUTON_HPP
#define BOUTON_HPP

#include <SDL.h>
#include <string>

class Bouton {
public:
    Bouton(int x, int y, int w, int h, SDL_Texture* texture);

    //verifie si le bouton a bien été cliqué
    bool isClicked(int mouseX, int mouseY) const;

    //dessine bouton
    void render(SDL_Renderer* renderer) const;

private:
    SDL_Rect m_rect;
    SDL_Texture* m_texture;
};

#endif // BOUTON_HPP