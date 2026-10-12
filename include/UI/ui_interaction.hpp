#pragma once
#include <string>
#include <iostream>

#include "joueur.hpp"
#include "carte.hpp"


namespace UI {

    const std::string RESET;

    // Police
    const std::string BOLD;
    const std::string UNDERLINE;

    // Couleurs du texte
    const std::string RED;
    const std::string GREEN;
    const std::string YELLOW;
    const std::string BLUE;
    const std::string PURPLE;

    // Utilitaires de terminal
    const std::string CLEAR_SCREEN;

    //Interactions
    bool choixOuiNon(const std::string& message);
    std::string getNomCarte();
    std::vector<size_t> choixParmiCartes(Joueur& J, std::vector<const Carte*> cartes, unsigned short nbChoix);

    void annonceCarteDepuis(std::string nomCarte, Emplacement depuis);
    void annoncerCarteVers(std::string nomCarte, Emplacement vers);
    void annonceRevelerCartes(const Joueur& J, std::vector <const Carte*> cartes);
    void annonceErreur(std::string message);

    // Plus tard
    // int demanderChoix(const std::string& message, int maxChoix);
    // std::string demanderCible(const std::vector<Joueur*>& joueurs);

};
