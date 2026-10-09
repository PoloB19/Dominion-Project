#pragma once

#include "actionAttaque.hpp"

class Milice : public ActionAttaque {

    public :
        // obtenir nom de la carte
        std::string getCarteNom() { return "Milice"; }
};