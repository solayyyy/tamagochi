#ifndef LIEU_HPP
#define LIEU_HPP

#include <SDL.h>
#include <iostream>

enum SceneType {
    SCENE_MAISON,
    SCENE_ARCADE,
    SCENE_BOUTIQUE,
    SCENE_QUIT 
};

class Lieu {
public:
    // Destructeur virtuel pour s'assurer que les classes dérivées sont bien nettoyées
    virtual ~Lieu() {}

    // Les trois fonctions essentielles d'une scène de jeu (virtuelles pures)

    virtual void handleEvents(SDL_Event& event) = 0;
    virtual void update() = 0;
    virtual void render(SDL_Renderer* renderer) = 0;

    
    bool isTransitionPending() const { return m_nextScene != SCENE_MAISON; } // Si ce n'est pas la scène par défaut
    SceneType getNextScene() const { return m_nextScene; }

protected:
    
    void requestTransition(SceneType nextScene) {
        m_nextScene = nextScene;
    }
    
private:
    SceneType m_nextScene = SCENE_MAISON; // SCENE_MAISON sera la valeur par défaut / scène active

};

#endif // LIEU_HPP