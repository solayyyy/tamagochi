#include "Statistique.hpp"
#include <algorithm>

// Constructeur
Stats::Stats() : faim(100.0f), joie(100.0f), sante(100.0f), energie(100.0f) {} //le f a coter de 100.0 signifie float

// Getters
float Stats::getFaim() const { return faim; }
float Stats::getJoie() const { return joie; }
float Stats::getSante() const { return sante; }
float Stats::getEnergie() const { return energie; }

// Setters
void Stats::setFaim(float v) { faim = std::max(0.0f, std::min(v, 100.0f)); } //la faim ne peut pas dépasser 0 ni augmenter a + de 100
void Stats::setJoie(float v) { joie = std::max(0.0f, std::min(v, 100.0f)); }
void Stats::setSante(float v) { sante = std::max(0.0f, std::min(v, 100.0f)); }
void Stats::setEnergie(float v) { energie = std::max(0.0f, std::min(v, 100.0f)); }
