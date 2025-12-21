#include "Animal.hpp"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

//Explication de la création de la classe Animal à compléter plus tard dans le main 
Animal::Animal(const std::string& nom,
               const std::string& type,
               const std::string& sexe,
               int age,
               SDL_Renderer* renderer,
               const std::vector<std::string>& chemin_image)
    : nom(nom),
      type(type),
      sexe(sexe),
      age(age),
      m_lastFrameTime(SDL_GetTicks())
    { 
        m_stats = new Stats();


        //Chargement SDL
        for (const auto& chemin : chemin_image) {
            SDL_Surface* surface = IMG_Load(chemin.c_str());
            if (!surface) {
                std::cerr << "Erreur chargement frame: " << chemin << " | " << IMG_GetError() << std::endl;
                continue; // Continue au lieu de s'arrêter pour le moment
            }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture) {
                m_textures.push_back(texture); // Stocke la nouvelle texture
            } else {
                std::cerr << "Erreur création texture: " << SDL_GetError() << std::endl;
            }

        SDL_FreeSurface(surface); 
    }



    // Définition de la position et taille initiale 
    m_position = { 225, 150, 200, 200 };

    }


    Animal::~Animal() {
    // Détruit la texture lorsque l'objet Animal est détruit.
    for (SDL_Texture* texture : m_textures) {
        SDL_DestroyTexture(texture);
    }
    delete m_stats;
}

// Ici on verifie le type, le sexe et l'age de l'animal
std::string Animal::getNom() const { return nom;}
std::string Animal::getType() const { return type; }
std::string Animal::getSexe() const { return sexe; }
int Animal::getAge() const { return age; }


void Animal::setType(const std::string& nouveau_type) { type = nouveau_type; }
void Animal::setSexe(const std::string& nouveau_sexe) { sexe = nouveau_sexe; }
void Animal::setAge(int nouveau_age) { age = nouveau_age; }


//Méthode d'animation
void Animal::updateAnimation() {
    if (m_textures.empty()) return;

    Uint32 currentTime = SDL_GetTicks();
    
    // Vérifie si le temps de la FRAME_DURATION_MS est écoulé
    if (currentTime > m_lastFrameTime + FRAME_DURATION_MS) {
        // Passe à la frame suivante 
        m_currentFrameIndex = (m_currentFrameIndex + 1) % m_textures.size();
        
        // Met à jour le temps de la dernière frame
        m_lastFrameTime = currentTime; 
    }
}


//Méthode rendu 
void Animal::render(SDL_Renderer* renderer) {
    if (m_textures.empty()) return;
    SDL_RenderCopy(renderer, m_textures[m_currentFrameIndex], NULL, &m_position);

}

// Méthode position
void Animal::setPosition(int x, int y) {
    m_position.x = x;
    m_position.y = y;
}