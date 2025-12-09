#ifdef LIEU_HPP 
#define LIEU_HPP

#include <string>
class Lieu{
    protected:
    std::string nom;

    public:
    Lieu(const std::string& nom);
    std::string getNom() const;
};

#endif