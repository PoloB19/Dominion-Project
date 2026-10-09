#pragma once

#include "actionSimple.hpp"

class Aventurier : public ActionSimple {

    public:
        Aventurier();
        ~Aventurier();

        void utiliser(const Plateau& P, size_t idJoueur);

};