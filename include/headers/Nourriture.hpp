#ifndef NOURRITURE_HPP
#define NOURRITURE_HPP

#include<string>

class Nourriture{
    protected:
    std::string nom;
    int donner_a_manger;

    public:
    Nourriture(const std::string& nom, int donner_a_manger);
    int getDonneramanger() const;
};

#endif