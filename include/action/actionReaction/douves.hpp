#pragma once

#include "actionReaction.hpp"

class Douves : public ActionReaction {

    public:
        Douves();
        ~Douves();

        void utiliser(const Plateau& P, size_t idJoueur);
};