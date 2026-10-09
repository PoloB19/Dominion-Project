#pragma once

#include "actionSimple.hpp"

class SalleDuTrone : public ActionSimple {

    public:
        SalleDuTrone();
        ~SalleDuTrone();

        void utiliser(const Plateau& P, size_t idJoueur);

};