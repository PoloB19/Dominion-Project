#pragma once

#include "actionSimple.hpp"

class Mine : public ActionSimple {

    public:
        Mine();
        ~Mine();
        
        void utiliser(Joueur& J, Plateau& P);};