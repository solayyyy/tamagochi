#ifndef JOUEUR_HPP
#define JOUEUR_HPP

#include <string>
#include <vector>
#include "Animal.hpp"

class Joueur{
    protected:
        int nbr_animaux;
        std::vector<Animal*> collection; //pointeur vers un animal de la collection
    
    public:
        std::string prenom;
        Joueur(const std::string& prenom );

    // Gestion des animaux
    void ajouterAnimal(Animal* animal);
    int getNbAnimaux() const;

    // Gérer la collection et lecture de tous les Animaux présent 
    const std::vector<Animal*>& getCollection() const;
};

#endif
