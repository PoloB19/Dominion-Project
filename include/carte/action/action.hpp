#pragma once

#include "carte.hpp"
#include "plateau.hpp"

class Action : public Carte {

    public:

        Action(std::string nom, std::string type, unsigned short prix, std::string description, unsigned short pointsVictoire, unsigned short valeur) : Carte(nom, type, prix, description, pointsVictoire, valeur) {};
        ~Action();

        virtual void utiliser(Joueur& J, Plateau& P) = 0;

};