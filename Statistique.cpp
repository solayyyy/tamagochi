#include "Statistique.hpp"
#include <algorithm> //pour les outils min et max utiliser.

Stats::Stats() : bonheur(100.0f), faim(100.0f), energie(100.0f), sante(100.0f){}

//Getters


float Stats::getJoie() const {
    return bonheur;
}

float Stats::getFaim() const {
    return faim;
}

float Stats::getEnergie() const {
    return energie;
}

float Stats::getSante() const {
    return sante;
}

// Setters, "f" après 100.0 indique que c'est un float.
void Stats::setJoie(float valeur) {
    bonheur = std::max(0.0f, std::min(valeur, 100.0f));
}

void Stats::setFaim(float valeur) {
    faim = std::max(0.0f, std::min(valeur, 100.0f));
}

void Stats::setEnergie(float valeur) {
    energie = std::max(0.0f, std::min(valeur, 100.0f));
}

void Stats::setSante(float valeur) {
    sante = std::max(0.0f, std::min(valeur, 100.0f));
}



