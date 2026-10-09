#pragma once

#include "action.hpp"

class ActionAttaque : public Action {

    public :
        // obtenir le type de la carte
        std::string getCarteType() { return "Action_Attaque"; }
};