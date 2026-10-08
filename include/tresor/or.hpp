#pragma once

#include "tresor.hpp"

class Or : public Tresor {

    public :
        // constructeur
        Or() : Tresor(6, "Trésor Or", 3){};

        // destucteur
        ~Or();

        // obtenir type de la carte
        std::string getCarteNom() { return "Or"; }

};