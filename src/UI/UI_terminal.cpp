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

void UI::animationChargement(size_t temps_attente) {
    const size_t tailleBarre = 20;
    const size_t delaiMs = (temps_attente * 1000) / tailleBarre; // découpe le temps pour la barre

    for (size_t i = 0; i <= tailleBarre; i++) {
        // \r écrase la ligne actuelle, std::flush force l'affichage immédiat
        std::cout << "\r" << std::string((longueurMaxLigne - tailleBarre - 1)/2, ' ')
                << "["
                << std::string(i, '~')
                << std::string(tailleBarre - i, ' ') 
                << "]" << std::flush;

        std::this_thread::sleep_for(std::chrono::milliseconds(delaiMs));
    }

    retourALigne();
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

void UI::afficherListeCarteParNom(const std::vector<const Carte*>& listeCartes) {

    std::cout << "[";

    for (size_t i = 0; i < listeCartes.size(); i++) {
        std::cout << listeCartes.at(i)->getNom();
        if(i != listeCartes.size() - 1 ){
            std::cout << ", ";
        }
    }

    std::cout << "]";

}

void UI::afficherPilesPlateau(const Plateau& P) {

    // Trouve le prix max parmi toutes les cartes du plateau
    size_t prixMax = 0;
    for (const auto& pair : P.getPiles()) {
        if (pair.first->getPrix() > prixMax) {
            prixMax = pair.first->getPrix();
        }
    }

    // Parcourir les prix par ordre décroissant à partir de prixMax
    for (short prix = prixMax; prix >= 0; prix--) {
        
        std::string ligne = "";

        for (const auto& pair : P.getPiles()) {
            if (pair.first->getPrix() == prix) {
                if (!ligne.empty()) {
                    ligne += ", ";
                }
                ligne += pair.first->getNom() + " (" + std::to_string(pair.second) + ")";
            }
        }

        // Empêche l'affichage des prix qui n'ont aucune carte
        if (!ligne.empty()) {
            std::cout << prix << " : " << ligne << "\n";
        }
    }

    std::cout << "Rebut (" << std::to_string(P.getRebut().size()) << ")";
    retourALigne();
}

void UI::afficherAttributsJoueur(const Joueur& J) {

    std::cout << "Nombre d'actions restantes : " << BOLD << std::to_string(J.getNbAction()) << RESET;
    retourALigne();
    std::cout << "Nombre d'achats restants : " << BOLD << std::to_string(J.getNbAchat()) << RESET;
    retourALigne();
    std::cout << "Pièces : " << BOLD << std::to_string(J.getNbPieces()) << RESET;

    sautDeLigne();

    std::cout << "Pioche (" << J.getPioche().size() << ") | Défausse (" << J.getDefausse().size() << ")";
    retourALigne();

    std::cout << "Main : ";
    if (!J.getMain().empty()) {
        afficherListeCarteParNom(J.getMain());
    } else {
        std::cout << ITALIC << "vide" << RESET;
    }
    retourALigne();

    std::cout << "En jeu : ";
    if (!J.getEnJeu().empty()) {
        afficherListeCarteParNom(J.getEnJeu());
    } else {
        std::cout << ITALIC << "aucune carte actuellement en jeu" << RESET;
    }
    retourALigne();

}

// Choix

size_t UI::choixParmiChiffre(const std::vector<std::string>& listeChoix, const std::string& choix0) {

    for (size_t i = 0; i < listeChoix.size(); i++){
        std::cout << i+1 << " : " << listeChoix.at(i);
        retourALigne();
    }

    if (!choix0.empty()) {
        std::cout << "0 : " << choix0;
    }

    while (true) {

        retourALigne();
        separateursChoix();
        retourALigne();
        std::cout << "> ";
        std::getline(std::cin >> std::ws, UI::input);
        retourALigne();

        if(UI::input.length() != 1 || !std::isdigit(UI::input.at(0))) {
            annonceErreur("veuillez entrer un chiffre valide");
            retourALigne();
            continue;
        }

        size_t inputValeur = UI::input.at(0) - '0'; //transforme la saisie en nombre

        if (inputValeur > listeChoix.size() || (inputValeur == 0 && choix0.empty())) {
            annonceErreur("le choix '" + UI::input + "' n'existe pas");
            retourALigne();
            continue;
        }

        return inputValeur;

    }
}

std::vector<size_t> UI::choixParmiCartes(const Joueur& J, const std::vector<const Carte*>& cartes, unsigned short nbChoix, std::string choix0) {

    // Sécurité
    if(cartes.empty()) return {};

    afficherInformation(J.getPseudo() + ", choisissez " + std::to_string(nbChoix) + " carte(s) parmi :");
    sautDeLigne();

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
    retourALigne();

    std::vector<size_t> idChoix = {};
    while (idChoix.size() < nbChoix){
        
        std::cout << "> ";
        std::getline(std::cin >> std::ws, UI::input);

        // Si choix0 est possible et demandé
        if(!choix0.empty() && UI::input.at(0) - '0' == 0) return {};

        bool carteExiste = false;
        bool carteDoublon = false;
        bool carteAcceptee = false;

        // Vérifie que la sélection est possible
        for (size_t i = 0; i < cartes.size(); i++){

            // Vérifie que la carte est proposée 
            if (cartes.at(i)->getNom() == UI::input){

                carteExiste = true;

                // Vérifie que la carte n'a pas déjà été sélectionnée
                for(size_t j : idChoix){
                    if (i == j){
                        carteDoublon = true;
                        break;
                    }
                }

                if (!carteDoublon) {
                    idChoix.push_back(i);
                    carteAcceptee = true;
                    break;
                }
            }
        }

        if (!carteExiste) annonceErreur("cette carte n'est pas proposée");
        else if (!carteAcceptee) annonceErreur("cette carte est déjà sélectionnée");
        sautDeLigne();

    }

    return idChoix;

}

const Carte* UI::choixParmiPiles(Plateau& P){

    retourALigne();
    while (true) {

        afficherInformation("Entrez le nom d'une carte.");
        retourALigne();
        afficherInformation("0 : Retour");
        separateursChoix();
        retourALigne();
        std::cout << " > ";
        std::getline(std::cin >> std::ws, UI::input);

        if(UI::input == "0") return nullptr;

        for (const auto& pair : P.getPiles()){
            if(pair.first->getNom() == input && pair.second > 0){
                return pair.first;
            }
        }

        annonceErreur("cette carte n'est plus disponible ou n'existe pas");
        sautDeLigne();

    }
}

bool UI::choixOuiNon(const std::string& question) {

    while (true) {

        afficherInformation(question);
        retourALigne();
        separateursChoix();
        retourALigne();
        std::cout << " > ";
        std::getline(std::cin >> std::ws, UI::input);
        
        if (UI::input == "O" || UI::input == "o" || UI::input == "Oui" || UI::input == "oui" || UI::input == "OUI") return true;
        if (UI::input == "N" || UI::input == "n" || UI::input == "Non" || UI::input == "non" || UI::input == "NON") return false;
        
        annonceErreur("veuillez répondre par 'oui' ou 'non'");

        sautDeLigne();

    }
}

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

    UI::listeChoix = {
        "Commencer une nouvelle partie",
        "Reprendre la partie sauvegardée",
    };

    UI::choix0 = RED + "Quitter" + RESET;

    return choixParmiChiffre(listeChoix, choix0);

}

