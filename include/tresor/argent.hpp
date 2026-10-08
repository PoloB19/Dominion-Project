#pragma once

#include "tresor.hpp"

class Argent : public Tresor {

    public :
        // constructeur
        Argent() : Tresor(3, "Trésor Argent", 2) {};

        // destucteur
        ~Argent();

        // obtenir type de la carte
        std::string getCarteNom() { return "Argent"; }
};