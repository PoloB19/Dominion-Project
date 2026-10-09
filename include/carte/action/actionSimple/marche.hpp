#pragma once

#include "actionSimple.hpp"

class Marche : public ActionSimple {

    public:
        Marche();
        ~Marche();

        void utiliser(const Plateau& P, size_t idJoueur);

};