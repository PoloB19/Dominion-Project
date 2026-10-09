#pragma once

#include "actionSimple.hpp"

class Atelier : public ActionSimple {

    public:
        Atelier();
        ~Atelier();

        void utiliser(const Plateau& P, size_t idJoueur);

};