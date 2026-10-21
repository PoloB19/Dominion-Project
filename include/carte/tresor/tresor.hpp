#pragma once

#include "carte.hpp"

#include <string>
class Tresor : public Carte {
    public:
        Tresor(std::string nom, unsigned short prix, std::string description, unsigned short valeur) : Carte(nom, "Tresor", "", prix, description, 0, valeur){};
        ~Tresor() {};
};