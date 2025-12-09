#include "Lieu.hpp"
#include <iostream>


Lieu::Lieu(const std::string& nom)
    : nom(nom) {}

std::string Lieu::getNom() const { return nom; }