#pragma once

#include "actionSimple.hpp"

class PreteurSurGages : public ActionSimple {

    public:
        PreteurSurGages();
        ~PreteurSurGages();

        void utiliser(Joueur& J, Plateau& P);
};