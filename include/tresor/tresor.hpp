#pragma once

#include "carte.hpp"

#include <string>
class Tresor : public Carte {

    public:
        Tresor(std::string nom, std::string type, unsigned short prix, std::string description, unsigned short pointsVictoire, unsigned short valeur) : Carte(std::string nom, std::string type, unsigned short prix, std::string description, unsigned short pointsVictoire, unsigned short valeur){};
        ~Tresor();

};