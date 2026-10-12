#pragma once

#include "actionAttaque.hpp"

class Milice : public ActionAttaque {
    public :
        Milice();
        ~Milice();

        void utiliser(Joueur& J, Plateau& P);};