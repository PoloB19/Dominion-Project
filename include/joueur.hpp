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

        static unsigned short m_nextId;
        unsigned short m_idJoueur;

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
        unsigned short getId() const {return m_idJoueur;}
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
        void ajustNbAction(unsigned short delta) {m_nbAction += delta;}
        void ajustNbAchat(unsigned short delta) {m_nbAchat += delta;}
        void ajustNbPiece(unsigned short delta) {m_pieces += delta;}

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
        void ecarter(std::string nomCarteEcartee, Plateau& P, bool phaseAction = 0);

        void melangerDefausse();

        const Carte* revelerCarte(Emplacement depuis);

        void utiliserCarte(Plateau& P, const Carte* carte);

        bool reagirAttaque(const Carte& attaque, Plateau& P);

        void compterPiecesEnMain(Plateau& P);

        short compterPoints() const;

        void finDeTour();

        //Interactions
        bool demanderOuiNon(const std::string& question) const;
        std::string demanderNomCarte() const;
        std::vector<size_t> choixParmiCartes(std::vector<const Carte*> cartes, unsigned short nbChoix);

        void annonceCarteDepuis(std::string nomCarte, Emplacement depuis) const ;
        void annonceCarteVers(std::string nomCarte, Emplacement vers) const ;
        void annonceRevelerCartes(std::vector<const Carte*> cartes) const ;
        void annonceErreur(std::string message) const ;

        bool operator== (const Joueur& J) const {return m_idJoueur == J.m_idJoueur;}
};