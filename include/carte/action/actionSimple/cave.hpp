#pragma once

#include "actionSimple.hpp"

class Cave : public ActionSimple {
    public:
        Cave();
        ~Cave();

        void utiliser(Joueur& J, Plateau& P);};