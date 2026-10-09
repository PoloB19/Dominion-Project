#pragma once

#include "tresor.hpp"

class Cuivre : public Tresor {
    public :
        Cuivre() : Tresor("Cuivre", 0, 1) {};
        ~Cuivre();
};