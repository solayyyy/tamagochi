#include "Nourriture.hpp"
#include <iostream>

Nourriture::Nourriture(const std::string& nom, int donner_a_manger)
    : nom(nom), donner_a_manger(donner_a_manger) {}

int Nourriture::getDonneramanger() const {return donner_a_manger; }
