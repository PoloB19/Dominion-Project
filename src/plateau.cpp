#include "plateau.hpp"

Plateau::Plateau(std::vector<Joueur> joueurs, Composition compositionPartie) : m_joueurs(joueurs), m_compositionPartie(compositionPartie), m_rebuts(std::stack<const Carte*>()), m_piles(std::map<const Carte*, unsigned short>()) {}

