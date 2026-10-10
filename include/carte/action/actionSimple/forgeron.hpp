#pragma once

#include "actionSimple.hpp"

class Forgeron : public ActionSimple {

    public:
        Forgeron();
        ~Forgeron();

        void utiliser(Joueur& J, Plateau& P);
};