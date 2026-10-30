#pragma once

#include "actionAttaque.hpp"

class Voleur : public ActionAttaque {
    public :
        Voleur();
        ~Voleur();

        void utiliser(Joueur& J, Plateau& P) const;
};