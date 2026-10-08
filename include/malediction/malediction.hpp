#pragma once

#include "carte.hpp"

class Malédiction : public Carte {

    public :
        // obtenir type de la carte
        std::string getCarteType() { return "Malediction"; }
};