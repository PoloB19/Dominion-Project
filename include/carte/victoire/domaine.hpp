#pragma once

#include "victoire.hpp"

class Domaine : public Victoire {
    public :
        Domaine() : Victoire("Domaine",2 , "Vaut 1 point de victoire",1) {};
        ~Domaine() {};
};