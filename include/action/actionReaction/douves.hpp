#pragma once

#include "actionReaction.hpp"

class Douves : public ActionReaction {

    public:
        Douves();
        ~Douves();

        //On est sûr qu'on fait comme ça?
        //std::string getCarteNom(){return "Mine";}

        void utiliser(const Plateau& P, size_t idJoueur);
};