size_t UI::ecranNouvellePartie() {

    clearScreen();

    afficherTitre("COMMENCER PARTIE");
    sautDeLigne();

    afficherInformation("Avec quelle composition souhaitez-vous jouer?");

    sautDeLigne();

    std::string compoString;
    UI::listeChoix.clear();
    for(const Composition& compo : Plateau::getCompositions()){

        compoString = UNDERLINE + compo.getNom() + RESET + " | ";

        for (const auto& pair : compo.getCompositionPartie()) {
            compoString += BLUE + pair.first->getNom() + RESET + " | ";
        }

        UI::listeChoix.push_back(compoString);
    }

    UI::listeChoix.push_back(UNDERLINE + "Créer sa propre composition" + RESET);
    UI::choix0 = "Retour";

    return choixParmiChiffre(listeChoix, choix0);

}

size_t UI::ecranCreationComposition() {

    clearScreen();
    afficherTitre("CRÉATION COMPOSITION");

    sautDeLigne();

    afficherInformation("Voici la liste des cartes Royaume disponibles :");
    sautDeLigne();

    afficherListeCarteParNom(Cartes::royaume());

    sautDeLigne();

    UI::listeChoix = {
        "Sélectionner les cartes",
        "Composition aléatoire",
        "Voir la description des cartes Royaume"
    };

    UI::choix0 = "Retour";

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

    std::cout << "1 : " << GREEN << "Terminer" << RESET;
    retourALigne();
    std::cout << "0 : Retour";
    retourALigne();
    separateursChoix();
    retourALigne();

    std::vector<std::string> pseudosJoueurs;
    while (true) {

        retourALigne();
        std::cout << "> ";
        std::getline(std::cin >> std::ws, UI::input);

        // Retour au menu
        if(UI::input == "0") return {};

        // Sélection terminée
        if(UI::input == "1"){

            // Vérification nombre de joueurs
            if(pseudosJoueurs.size() < 2) {
                annonceErreur("nombre de joueurs insuffisant");
                sautDeLigne();
                continue;
            }

            return pseudosJoueurs;

        }

        // Vérication de l'unicité des pseudos
        bool dejaPris = false;
        for (std::string pseudo : pseudosJoueurs){
            if (pseudo == UI::input) {
                annonceErreur("ce pseudo est déjà choisi");
                sautDeLigne();
                dejaPris = true;
                break;
            }
        }
        if (dejaPris) continue;

        pseudosJoueurs.push_back(UI::input);

        // Atteinte de la limite maximale de joueurs
        if (pseudosJoueurs.size() == 4) return pseudosJoueurs;

    }
}

