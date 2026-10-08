#pragma once

#include "victoire.hpp"

class Domaine : public Victoire {

    public :
        // constructeur
        Domaine() : Victoire(2, "Victoire domaine", 1) {};

        // destructeur
        ~Domaine();

        // obtenir nom de la carte
        std::string getCarteNom() { return "Domaine"; }
};