#pragma once

#include "actionSimple.hpp"

class Bucheron : public ActionSimple {
    public:
        Bucheron();
        ~Bucheron();

        void utiliser(const Plateau& P, size_t idJoueur);
};