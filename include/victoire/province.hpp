#pragma once

#include "victoire.hpp"

class Province : public Victoire {

    public :
        // constructeur
        Province() : Victoire(8, "Victoire province", 6) {};

        // destructeur
        ~Province();

        // obtenir nom de la carte
        std::string getCarteNom() { return "Province"; }
};