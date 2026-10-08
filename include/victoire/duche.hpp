#pragma once

#include "victoire.hpp"

class Duche : public Victoire {

    public :
        // constructeur
        Duche() : Victoire(5, "Victoire duché", 3) {};

        // destructeur
        ~Duche();

        // obtenir nom de la carte
        std::string getCarteNom() { return "Duche"; }
};