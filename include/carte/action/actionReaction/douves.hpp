#pragma once

#include "actionReaction.hpp"

class Douves : public ActionReaction {
    public:
        Douves();
        ~Douves();

        void utiliser(Joueur& , Plateau& ) const;
        bool reagir(Joueur& cible, const Carte* carteAttaque, Plateau&) const;
};