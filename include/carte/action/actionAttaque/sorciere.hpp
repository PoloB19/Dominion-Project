#pragma once

#include "actionAttaque.hpp"

class Sorciere : public ActionAttaque {

    public:
        Sorciere();
        ~Sorciere();

        void utiliser(Joueur& J, Plateau& P);
};