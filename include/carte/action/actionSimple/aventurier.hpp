#pragma once

#include "actionSimple.hpp"

class Aventurier : public ActionSimple {

    public:
        Aventurier();
        ~Aventurier();

        void utiliser(Joueur& J, Plateau& P);
};