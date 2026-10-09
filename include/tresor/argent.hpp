#pragma once

#include "tresor.hpp"

class Argent : public Tresor {

    public :
    
        Argent() : Tresor(3, "Trésor Argent", 2) {};
        ~Argent();

};