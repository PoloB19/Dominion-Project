#pragma once

#include "actionSimple.hpp"

class Cave : public ActionSimple {
    public:
        Cave();
        ~Cave();

        void utiliser(const Plateau& P, size_t idJoueur);
};