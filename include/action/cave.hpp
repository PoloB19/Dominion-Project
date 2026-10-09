#pragma once

#include "action.hpp"

class Cave : public Action {

    public:
        Cave();
        ~Cave();

        //On est sûr qu'on fait comme ça?
        //std::string getCarteNom(){return "Mine";}

        void utiliser(const Plateau& P, size_t idJoueur);
};