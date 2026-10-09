#pragma once

#include <string>
class Carte {

    private:
        static unsigned short m_nextId;
        unsigned short m_id;

        std::string m_type;
        std::string m_nom;
        unsigned short m_prix;
        std::string m_description;
        short m_pointsVictoire;
        unsigned short m_valeur;
        
    public:
        Carte(std::string nom, std::string type, unsigned short prix, std::string description, short pointsVictoire, unsigned short valeur) : m_id(m_nextId++), m_type(type), m_nom(nom), m_prix(prix), m_description(description), m_pointsVictoire(pointsVictoire), m_valeur(valeur) {};
        ~Carte();

        std::string getNom() const {return m_nom;}
        std::string getType() const {return m_type;}
        short getPointsVictoire() const {return m_pointsVictoire;}
        
};
