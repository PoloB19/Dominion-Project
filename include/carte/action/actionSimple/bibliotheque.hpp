#pragma once

#include "actionSimple.hpp"

class Bibliotheque : public ActionSimple {

    public:
        Bibliotheque();
        ~Bibliotheque();

        void utiliser(Joueur& J, Plateau& P);
};