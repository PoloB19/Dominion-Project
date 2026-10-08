#pragma once

#include "carte.hpp"

class Action : public Carte {

    private:


    public:
        virtual void utiliser() = 0;

        // obtenir le type de la carte
        virtual std::string getCarteType() { return "Action"; }

};