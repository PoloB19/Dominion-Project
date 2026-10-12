#pragma once

#include "actionSimple.hpp"

class Chapelle : public ActionSimple {

    public:
        Chapelle();
        ~Chapelle();

        void utiliser(Joueur& J, Plateau& P);
};