#pragma once

#include "carte.hpp"

class Joueur;

class Victoire : public Carte {
    public :
        Victoire(std::string nom, unsigned short prix, unsigned short pointsVictoire) : Carte(nom, "Victoire", prix, NULL, pointsVictoire, 0){};
        ~Victoire();

        short getPointsVictoire(const Joueur& J) const override {
            Carte::getPointsVictoire(J);
        }
};