bool UI::ecranModeRapide() {

    clearScreen();

    afficherTitre("MODE RAPIDE");

    sautDeLigne();

    return choixOuiNon("Désirez-vous jouer en mode " + YELLOW + "rapide" + RESET +" (1 carte par pile) ?");

}

void UI::ecranMessageDemarragePartie(bool depuisSauvegarde) {

    clearScreen();

    std::cout << "§" << std::string(longueurMaxLigne - 2, '~') << "§";
    retourALigne();

    std::cout << BLUE;
    depuisSauvegarde ? std::cout << "REPRISE " : std::cout << "DÉMARRAGE ";
    std::cout << "DE LA PARTIE, QUE LE MEILLEUR GAGNE !";

    std::cout << RESET;
    retourALigne();
    std::cout << "§" << std::string(longueurMaxLigne - 2, '~') << "§";
    sautDeLigne();

    animationChargement(4);

}

size_t UI::ecranTourJoueur(Joueur& J, Plateau& P, bool phaseSuivante) {

    clearScreen();
    afficherTitre(BOLD + BLUE + "TOUR " + std::to_string(J.getNbTourJoues() + 1) + " - " + J.getPseudo() + RESET);

    sautDeLigne();

    afficherInformation(ITALIC + "Piles centrales du plateau (triées par prix) :" + RESET);
    sautDeLigne();
    afficherPilesPlateau(P);

    sautDeLigne();

    afficherAttributsJoueur(J);
    
    sautDeLigne();

    return phaseSuivante ? ongletPhaseAchat() : ongletPhaseAction();
}

size_t UI::ecranQuitterPartie() {

    clearScreen();
    afficherTitre("QUITTER LA PARTIE");
    sautDeLigne();
    afficherInformation("Vous vous apprêtez à quitter la partie.");
    sautDeLigne();
    separateursTitre();
    sautDeLigne();

    UI::listeChoix = {
        GREEN + "Avec sauvegarde" + RESET,
        RED + "Sans sauvegarde" + RESET
    };

    UI::choix0 = "Annuler et reprendre";

    return choixParmiChiffre(UI::listeChoix, UI::choix0);

}

size_t UI::ecranFinDePartie(Plateau& P) {

    clearScreen();

    afficherTitre("FIN DE PARTIE");

    sautDeLigne();

    afficherInformation("Le gagnant va être annoncé...");

    sautDeLigne();

    animationChargement(4);

    sautDeLigne();

    std::vector<Joueur *> gagnants = P.determinerGagnant();

    std::cout << GREEN << "Un grand BRAVO à ";

    if(gagnants.size() == 1){

        std::cout << gagnants.at(0)->getPseudo() << " !!!" << RESET;
        retourALigne();
        std::cout << "Il/Elle a obtenu " << std::to_string(gagnants.at(0)->compterPoints()) << " points.";
        retourALigne();
        std::cout << "Qui viendra le détrôner :) ?";

    } else {

        std::string pseudosGagants;
        for (const Joueur * J : gagnants){
            pseudosGagants += J->getPseudo() + ", ";
        }

        std::cout << pseudosGagants << " !!!" << RESET;
        std::cout << "Ils ont obtenu " << std::to_string(gagnants.at(0)->compterPoints()) << " points à égalité";
        retourALigne();
        std::cout << "Qui viendra les détrôner :) ?";

    }

    sautDeLigne();

    return choixParmiChiffre({}, "Retour au menu principal");

}

//Onglets

