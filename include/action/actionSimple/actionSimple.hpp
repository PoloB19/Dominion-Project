#pragma once

#include "action.hpp"

class ActionSimple : public Action {
    public:
        ActionSimple(std::string nom, unsigned short prix, std::string description) : Action(nom, "ActionSimple", prix, description, 0, 0) {};
        ~ActionSimple();
};