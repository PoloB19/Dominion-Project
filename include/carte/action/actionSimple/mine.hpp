#pragma once

#include "actionSimple.hpp"

class Mine : public ActionSimple {

    public:
        Mine();
        ~Mine();
        
        void utiliser(const Plateau& P, size_t idJoueur);
};