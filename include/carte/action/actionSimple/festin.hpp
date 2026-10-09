#pragma once

#include "actionSimple.hpp"

class Festin : public ActionSimple {

    public:
        Festin();
        ~Festin();

        void utiliser(const Plateau& P, size_t idJoueur);

};