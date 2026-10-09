#pragma once

#include "actionSimple.hpp"

class PreteurSurGages : public ActionSimple {

    public:
        PreteurSurGages();
        ~PreteurSurGages();

        void utiliser(const Plateau& P, size_t idJoueur);

};