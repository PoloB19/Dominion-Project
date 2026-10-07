#pragma once

#include <vector>
#include <stack>
#include <map>

#include "carte.hpp"
#include "composition.hpp"
#include "joueur.hpp"

class Plateau {

    private:
        std::vector<Joueur> m_joueurs;
        Composition m_compositionPartie;
        std::stack<const Carte*> m_rebuts;
        std::map<const Carte*, unsigned short> m_piles;

    public:
        Plateau(std::vector<Joueur> joueurs, Composition compositionPartie);
        ~Plateau();


};