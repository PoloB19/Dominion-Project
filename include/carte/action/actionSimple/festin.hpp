#pragma once

#include "actionSimple.hpp"

class Festin : public ActionSimple {

    public:
        Festin();
        ~Festin();

        void utiliser(Joueur& J, Plateau& P);
};