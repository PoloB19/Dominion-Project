#pragma once

#include "actionSimple.hpp"

class Bucheron : public ActionSimple {
    public:
        Bucheron();
        ~Bucheron();

        void utiliser(Joueur& J, Plateau& P);};