#pragma once

#include "victoire.hpp"
#include "joueur.hpp"

class Jardins : public Victoire {

    public:
        Jardins() : Victoire("Jardins", 4, NULL) {};
        ~Jardins();

        short getPointsVictoire(const Joueur& J) const override {
            return J.getTailleDeck() / 10;
        }

};