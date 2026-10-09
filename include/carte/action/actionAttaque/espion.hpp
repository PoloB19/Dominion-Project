#pragma once

#include "actionAttaque.hpp"

class Espion : public ActionAttaque {

    public:
        Espion();
        ~Espion();

        void utiliser(const Plateau& P, size_t idJoueur);

};