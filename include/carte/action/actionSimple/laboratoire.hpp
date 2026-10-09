#pragma once

#include "actionSimple.hpp"

#include <string>

class Laboratoire : public ActionSimple {
    public:
        Laboratoire();
        ~Laboratoire();

        void utiliser(Joueur& J, Plateau& P);};