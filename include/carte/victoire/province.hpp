#pragma once

#include "victoire.hpp"

class Province : public Victoire {

    public :
        Province() : Victoire("Province", 8, "Vaut 6 points de victoire", 6) {};
        ~Province() {};
};