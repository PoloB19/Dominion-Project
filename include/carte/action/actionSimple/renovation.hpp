#pragma once

#include "actionSimple.hpp"

class Renovation : public ActionSimple {

    public:
        Renovation();
        ~Renovation();

        void utiliser(const Plateau& P, size_t idJoueur);

};