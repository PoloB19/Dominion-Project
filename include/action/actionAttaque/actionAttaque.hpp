#pragma once

#include "action.hpp"

class ActionAttaque : public Action {

    public :

        ActionAttaque(unsigned short prix, std::string description, unsigned short pointsVictoire, unsigned short valeur);
        ~ActionAttaque();

        // obtenir le type de la carte
        std::string getCarteType() { return "Action_Attaque"; }
};