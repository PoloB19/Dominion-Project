#pragma once

#include <string>
#include <stack>
#include <vector>

#include <iostream>

#include <random>
#include <algorithm>

class Joueur {
    private:
        std::string m_pseudo;

        std::stack<const Carte*> m_pioche;
        std::vector<const Carte*> m_main;
        std::stack<const Carte*> m_defausse;

        unsigned short m_nbAction;
        unsigned short m_nbAchat;
        unsigned short m_monnaie;

    public:
        Joueur(std::string pseudo);
        ~Joueur();
         
        void piocher();
        void acheter(const Carte* carte);
        void defausser(const Carte* carte);
        void ecarter(const Carte* carte);

        void melangerDefausse();
        void resetTour();

        short compterPoints();
};