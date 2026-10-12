#pragma once

#include "actionSimple.hpp"

class Atelier : public ActionSimple {

    public:
        Atelier();
        ~Atelier();

        void utiliser(Joueur& J, Plateau& P);
};