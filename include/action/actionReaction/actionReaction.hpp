#pragma once

#include "action.hpp"

class ActionReaction : public Action {
    
    public :

    ActionReaction(unsigned short prix, std::string description, unsigned short pointsVictoire, unsigned short valeur);
    ~ActionReaction();

    // obtenir le type de la carte
    std::string getCarteType() { return "Action_Reaction"; }
};