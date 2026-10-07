#pragma once

#include "carte.hpp"

#include <string>
class Tresor : public Carte {

    private:
        unsigned short m_valeur;

    public:
        Tresor(unsigned short prix, std::string description, unsigned short valeur) : Carte(prix, description),m_valeur(valeur){};
        ~Tresor();

};