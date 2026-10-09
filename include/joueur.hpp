#pragma once

#include <string>
#include <stack>
#include <vector>

#include <iostream>

//Pour mélanger des paquets de cartes
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
        unsigned short m_pieces;

        unsigned short m_nbToursJoues;

    public:
        Joueur(std::string pseudo);
        ~Joueur();

        //Getters
        std::stack<const Carte*> getPioche() const {return m_pioche;}
        std::vector<const Carte*> getMain() const {return m_main;}
        std::stack<const Carte*> getDefausse() const {return m_defausse;}
        unsigned short getNbTourJoues() const {return m_nbToursJoues;}
        unsigned short getTailleDeck() const {return m_pioche.size() + m_main.size() + m_defausse.size();}

        //Setters
        void ajustNbAction(unsigned short delta) {m_nbAction += delta;}
        void ajustNbAchat(unsigned short delta) {m_nbAchat += delta;}
        void ajustNbPiece(unsigned short delta) {m_pieces += delta;}

        //Méthodes
        void piocher(unsigned short nbPioche);
        void defausser(const Carte* cartDefaussee);
        
        void acheter(const Carte* carteAchetee, Plateau& P);
        void ecarter(Carte* carteRebutee, Plateau& P);

        void resetTour();

        void melangerDefausse();

        short compterPoints() const;
};