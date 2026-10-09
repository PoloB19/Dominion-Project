#pragma once

#include "victoire.hpp"

class Province : public Victoire {

    public :
        Province() : Victoire("Province", 8, 6) {};
        ~Province();
};