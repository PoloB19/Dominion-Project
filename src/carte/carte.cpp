#include "carte.hpp"

unsigned short Carte::m_nextId = 1;

Carte::Carte(std::string nom, std::string type, std::string sousType,unsigned short prix, std::string description, short pointsVictoire, unsigned short valeur) : m_id(m_nextId++), m_nom(nom), m_type(type), m_sousType(sousType), m_prix(prix), m_description(description), m_pointsVictoire(pointsVictoire), m_valeur(valeur) {};

Carte::~Carte() {}

void Carte::utiliser(Joueur& J, Plateau&) {
    J.ajustNbPiece(this->getValeur());
}
