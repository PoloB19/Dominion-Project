#pragma once

#include "tresor.hpp"

class Argent : public Tresor {

    public :
    
        Argent() : Tresor("Argent", 3, 2) {};
        ~Argent();

};