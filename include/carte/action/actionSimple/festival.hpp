#pragma once

#include "actionSimple.hpp"

class Festival : public ActionSimple {

    public:
        Festival();
        ~Festival();

        void utiliser(const Plateau& P, size_t idJoueur);

};