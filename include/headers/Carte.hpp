#ifndef CARTE_HPP
#define CARTE_HPP

#include"Lieu.hpp"
#include <SDL.h>

class Carte : public Lieu {
    
public:
    Carte(SDL_Renderer* renderer);
    ~Carte();

    void handleEvents(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);

private:
    SDL_Renderer* a_renderer;
    SDL_Texture* a_background;

    //boutons
    SDL_Texture* texBtnMaison = nullptr;
    SDL_Texture* texBtnArcade = nullptr;
    
    SDL_Rect btnMaison;
    SDL_Rect btnArcade;
};

#endif