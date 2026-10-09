#pragma once

#include <string>

class Carte {

    private:
        static unsigned short m_nextId;
        unsigned short m_id;
        unsigned short m_prix;
        std::string m_description;
        unsigned short m_pointsVictoire;
        unsigned short m_valeur;

    public:
        Carte(unsigned short prix, std::string description, unsigned short pointsVictoire, unsigned short valeur);
        ~Carte();

        virtual std::string getCarteType() const = 0;
        
};
