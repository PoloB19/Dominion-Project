#pragma once

#include "actionAttaque.hpp"

class Milice : public ActionAttaque {

    public :

        Milice();
        ~Milice();

        void utiliser(const Plateau& P, size_t idJoueur);
};