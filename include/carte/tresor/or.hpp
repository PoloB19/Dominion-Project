#pragma once

#include "tresor.hpp"

class Or : public Tresor {
    public :
        Or() : Tresor("Or", 6, "Vaut 3 pièces", 3){};
        ~Or() {};
};