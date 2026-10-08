#pragma once

#include "tresor.hpp"

class Cuivre : public Tresor {

    public :
        // constructeur
        Cuivre() : Tresor(1, "Trésor Cuivre", 1) {};

        // destucteur
        ~Cuivre();

        // obtenir type de la carte
        std::string getCarteNom() { return "Cuivre"; }
};