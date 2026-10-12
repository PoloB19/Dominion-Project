#pragma once

#include "actionSimple.hpp"

class ChambreDuConseil : public ActionSimple {

    public:
        ChambreDuConseil();
        ~ChambreDuConseil();

        void utiliser(Joueur& J, Plateau& P);
};