#pragma once

#include "victoire.hpp"

class Jardins : public Victoire {

    public:
        //Points de victoire à calculer
        Jardins() : Victoire("Jardins", 4, NULL) {};
        ~Jardins();

};