#pragma once

#include "actionAttaque.hpp"

class Bureaucrate : public ActionAttaque {
    public:
        Bureaucrate();
        ~Bureaucrate();
        
        void utiliser(Joueur& J, Plateau& P);
};

