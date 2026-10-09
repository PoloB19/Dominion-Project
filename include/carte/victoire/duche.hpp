#pragma once

#include "victoire.hpp"

class Duche : public Victoire {
    public :
        Duche() : Victoire("Duche", 5, 3) {};
        ~Duche();
};