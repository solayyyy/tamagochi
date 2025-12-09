#ifndef ANIMAL_HPP 
#define ANIMAL_HPP

#include <string>

class Lieu{
    protected:
    std::string nom;

    public:
    Lieu(const std::string& nom);
    std::string getNom() const;
};

#endif