#pragma once

#include "actionAttaque.hpp"

class Espion : public ActionAttaque {

    public:
        Espion();
        ~Espion();

        void utiliser(Joueur& J, Plateau& P);
};