#ifndef ANIMAL_HPP //Pour éviter toute confusion on l'écrit en MAJUSCULE
#define ANIMAL_HPP

#include  "Statistique.hpp"
#include <string>

enum class humeur{ //enum est un groupe de constante
    heureux,
    triste,
    fatigue,
    mort,
};

class Animal{
    protected: 
        std::string type;
        std::string sexe;
        int age;
        Stats* Stats; //Animal possède les statistiques

    public:
        std::string nom;

    Animal(const std::string& nom, const std::string& type, const std::string& sexe, int age); 
    //Initialiser le programme avec un nom un type un sexe et un âge, à changer plutard si on veut que l'age augmente

    // Fonction qui permet de lire un attribut protéger ou privée.
    std::string getNom() const;
    std::string getType() const;
    std::string getSexe() const;
    int getAge() const;

    // Fonctions qui permet de modifier un attribut
    void setType(const std::string& nouveau_type);
    void setSexe(const std::string& nouveau_sexe);
    void setAge(int nouveau_age);

    // polymorphisme // Plutard si on veut faire parler l'animal on pourra par exemple
    //virtual void Politesse() const;

};

#endif

