#pragma once

#include "actionAttaque.hpp"

class Sorciere : public ActionAttaque {

    public:
        Sorciere();
        ~Sorciere();

        void utiliser(const Plateau& P, size_t idJoueur);

};