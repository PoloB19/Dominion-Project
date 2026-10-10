#pragma once

#include "actionSimple.hpp"

class Marche : public ActionSimple {

    public:
        Marche();
        ~Marche();

        void utiliser(Joueur& J, Plateau& P);
};