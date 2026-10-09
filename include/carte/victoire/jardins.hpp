#pragma once

#include "victoire.hpp"
#include "joueur.hpp"

class Jardins : public Victoire {

    public:
        //Points de victoire à calculer
        Jardins() : Victoire("Jardins", 4, NULL) {};
        ~Jardins();

        short getPointsVictoire(const Joueur& J) const override {
            return (J.getMain().size() + J.getDefausse().size() + J.getPioche().size()) / 10;
        }

};