#pragma once

#include <string>
#include <stack>
#include <vector>

class Joueur {
    private:
        std::string m_pseudo;
        std::stack<const Carte*> m_pioche;
        std::vector<const Carte*> m_main;
        std::stack<const Carte*> m_defausse;

        unsigned short m_nbAction;
        unsigned short m_nbAchat;

    public:
        Joueur(std::string pseudo);
};