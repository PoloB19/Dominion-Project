#pragma once

#include "tresor.hpp"

class Or : public Tresor {

    public:
        Or() : Tresor(6, "Trésor Or", 3){};
        ~Or();

};