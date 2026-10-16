#include "UI_terminal.hpp"

// Outils
void UI::retourALigne() {
    std::cout << std::endl;
}

void UI::sautDeLigne() {
    std::cout << std::endl << std::endl;
}

void UI::separateursTitre() {
    std::cout << std::string(longueurMaxLigne, '~');
}

void UI::separateursChoix() {
    std::cout << std::string(longueurMaxLigne, '-');
}

void UI::clearScreen() {
    std::cout << CLEAR_SCREEN << RESET;
}

void UI::afficherInformation(const std::string& info) {
    std::cout << info;
}

void UI::afficherTitre(const std::string& titre) {

    size_t tailleTitre = titre.length() + 2;

    // Si le titre est trop grand
    if (tailleTitre + 6 > longueurMaxLigne) {
        std::cout << "§ " << titre << " §";
        return;
    }

    // Place disponible pour UN côté (gauche ou droite)
    size_t espaceParCote = (longueurMaxLigne - tailleTitre) / 2;

    std::string coteGauche;
    std::string coteDroit;

    // Il faut au moins 11 caractères par côté pour que §~~~~§~~~~§ soit joli
    if (espaceParCote >= 11) {
        size_t nbTildesTotal = espaceParCote - 3; // pour mettre §
        size_t tildesBloc1 = nbTildesTotal / 2;
        size_t tildesBloc2 = nbTildesTotal - tildesBloc1;

        coteGauche = "§" + std::string(tildesBloc1, '~') + "§" + std::string(tildesBloc2, '~') + "§";
        coteDroit  = "§" + std::string(tildesBloc2, '~') + "§" + std::string(tildesBloc1, '~') + "§";
    }

    // Si le titre est trop long : motif simple "§~~~~§"
    else {

        size_t nbTildes = espaceParCote - 2; // pour mettre §
        
        coteGauche = "§" + std::string(nbTildes, '~') + "§";
        coteDroit  = coteGauche;
    }

    std::cout << coteGauche << " " << titre << " " << coteDroit;
}

void UI::afficherListeCarteParNom(std::vector<const Carte*> listeCartes) {

    std::cout << "[";

    for (size_t i = 0; i < listeCartes.size(); i++) {
        std::cout << listeCartes.at(i);
        if(i != listeCartes.size() - 1 ){
            std::cout << ", ";
        }
    }

    std::cout << "]";

}

// Choix

size_t UI::choixParmiChiffre(const std::vector<std::string>& listeChoix, const std::string& choix0) {

    for (size_t i = 0; i < listeChoix.size(); i++){
        std::cout << i+1 << " : " << listeChoix.at(i);
        retourALigne();
    }

    if (!choix0.empty()) {
        std::cout << "0 : " << choix0;
        retourALigne();
    }

    while (true) {

        retourALigne();
        separateursChoix();
        std::cout << "> ";
        std::cin >> input;
        retourALigne();

        if(input.length() != 1 || !std::isdigit(input.at(0))) {
            annonceErreur("veuillez entrer un chiffre valide");
            retourALigne();
            continue;
        }

        size_t inputValeur = input.at(0) - '0'; //transforme la saisie en nombre

        if (inputValeur > listeChoix.size() || (inputValeur == 0 && choix0.empty())) {
            annonceErreur("le choix '" + input + "' n'existe pas." );
            retourALigne();
            continue;
        }

        return inputValeur;

    }
}

std::vector<size_t> UI::choixParmiCartes(Joueur& J, const std::vector<const Carte*> cartes, unsigned short nbChoix, std::string choix0) {

    afficherInformation(J.getPseudo() + ", choisissez " + std::to_string(nbChoix) + " carte(s) parmi :");
    retourALigne();

    std::cout << "[ ";
    for (const Carte* c : cartes){
        std::cout << c->getNom() + " ";
    }
    std::cout << " ]";
    
    sautDeLigne();

    if(!choix0.empty()){ 
        std::cout << "0 : " + choix0;
        retourALigne();
    }
        
    separateursChoix();

    std::vector<size_t> idChoix = {};
    while (idChoix.size() < nbChoix){
        
        std::cout << "> ";
        std::cin >> input;

        // Si choix0 est possible et demandé
        if(!choix0.empty() && input.at(0) - '0' == 0) return {};

        // Vérifie que la sélection est possible
        for (size_t i = 0; i < cartes.size(); i++){

            // Vérifie que la carte est proposée 
            if (cartes.at(i)->getNom() == input){

                for(size_t j : idChoix){

                    // Vérifie que la carte n'a pas déjà été sélectionnée
                    if (i == j){
                        annonceErreur("cette carte a déjà été sélectionnée");
                        sautDeLigne();
                        continue;
                    }
                }

                idChoix.push_back(i);
                continue;

            }
        }

        annonceErreur("cette carte n'est pas proposée");
        sautDeLigne();

    }

    return idChoix;

}

bool UI::choixOuiNon(const std::string& question) {

    while (true) {

        afficherInformation(question);
        separateursChoix();
        retourALigne();
        std::cout << " > ";
        std::cin >> input;
        
        if (input == "O" || input == "o" || input == "Oui" || input == "oui" || input == "OUI") return true;
        if (input == "N" || input == "n" || input == "Non" || input == "non" || input == "NON") return false;
        
        //retourALigne(); ?
        annonceErreur("veuillez répondre par 'oui' ou 'non'");

        sautDeLigne();

    }
}

// Afffichage

// Écrans

