#include "Animal.hpp"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

//Explication de la création de la classe Animal à compléter plus tard dans le main 
Animal::Animal(const std::string& nom, const std::string& type, const std::string& sexe, int age,
               SDL_Renderer* renderer, const std::string& chemin_image) 
    : nom(nom), type(type), sexe(sexe), age(age), 
      m_texture(nullptr) {


        //Chargement SDL
        SDL_Surface* surface = IMG_Load(chemin_image.c_str());
    if (!surface) {
        std::cerr << "Erreur chargement image animal: " << chemin_image << " | " << IMG_GetError() << std::endl;
        return; 
    }

    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    if (!m_texture) {
        std::cerr << "Erreur création texture animal: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(surface); 



    // Définition de la position et taille initiale 
    m_position = { 125, 150, 200, 200 };

}


    Animal::~Animal() {
    // Détruit la texture lorsque l'objet Animal est détruit.
    if (m_texture) {
        SDL_DestroyTexture(m_texture);
    }
}

// Ici on verifie le type, le sexe et l'age de l'animal
std::string Animal::getNom() const { return nom;}
std::string Animal::getType() const { return type; }
std::string Animal::getSexe() const { return sexe; }
int Animal::getAge() const { return age; }


void Animal::setType(const std::string& nouveau_type) { type = nouveau_type; }
void Animal::setSexe(const std::string& nouveau_sexe) { sexe = nouveau_sexe; }
void Animal::setAge(int nouveau_age) { age = nouveau_age; }


//Méthode rendu 
void Animal::render(SDL_Renderer* renderer) {
    if (m_texture) {
        SDL_RenderCopy(renderer, m_texture, NULL, &m_position);
    }
}

// Méthode position
void Animal::setPosition(int x, int y) {
    m_position.x = x;
    m_position.y = y;
}