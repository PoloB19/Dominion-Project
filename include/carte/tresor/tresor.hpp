#pragma once

#include "carte.hpp"

#include <string>
class Tresor : public Carte {
    public:
        Tresor(std::string nom, unsigned short prix, unsigned short valeur) : Carte(nom, "Tresor", prix, NULL, 0, valeur){};
        ~Tresor();
};