size_t UI::ecranAccueil() {

    clearScreen();
    afficherTitre("DOMINION");

    sautDeLigne();

    std::cout << "Bienvenue sur ce deck builder médiéval.";
    retourALigne();
    std::cout << "Votre royaume commence ici !";

    sautDeLigne();

    separateursTitre();

    sautDeLigne();

    std::cout << ITALIC << "Projet de Paul Balensi & Mélodie De Marchi" << RESET;

    sautDeLigne();

    listeChoix = {
        "Commencer une nouvelle partie",
        "Reprendre la partie sauvegardée",
    };

    choix0 = "Quitter";

    return choixParmiChiffre(listeChoix, choix0);

}

size_t UI::ecranNouvellePartie() {

    clearScreen();

    afficherTitre("COMMENCER PARTIE");

    afficherInformation("Avec quelle composition souhaitez-vous jouer?");

    sautDeLigne();

    std::string compoString;
    listeChoix.clear();
    for(const Composition& compo : Plateau::getCompositions()){

        compoString = compo.getNom() + " [";

        for (const auto& pair : compo.getCompositionPartie()) {
            compoString += pair.first->getNom() + ", ";
        }

        listeChoix.push_back(compoString + "]");
    }

    choix0 = "Retour";

    return choixParmiChiffre(listeChoix, choix0);

}

size_t UI::ecranCreationComposition() {

    clearScreen();
    afficherTitre("CRÉATION COMPOSITION");

    sautDeLigne();

    afficherInformation("Voici la liste des cartes du royaume :");
    retourALigne();

    sautDeLigne();

    listeChoix = {
        "Sélectionner les cartes",
        "Composition aléatoire",
        "Voir la description des cartes du royaume"
    };

    choix0 = "Retour";

    return choixParmiChiffre(listeChoix, choix0);

}

std::vector<std::string> UI::ecranChoixJoueurs() {
    
    clearScreen();

    afficherTitre("JOUEURS");
    sautDeLigne();
    afficherInformation("Entrez un à un les pseudos des joueurs de la partie.");
    retourALigne();
    afficherInformation("Capacité : 2 à 4 joueurs maximum.");

    sautDeLigne();

    std::cout << "1 : Terminer";
    retourALigne();
    std::cout << "0 : Retour";
    separateursChoix();
    retourALigne();

    std::vector<std::string> pseudosJoueurs;
    while (true) {

        retourALigne();
        std::cout << "> ";
        std::cin >> input;

        // Retour au menu
        if(input == "0") return {};

        // Sélection terminée
        if(input == "1"){

            // Vérification nombre de joueurs
            if(pseudosJoueurs.size() < 2) {
                annonceErreur("nombre de joueurs insuffisant");
                sautDeLigne();
                continue;
            }

            return pseudosJoueurs;

        }

        // Vérication de l'unicité des pseudos
        for (std::string pseudo : pseudosJoueurs){
            if (pseudo == input) {
                annonceErreur("ce pseudo est déjà choisi");
                sautDeLigne();
                continue;
            }
        }

        pseudosJoueurs.push_back(input);

        // Atteinte de la limite maximale de joueurs
        if (pseudosJoueurs.size() == 4) return pseudosJoueurs;

    }
}

bool UI::ecranModeRapide() {

    clearScreen();

    afficherTitre("MODE RAPIDE");

    sautDeLigne();

    return choixOuiNon("Désirez-vous jouer en mode rapide (1 carte par pile) ?");

}


//Onglets

//VERIFIER QUEL INDICES SONT VRAIMENT RENVOYE

std::vector<size_t> UI::ongletChoixCartesComposition(Joueur &J) {

    separateursTitre();

    sautDeLigne();

    afficherInformation("Entrez un à un les noms des 10 cartes sélectionnée :");
    retourALigne();

    return choixParmiCartes(J, Cartes::catalogue(), 10, "Retour");

}

size_t UI::ongletChoixAleatoireCartesComposition() {

    separateursTitre();
    sautDeLigne();

    afficherInformation("Voici la composition aléatoire de votre partie :");
    retourALigne();

    //std::srand(std::time({}));

    //int r = (std::rand() % Cartes::catalogue().size()) - 1; //Une carte au hasard dans le catalogue, mais mettre royaume?

    // A FINIR

    return 0;

}

size_t UI::ongletDescriptionCartes(const std::vector<const Carte*>&) {
    //A FAIRE
    return 0;
}

// Annonces

void UI::annonceCarteDepuis(std::string nomCarte, Emplacement depuis) {

    switch (depuis)
    {
    case Emplacement::PIOCHE :
        std::cout << "Vous avez pioché la carte " << nomCarte << ".";
        retourALigne();
        break;
    
    case Emplacement::DEFAUSSE :
        std::cout << "Vous avez récupérer de la défausse la carte " << nomCarte << ".";
        retourALigne();
        break;

    default:
        break;
    }

}

void UI::annonceCarteVers(std::string nomCarte, Emplacement vers) {

    switch (vers)
    {
    case Emplacement::PIOCHE :
        std::cout << "Vous mettez sur la pioche la carte " << nomCarte << ".";
        break;
    
    case Emplacement::DEFAUSSE :
        std::cout << "Vous défaussez la carte " << nomCarte << ".";

    default:
        break;
    }

}

void UI::annonceRevelerCartes(const Joueur& J, std::vector <const Carte*> cartes) {

    std::cout << J.getPseudo() << ", vous révélez : [ ";

    for (const Carte* c : cartes){
        std::cout << c->getNom() + " ";
    }

    std::cout << "]";

}

void UI::annonceErreur(const std::string& message) {
    std::cout << RESET << RED << ITALIC << "Erreur : " << RESET << ITALIC << message << "." << RESET;
}
