#ifndef ARCADE_HPP
#define ARCADE_HPP

#include "Lieu.hpp"
#include "Bouton.hpp"
#include "MiniJeu.hpp"
#include <SDL.h>
#include <string>

class Arcade : public Lieu{
public:
    Arcade(SDL_Renderer* renderer);
    ~Arcade(); 

    void handleEvents(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);

private:
    SDL_Renderer* m_renderer = nullptr;
    SDL_Texture* background;

    
    // Ajout du bouton
    Bouton* btnCarte;
    SDL_Texture* m_buttonTexture;

    //Bouton du premier mini jeu
    Bouton* btnmj1;
    SDL_Texture* m_btnmj1Texture;
    

    MiniJeu* m_miniJeu;  
    bool m_isPlayingGame;



    // Fonction utilitaire pour charger les textures
    SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& chemin);

};
#endif // ARCADE_HPP