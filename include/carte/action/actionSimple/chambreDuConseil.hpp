#pragma once

#include "actionSimple.hpp"

class ChambreDuConseil : public ActionSimple {

    public:
        ChambreDuConseil();
        ~ChambreDuConseil();

        void utiliser(const Plateau& P, size_t idJoueur);

};