std::vector<size_t> UI::ongletChoixCartesComposition(Joueur &J) {

    separateursTitre();

    sautDeLigne();

    afficherInformation("Entrez un à un les noms des 10 cartes sélectionnées :");
    retourALigne();

    //Renvoie les ID des cartes Royaume du catalogue
    return choixParmiCartes(J, Cartes::royaume(), 10, "Retour");

}

size_t UI::ongletChoixAleatoireCartesComposition(Composition& compoAlea) {

    separateursTitre();
    sautDeLigne();

    afficherInformation("Voici la composition aléatoire de votre partie :");
    retourALigne();

    std::vector<const Carte*> catalogue = Cartes::royaume();
    std::map<const Carte*, unsigned short> selectionAleatoire;
    std::vector<const Carte*> listeCartes;

    // tirage de 10 cartes uniques au hasard
    while (selectionAleatoire.size() < 10 ) {
        size_t indexAleatoire = std::rand() % catalogue.size();
        const Carte* carteTiree = catalogue[indexAleatoire];
        selectionAleatoire[carteTiree] = 10;
    }

    // Création de la composition
    compoAlea = Composition("Composition Aléatoire", selectionAleatoire);

    // Affichage des 10 cartes tirées
    for (const auto& pair : compoAlea.getCompositionPartie()) {
        listeCartes.push_back(pair.first);
    }

    afficherListeCarteParNom(listeCartes);

    sautDeLigne();

    UI::listeChoix = {
        "Valider",
        "Recommencer",
    };

    UI::choix0 = "Retour";

    return choixParmiChiffre(listeChoix, choix0);

}

size_t UI::ongletDescriptionCartes(const std::vector<const Carte*>& listeCarte) {
    
    afficherTitre("DESCRIPTION CARTES");
    sautDeLigne();

    for (const Carte* c : listeCarte){
        std::cout << UNDERLINE << c->getNom() << " :" << RESET << " " << c->getPrix() << " pcs";
        retourALigne();
        std::cout << ITALIC << c->getDescription() << RESET;
        sautDeLigne();
    }

    separateursTitre();

    sautDeLigne();

    return choixParmiChiffre({}, "Retour");
}

size_t UI::ongletPhaseAction() {
    
    std::cout << PURPLE << "!~~~~~~~~!~~~~~~~! PHASE ACTION !~~~~~~~!~~~~~~~~!" << RESET;
    sautDeLigne();

    UI::listeChoix = {
        CYAN + "Voir la description des cartes du jeu" + RESET,
        BLUE + "Utiliser une carte" + RESET,
        YELLOW + "Écarter une carte" + RESET,
        GREEN + "Passer à la phase d'achat" + RESET,
    };

    UI::choix0 = RED + "Quitter la partie" + RESET;

    return choixParmiChiffre(listeChoix, choix0);

}

size_t UI::ongletPhaseAchat() {
    
    std::cout << GREEN << "€~~~~~~~~€~~~~~~~€ PHASE ACHAT €~~~~~~~€~~~~~~~~€" << RESET;

    sautDeLigne();

    UI::listeChoix = {
        CYAN + "Voir les descriptions des cartes du jeu" + RESET,
        BLUE + "Acheter une carte" + RESET,
        YELLOW + "Finir son tour" + RESET
    };

    UI::choix0 = RED + "Quitter la partie" + RESET;

    return choixParmiChiffre(listeChoix, choix0);

}

// Annonces

void UI::annonceCarteDepuis(std::string nomCarte, Emplacement depuis) {

    switch (depuis)
    {
    case Emplacement::PIOCHE :
        std::cout << "Vous piochez la carte " << nomCarte << ". ";
        retourALigne();
        break;
    case Emplacement::DEFAUSSE :
        std::cout << "Vous récupérez de la défausse la carte " << nomCarte << ". ";
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
        std::cout << "Vous mettez sur la pioche la carte " << nomCarte << ". ";
        break;
    
    case Emplacement::DEFAUSSE :
        std::cout << "Vous défaussez la carte " << nomCarte << ". ";
        break;
    case Emplacement::EN_JEU:
        std::cout << "Vous jouez la carte " << nomCarte << ". ";
        break;
    default:
        break;
    }

}

void UI::annonceRevelerCartes(const Joueur& J, const std::vector <const Carte*>& cartes) {

    std::cout << J.getPseudo() << ", vous révélez : [ ";

    for (const Carte* c : cartes){
        std::cout << c->getNom() + " ";
    }

    std::cout << "]";
    retourALigne();

}

void UI::annonceErreur(const std::string& message) {
    std::cout << RESET << RED << ITALIC << "Erreur : " << RESET << ITALIC << message << "." << RESET;
}
