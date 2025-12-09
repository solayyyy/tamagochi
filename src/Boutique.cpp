#include "Boutique.hpp"
#include <iostream>

void Boutique::ajouterProduit(const Nourriture& nouveau_nourriture){
    liste.push_back(nouveau_nourriture);
}

const std::vector<Nourriture>& Boutique::getProduit() const {
    return liste;
}