#pragma once

#include "action.hpp"

class ActionReaction : public Action {
    public :
        ActionReaction(std::string nom, unsigned short prix, std::string description) : Action(nom, "ActionReaction", prix, description, 0, 0) {};
        ~ActionReaction();
};