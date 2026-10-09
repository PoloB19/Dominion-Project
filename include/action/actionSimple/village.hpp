#pragma once

#include "actionSimple.hpp"

class Village : public ActionSimple {

    public:
        Village();
        ~Village();

        void utiliser(const Plateau& P, size_t idJoueur);
};