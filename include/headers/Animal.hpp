#ifndef ANIMAL_HPP //Pour éviter toute confusion on l'écrit en MAJUSCULE
#define ANIMAL_HPP



#include <SDL.h>
#include <SDL_image.h>
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

    Animal(const std::string& nom, const std::string& type, const std::string& sexe, int age, SDL_Renderer *renderer, const std::string &chemin_image); 
    //Initialiser le programme avec un nom un type un sexe et un âge, à changer plutard si on veut que l'age augmente + création propriété graphique

    ~Animal(); // Nécessaire pour détruire la SDL_Texture

    // Fonction qui permet de lire un attribut protéger ou privée.
    std::string getNom() const;
    std::string getType() const;
    std::string getSexe() const;
    int getAge() const;

    // Fonctions qui permet de modifier un attribut
    void setType(const std::string& nouveau_type);
    void setSexe(const std::string& nouveau_sexe);
    void setAge(int nouveau_age);


    //Création du sprite dans le jeu

    //Création des méthodes graphiques
    void render(SDL_Renderer* renderer);
    void setPosition(int x, int y);

    private:
        // La texture SDL représentant l'image de l'animal
    SDL_Texture* m_texture;
    
    // Le rectangle SDL qui définit la position (x, y) et la taille (w, h)
    SDL_Rect m_position;

    // Suppression du constructeur de copie et de l'opérateur d'affectation 
    // pour éviter la duplication non gérée des pointeurs SDL.
    Animal(const Animal&) = delete;
    Animal& operator=(const Animal&) = delete;



    // polymorphisme // Plutard si on veut faire parler l'animal on pourra par exemple
    //virtual void Politesse() const;

};

#endif

