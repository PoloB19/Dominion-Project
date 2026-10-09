#pragma once

#include "carte.hpp"
#include "plateau.hpp"

class Action : public Carte {

    private:


    public:

        Action(unsigned short prix, std::string description, unsigned short pointsVictoire, unsigned short valeur);
        ~Action();

        virtual void utiliser(const Plateau& P, size_t idJoueur) = 0;

        // obtenir le type de la carte
        virtual std::string getCarteType() { return "Action"; }

};