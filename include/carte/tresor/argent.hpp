#pragma once

#include "tresor.hpp"

class Argent : public Tresor {

    public :
    
        Argent() : Tresor("Argent", 3, "Vaut 2 pièces", 2) {};
        ~Argent() {};
};