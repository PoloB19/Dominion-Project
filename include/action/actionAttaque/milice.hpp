#pragma once

#include "actionAttaque.hpp"

class Milice : public ActionAttaque {

    public :

        Milice();
        ~Milice();

        //On est sûr qu'on fait comme ça?
        //std::string getCarteNom(){return "Milice";}

        void utiliser(const Plateau& P, size_t idJoueur);
};