#pragma once

#include "tresor.hpp"

class Cuivre : public Tresor {
    public :
        Cuivre() : Tresor("Cuivre", 0, "Vaut 1 pièce", 1) {};
        ~Cuivre() {};
};