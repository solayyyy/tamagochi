
#ifndef MAISON_HPP
#define MAISON_HPP

#include "Lieu.hpp"
#include "Animal.hpp"
#include "Bouton.hpp"

class Maison : public Lieu {
public:
    Maison(SDL_Renderer* renderer, Animal* animal);
    ~Maison() override;

    // Implémentations des fonctions virtuelles pures
    void handleEvents(SDL_Event& evenement) override;
    void update() override;
    void render(SDL_Renderer* renderer) override;

private:
    Animal* m_animal; // Pointeur vers l'animal (il n'est pas géré par la Maison)
    SDL_Texture* m_background; // une image de fond de la maison
    
    Bouton* btnCarte; 
    
    // NOUVEAU : La texture du bouton (doit être chargée une fois)
    SDL_Texture* m_buttonTexture; 

    // Méthode utilitaire pour charger les textures des boutons
    SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& chemin);

  
};

#endif 
