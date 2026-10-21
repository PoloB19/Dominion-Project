#pragma once

#include <vector>
#include <stack>
#include <map>
#include <string>

#include "composition.hpp"
#include "carte.hpp"
#include "joueur.hpp"

class Carte;

class Plateau {

    private:
        // vecteur qui recense toutes les compositions de partie qui existent
        static std::vector<Composition> m_compositions;

        std::vector<Joueur> m_joueurs;
        size_t m_idCompositionPartie;
        std::map<const Carte*, unsigned short> m_piles;
        std::stack<const Carte*> m_rebut;

    public:
        Plateau(std::vector<std::string> joueurs, size_t idCompositionPartie);
        ~Plateau();

        //Getters
        static std::vector<Composition> getCompositions() {return m_compositions;}

        std::vector<Joueur>& getJoueurs() {return m_joueurs;}
        const std::vector<Joueur>& getJoueurs() const {return m_joueurs;}
        size_t getIdCompositionPartie() const {return m_idCompositionPartie;}
        const std::map<const Carte*, unsigned short>& getPiles() const {return m_piles;}
        std::stack<const Carte*> getRebut() const {return m_rebut;}
        
        //Setters
        static void setCompositions(std::vector<Composition> compositions) {m_compositions = compositions;}

        //Méthodes
        static void addComposition(Composition composition) {m_compositions.push_back(composition);}

        const Carte* getCarteParNom(const std::string& nomCarte) const;
        bool pileEstVide(const Carte* c) const {return m_piles.at(c) == 0;}
        void ajoutRebut(const Carte* carteRebutee);
        void retirerCartePlateau(const Carte* carte);
        bool checkerEndCondition();
        std::vector<Joueur*> determinerGagnant();
        void setModeRapide();

};