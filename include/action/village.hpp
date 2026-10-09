#pragma once

#include "action.hpp"

class Village : public Action {

    public:
        Village();
        ~Village();

        //On est sûr qu'on fait comme ça?
        //std::string getCarteNom(){return "Mine";}

        void utiliser(const Plateau& P, size_t idJoueur);
};