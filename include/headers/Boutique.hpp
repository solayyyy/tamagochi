#ifndef BOUTIQUE_HPP
#define BOUTIQUE_HPP

#include <vector>
#include "Nourriture.hpp"

class Boutique{
    private:
        std::vector<Nourriture>liste;

    public:
        void ajouterProduit(const Nourriture& nouveau_nourriture);
        const std::vector<Nourriture>& getProduit() const;

};

#endif