#pragma once

#include "actionSimple.hpp"

class Renovation : public ActionSimple {

    public:
        Renovation();
        ~Renovation();

        void utiliser(Joueur& J, Plateau& P);
};