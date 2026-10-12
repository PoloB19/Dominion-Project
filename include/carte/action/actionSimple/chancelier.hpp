#pragma once

#include "actionSimple.hpp"

class Chancelier : public ActionSimple {

    public:
        Chancelier();
        ~Chancelier();

        void utiliser(Joueur& J, Plateau& P);
};

