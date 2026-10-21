#pragma once

#include "carte.hpp"

class Joueur;

class Victoire : public Carte {
    public :
        Victoire(std::string nom, unsigned short prix, std::string description, unsigned short pointsVictoire) : Carte(nom, "Victoire", "", prix, description, pointsVictoire, 0){};
        ~Victoire() {};
};