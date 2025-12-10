#ifndef STATISTIQUE_HPP
#define STATISTIQUE_HPP

class Stats{ //décalaration des statistiques de l'animal
    private:
        float joie;
        float faim;
        float energie;
        float sante;

    public: 
        Stats(); //Création du constructeur, initialisation de l'objet.


        //Getters et le const final est là pour que l'objet ne soit jamais modifier.
        float getJoie() const; //bonheur
        float getFaim() const; //Faim
        float getEnergie() const; //Energie
        float getSante() const; //Santé 

        //shetter Seul façon de modifier les valeurs privées
        void setJoie(float valeur);
        void setFaim(float valeur);
        void setEnergie(float valeur);
        void setSante(float valeur);

        //partie opérateur que je comprend pas bien encore.

};
        


#endif