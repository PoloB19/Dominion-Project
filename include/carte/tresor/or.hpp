#pragma once

#include "tresor.hpp"

class Or : public Tresor {
    public :
        Or() : Tresor("Or", 6, 3){};
        ~Or();
};