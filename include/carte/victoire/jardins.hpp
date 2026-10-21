#pragma once

#include "victoire.hpp"
#include "joueur.hpp"

class Jardins : public Victoire {

    public:
        Jardins() : Victoire("Jardins", 4, "Vaut 1 point de victoire pour chaque 10 cartes dans votre deck (arrondi à l'unité inférieure)", 0) {};
        ~Jardins() {};

        short getPointsVictoire(const Joueur& J) const override {
            return J.getTailleDeck() / 10;
        }

};