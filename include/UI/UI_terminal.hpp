#pragma once
#include <string>
#include <iostream>
#include <ranges>

#include "plateau.hpp"
#include "joueur.hpp"
#include "carte.hpp"
#include "listeCartes.hpp"


namespace UI {

    // Constantes et variables diverses
    const size_t longueurMaxLigne = 50;

    std::vector<std::string> listeChoix;
    std::string choix0;

    std::string input;

   // Annule tous les styles
    const std::string RESET = "\033[0m";

    // Police
    const std::string BOLD = "\033[1m";
    const std::string ITALIC = "\033[3m";
    const std::string UNDERLINE = "\033[4m";

    // Couleurs du texte
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string PURPLE = "\033[35m";
    const std::string CYAN = "\033[36m";

    // Utilitaires de terminal
    const std::string CLEAR_SCREEN = "\033[2J\033[H";

    // Affichage

        // Écrans
        size_t ecranAccueil();

        size_t ecranNouvellePartie();

        size_t ecranCreationComposition();

        std::vector<std::string> ecranChoixJoueurs();

        bool ecranModeRapide();



        // Onglets
        std::vector<size_t> ongletChoixCartesComposition(Joueur &J);
        size_t ongletChoixAleatoireCartesComposition();
        size_t ongletDescriptionCartes(const std::vector<const Carte*>& cartes);



    // Annonces 
    void annonceCarteDepuis(std::string nomCarte, Emplacement depuis);
    void annonceCarteVers(std::string nomCarte, Emplacement vers);
    void annonceRevelerCartes(const Joueur& J, std::vector <const Carte*> cartes);
    void annonceErreur(const std::string& message);

    // Outils
    void retourALigne();
    void sautDeLigne();
    void separateursTitre();
    void separateursChoix();
    void clearScreen();
    void afficherInformation(const std::string& info);
    void afficherTitre(const std::string& titre);
    void afficherListeCarteParNom(std::vector<const Carte*> listeCartes);

    //Choix
    size_t choixParmiChiffre(const std::vector<std::string>& listeChoix, const std::string& choix0 = "");

    std::vector<size_t> choixParmiCartes(Joueur& J, const std::vector<const Carte*> cartes, unsigned short nbChoix, std::string choix0 = "");

    bool choixOuiNon(const std::string& question);
};
