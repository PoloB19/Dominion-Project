#pragma once

#include "action.hpp"
#include "joueur.hpp"

#include <string>
class Laboratoire : public Action {
    public:

        Laboratoire();
        ~Laboratoire();

        //On est sûr qu'on fait comme ça?
        std::string getCarteNom(){return "Laboratoire";}

        void utiliser(const Plateau& P, size_t idJoueur);
};