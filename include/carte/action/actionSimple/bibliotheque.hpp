#pragma once

#include "actionSimple.hpp"

class Bibliotheque : public ActionSimple {

    public:
        Bibliotheque();
        ~Bibliotheque();

        void utiliser(const Plateau& P, size_t idJoueur);

};