#pragma once

#include <vector>
#include <stack>
#include <map>

#include "composition.hpp"
#include "carte.hpp"
#include "joueur.hpp"

class Plateau {

    private:
        // vecteur qui recense toutes les compositions de partie qui existent
        static std::vector<const Composition*> m_compositions;

        std::vector<const Joueur*> m_joueurs;
        size_t m_idCompositionPartie;
        std::map<const Carte*, unsigned short> m_piles;
        std::stack<const Carte*> m_rebut;

    public:
        Plateau(std::vector<const Joueur*> joueurs, size_t idCompositionPartie);
        ~Plateau();

        //Getters
        static std::vector<const Composition*> getCompositions() {return m_compositions;}
        std::vector<const Joueur*> getJoueurs() {return m_joueurs;}

        //Setters
        static void setCompositions(std::vector<const Composition*> compositions) {m_compositions = compositions;}

        //Méthodes
        void ajoutRebut(const Carte* carteRebutee);
        void retirerCartePlateau(const Carte* carteAchetee);
        bool checkerEndCondition();
        std::vector<Joueur> determinerGagnant();

};