#pragma once

#include "actionSimple.hpp"

class Festival : public ActionSimple {

    public:
        Festival();
        ~Festival();

        void utiliser(Joueur& J, Plateau& P);
};