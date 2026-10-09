#pragma once

#include "action.hpp"

class ActionAttaque : public Action {
    public :
        ActionAttaque(std::string nom, unsigned short prix, std::string description) : Action(nom, "ActionAttaque", prix, description, 0, 0) {};
        ~ActionAttaque();
};