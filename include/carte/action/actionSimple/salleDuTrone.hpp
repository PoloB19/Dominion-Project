#pragma once

#include "actionSimple.hpp"

class SalleDuTrone : public ActionSimple {

    public:
        SalleDuTrone();
        ~SalleDuTrone();

        void utiliser(Joueur& J, Plateau& P);
};