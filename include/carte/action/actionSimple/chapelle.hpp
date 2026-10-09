#pragma once

#include "actionSimple.hpp"

class Chapelle : public ActionSimple {

    public:
        Chapelle();
        ~Chapelle();

        void utiliser(const Plateau& P, size_t idJoueur);

};