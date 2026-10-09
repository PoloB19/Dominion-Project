#pragma once

#include "action.hpp"

class Mine : public Action {

    public:
        Mine();
        ~Mine();

        //On est sûr qu'on fait comme ça?
        //std::string getCarteNom(){return "Mine";}

        void utiliser(const Plateau& P, size_t idJoueur);
};