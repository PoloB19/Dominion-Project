#pragma once

#include <string>
#include <stack>
#include <vector>

#include <iostream>

//Pour mélanger des paquets de carte
#include <random>
#include <algorithm>

class Plateau;
class Carte;
class Joueur {
    private:
        std::string m_pseudo;

        std::stack<const Carte*> m_pioche;
        std::vector<const Carte*> m_main;
        std::stack<const Carte*> m_defausse;

        unsigned short m_nbAction;
        unsigned short m_nbAchat;
        unsigned short m_monnaie;

        unsigned short m_nbToursJoues;

    public:
        Joueur(std::string pseudo);
        ~Joueur();

        //Getters
        unsigned short getNbTourJoues() const {return m_nbToursJoues;}
        unsigned short nbCartesDeck() const;

        //Setters
        void augmenterNbAction() {m_nbAction++;}
        void augmenterNbAchat() {m_nbAchat++;}
        void diminuerNbAction() {m_nbAction--;}
        void diminuerNbAchat() {m_nbAchat--;}

        //Méthodes
        void piocher();
        void defausser(const Carte* cartDefaussee);
        
        void acheter(const Carte* carteAchetee, Plateau& P);
        void ecarter(Carte* carteRebutee, Plateau& P);

        void resetTour();

        void melangerDefausse();

        short compterPoints() const;
};