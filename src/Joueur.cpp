#include "Joueur.hpp"
#include <iostream>


Joueur::Joueur(const std::string& prenom) 
    : prenom(prenom), nbr_animaux(0) {}

void Joueur::ajouterAnimal(Animal* animal) {
    collection.push_back(animal);
    nbr_animaux++;
}

int Joueur::getNbAnimaux() const { return nbr_animaux; }

const std::vector<Animal*>& Joueur::getCollection() const {
    return collection;
}