#pragma once

#include "actionSimple.hpp"

class Forgeron : public ActionSimple {

    public:
        Forgeron();
        ~Forgeron();

        void utiliser(const Plateau& P, size_t idJoueur);

};