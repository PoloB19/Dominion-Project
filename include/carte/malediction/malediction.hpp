#pragma once

#include "carte.hpp"

class Malediction : public Carte {
    public :
        Malediction() : Carte("Malediction", "Malediction", 0, "Retire un point de victoire.", -1, 0) {};
        ~Malediction();
};