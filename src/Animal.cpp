#include "Animal.hpp"
#include <iostream>

//Explication de la création de la classe Animal à compléter plus tard dans le main
Animal::Animal(const std::string& nom, const std::string& type, const std::string& sexe, int age) 
    : nom(nom), type(type), sexe(sexe), age(age) {}

// Ici on verifie le type, le sexe et l'age de l'animal
std::string Animal::getNom() const { return nom;}
std::string Animal::getType() const { return type; }
std::string Animal::getSexe() const { return sexe; }
int Animal::getAge() const { return age; }


void Animal::setType(const std::string& nouveau_type) { type = nouveau_type; }
void Animal::setSexe(const std::string& nouveau_sexe) { sexe = nouveau_sexe; }
void Animal::setAge(int nouveau_age) { age = nouveau_age; }

