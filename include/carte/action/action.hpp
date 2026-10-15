#pragma once

#include "carte.hpp"
#include "plateau.hpp"

class Action : public Carte {

    public:

        Action(std::string nom, std::string sousType, unsigned short prix, std::string description, unsigned short pointsVictoire, unsigned short valeur) : Carte(nom, "Action", sousType, prix, description, pointsVictoire, valeur) {};
        ~Action() {};

};