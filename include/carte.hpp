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
        unsigned short m_pointsVictoire;
        unsigned short m_valeur;
        
    public:
        Carte(std::string nom, std::string type, unsigned short prix, std::string description, unsigned short pointsVictoire, unsigned short valeur) : m_nom(nom), m_type(type), m_prix(prix), m_description(description), m_pointsVictoire(pointsVictoire), m_valeur(valeur), m_id(m_nextId++){};        ~Carte();

        std::string getNom() {return m_nom;}
        std::string getType() {return m_type;}
        
};

//Possible de faire ça?
unsigned short Carte::m_nextId = 1;
