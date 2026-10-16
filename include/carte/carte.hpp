#pragma once

#include <string>

class Plateau;
class Joueur;

class Carte {

    private:
        static unsigned short m_nextId;
        unsigned short m_id;

        std::string m_nom;
        std::string m_type;
        std::string m_sousType;
        unsigned short m_prix;
        std::string m_description;
        short m_pointsVictoire;
        unsigned short m_valeur;
        
    public:
        Carte(std::string nom, std::string type, std::string sousType,unsigned short prix, std::string description, short pointsVictoire, unsigned short valeur);
        ~Carte();

        // Getters
        std::string getNom() const {return m_nom;}
        std::string getType() const {return m_type;}
        std::string getSousType() const {return m_sousType;}
        unsigned short getPrix() const {return m_prix;}
        std::string getDescription() const {return m_description;}
        virtual short getPointsVictoire(const Joueur&) const {return m_pointsVictoire;}
        unsigned short getValeur() const {return m_valeur;}

        // Méthode
        virtual void utiliser(Joueur& J, Plateau&);
        
};