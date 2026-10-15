#pragma once
#include <string>
#include <iostream>

#include "joueur.hpp"
#include "carte.hpp"


namespace UI {

   // Annule tous les styles
    const std::string RESET = "\033[0m";

    // Police
    const std::string BOLD = "\033[1m";
    const std::string UNDERLINE = "\033[4m";

    // Couleurs du texte
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string PURPLE = "\033[35m";

    // Utilitaires de terminal
    const std::string CLEAR_SCREEN = "\033[2J\033[H";

    // Interactions
    bool choixOuiNon(const std::string& message);
    std::string getNomCarte();
    std::vector<size_t> choixParmiCartes(Joueur& J, std::vector<const Carte*> cartes, unsigned short nbChoix);

    // Affichage
    void afficherDemarrage();

    // Annonces 
    void annonceCarteDepuis(std::string nomCarte, Emplacement depuis);
    void annonceCarteVers(std::string nomCarte, Emplacement vers);
    void annonceRevelerCartes(const Joueur& J, std::vector <const Carte*> cartes);
    void annonceErreur(std::string message);

    // Outils
    void retourALigne();
    void sautDeLigne();
    void separateurs();
    void separateurTitre(std::string& titre);


    // Plus tard
    // int demanderChoix(const std::string& message, int maxChoix);
    // std::string demanderCible(const std::vector<Joueur*>& joueurs);

};
