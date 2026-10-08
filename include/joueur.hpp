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

        unsigned short m_nbTourJoues;

    public:
        Joueur(std::string pseudo);
        ~Joueur();

        unsigned short getNbTourJoues() {return m_nbTourJoues;}
         
        void piocher();
        void defausser(const Carte* cartDefaussee);
        void acheter(const Carte* carteAchetee, Plateau &P);
        void ecarter(Carte* carteRebutee, Plateau& P);

        void melangerDefausse();
        void resetTour();

        short compterPoints();
};