#pragma once

#include "carte.hpp"

#include <string>
class Tresor : public Carte {

    private:
        unsigned short m_valeur;

    public:
        // constructeur
        Tresor(unsigned short prix, std::string description, unsigned short valeur) : Carte(prix, description), m_valeur(valeur){};

        // destructeur
        ~Tresor();

        // obtenir type de la carte
        std::string getCarteType() { return "Tresor"; }

        // obtenir valeur du trésor
        unsigned short getValeur() { return m_valeur; }

};