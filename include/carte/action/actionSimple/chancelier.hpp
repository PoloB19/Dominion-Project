#pragma once

#include "actionSimple.hpp"

class Chancelier : public ActionSimple {

    public:
        Chancelier();
        ~Chancelier();

        void utiliser(const Plateau& P, size_t idJoueur);

};

