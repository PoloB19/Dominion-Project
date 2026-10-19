#pragma once

#include <vector>
#include <stack>
#include <map>

#include "composition.hpp"
#include "carte.hpp"
#include "joueur.hpp"

class Carte;

class Plateau {

    private:
        // vecteur qui recense toutes les compositions de partie qui existent
        static std::vector<Composition> m_compositions;

        // A VERIFIER
        std::vector<Joueur*> m_joueurs;
        size_t m_idCompositionPartie;
        std::map<const Carte*, unsigned short> m_piles;
        std::stack<const Carte*> m_rebut;

    public:
        Plateau(std::vector<Joueur*> joueurs, size_t idCompositionPartie);
        ~Plateau();

        //Getters
        static std::vector<Composition> getCompositions() {return m_compositions;}

        std::vector<Joueur*> getJoueurs() {return m_joueurs;}
        size_t getIdCompositionPartie() {return m_idCompositionPartie;}
        std::map<const Carte*, unsigned short> getPiles() {return m_piles;}
        std::stack<const Carte*> getRebut() {return m_rebut;}
        
        //Setters
        static void setCompositions(std::vector<Composition> compositions) {m_compositions = compositions;}

        //Méthodes
        const Carte* getCarteParNom(const std::string& nomCarte) const;
        bool pileEstVide(const Carte* c) const {return m_piles.at(c) == 0;}
        void ajoutRebut(const Carte* carteRebutee);
        void retirerCartePlateau(const Carte* carte);
        bool checkerEndCondition();
        std::vector<Joueur*> determinerGagnant();

};