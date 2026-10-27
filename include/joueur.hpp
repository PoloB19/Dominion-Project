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

enum class Emplacement {
    DEFAUSSE,
    MAIN,
    PIOCHE,
    EN_JEU
};

class Joueur {

    friend class Sauvegarde;

    private:

        std::string m_pseudo;

        std::stack<const Carte*> m_pioche;
        std::vector<const Carte*> m_main;
        std::stack<const Carte*> m_defausse;
        std::vector<const Carte*> m_enJeu;

        unsigned short m_nbAction;
        unsigned short m_nbAchat;
        unsigned short m_pieces;

        unsigned short m_nbToursJoues;

    public:
        Joueur(std::string pseudo);
        ~Joueur();

        //Getters
        std::string getPseudo() const {return m_pseudo;}
        std::stack<const Carte*> getPioche() const {return m_pioche;}
        std::vector<const Carte*> getMain() const {return m_main;}
        std::stack<const Carte*> getDefausse() const {return m_defausse;}
        std::vector<const Carte*> getEnJeu() const {return m_enJeu;}

        unsigned short getNbAction() const {return m_nbAction;}
        unsigned short getNbAchat() const {return m_nbAchat;}
        unsigned short getNbPieces() const {return m_pieces;}
        unsigned short getNbTourJoues() const {return m_nbToursJoues;}

        unsigned short getTailleDeck() const {return m_pioche.size() + m_main.size() + m_defausse.size();}

        //Setters
        void ajustNbAction(short delta) {m_nbAction += delta;}
        void ajustNbAchat(short delta) {m_nbAchat += delta;}
        void ajustNbPiece(short delta) {m_pieces += delta;}

        //Méthodes
        bool accesMain() const;
        bool accesDefausse() const;
        bool accesPioche();

        void piocher(unsigned short nbPioche);

        void ajouterAPioche(const Carte* carte);
        void ajouterADefausse(const Carte* carte);
        void ajouterAEnJeu(const Carte* carte);

        bool enleverDepuisMain(const std::string& nomCarte, Emplacement vers);
        
        void obtenirCartePlateau(const Carte* carte, Plateau& P, Emplacement destination);
        void acheter(const Carte* carteAchetee, Plateau& P);
        void ecarter(std::string nomCarteEcartee, Plateau& P, Emplacement depuis, bool actionJoueur = 0);

        void melangerDefausse();

        const Carte* revelerCarte(Emplacement depuis);

        void utiliserCarte(Plateau& P, const Carte* carte);

        bool reagirAttaque(const Carte* attaque, Plateau& P);

        void compterPiecesEnMain(Plateau& P);

        short compterPoints() const;

        void finDeTour();

};