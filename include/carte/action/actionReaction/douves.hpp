#pragma once

#include "actionReaction.hpp"

class Douves : public ActionReaction {

    public:
        Douves();
        ~Douves();

        void utiliser(Joueur& J, Plateau& P);};