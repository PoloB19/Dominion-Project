#pragma once

#include "actionAttaque.hpp"

class Bureaucrate : public ActionAttaque {
    public:
        Bureaucrate();
        ~Bureaucrate();
        
        void utiliser(const Plateau& P, size_t idJoueur);
};

