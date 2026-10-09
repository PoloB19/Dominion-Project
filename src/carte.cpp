#include "carte.hpp"

unsigned short Carte::m_nextId = 1;

Carte::Carte(std::string nom, std::string type, unsigned short prix, std::string description, unsigned short pointsVictoire, unsigned short valeur) : m_nom(nom), m_type(type), m_prix(prix), m_description(description), m_pointsVictoire(pointsVictoire), m_valeur(valeur), m_id(m_nextId++){};

//CLASSE INUTILE?