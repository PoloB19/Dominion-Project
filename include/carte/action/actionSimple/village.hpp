#pragma once

#include "actionSimple.hpp"

class Village : public ActionSimple {
    public:
        Village();
        ~Village();

        void utiliser(Joueur& J, Plateau& P);
};