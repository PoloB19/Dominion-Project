#pragma once

#include "carte.hpp"

class Victoire : public Carte {

    private :
        unsigned short m_pointsVictoire;

    public :
        //constructeur
        Victoire(unsigned short prix, std::string description, unsigned short pointsVictoire) : Carte(prix, description), m_pointsVictoire(pointsVictoire) {};

        //destucteur
        ~Victoire();

        // obtenir type de la carte
        std::string getCarteType() { return "Victoire"; }

        // getters
        unsigned short getPointsVictoire() { return m_pointsVictoire; }

};