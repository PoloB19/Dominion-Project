#pragma once

#include "victoire.hpp"

class Duche : public Victoire {
    public :
        Duche() : Victoire("Duche", 5, "Vaut 3 points de victoire", 3) {};
        ~Duche() {};
};