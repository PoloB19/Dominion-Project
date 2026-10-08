#pragma once

#include "action.hpp"

class ActionRéaction : public Action {
    
    public :
        // obtenir le type de la carte
        std::string getCarteType() { return "Action_Reaction"; }
};