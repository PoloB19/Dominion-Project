#include "UI_terminal.hpp"

// Outils
void UI::retourALigne(){
    std::cout << std::endl;
}

void UI::sautDeLigne(){
    std::cout << std::endl << std::endl;
}

void UI::separateurs() {
    std::cout << std::string(longueurMaxLigne, '~');
}

void UI::clearScreen() {
    std::cout << CLEAR_SCREEN << RESET;
}

void UI::afficherInformation(const std::string& info){

    std::cout << info;

}

void UI::afficherTitre(const std::string& titre) {

    size_t tailleTitre = titre.length() + 2;

    // Si le titre est trop grand
    if (tailleTitre + 6 > longueurMaxLigne) {
        std::cout << "§ " << titre << " §";
        return;
    }

    // 2. On calcule la place disponible pour UN côté (gauche ou droite)
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

    sautDeLigne();
}


// Choix A REVOIR

std::string choix;

// vraiment besoin de "message" en paramètre dans choixOuiNon ?
bool UI::choixOuiNon(const std::string& message) {

    while (true) {
        std::cout << message << std::endl;
        std::cout << " Choix (O/N) > ";
        std::cin >> choix;
        
        if (choix == "O" || choix == "o" || choix == "Oui" || choix == "oui" || choix == "OUI") return true;
        if (choix == "N" || choix == "n" || choix == "Non" || choix == "non" || choix == "NON") return false;
        
        std::cout << "Choix invalide. Veuillez répondre par 'oui' ou 'non'.";

        sautDeLigne();
    }
}

std::string UI::getNomCarte() {

    while(true){

        std::cout << "Quel est son nom : ";
        std::cin >> choix;

        return choix;

    }

}

std::vector<size_t> UI::choixParmiCartes(Joueur& J, std::vector<const Carte*> cartes, unsigned short nbChoix){

    std::vector<size_t> idChoix = {};
    
    while (idChoix.size() < nbChoix){

        std::cout << "Choisissez " << nbChoix << " carte(s) parmi : ";
        for (const Carte* c : cartes){
            std::cout << c->getNom() + " ";
        }
        
        retourALigne();

        std::string nomCarteChoisieTmp = J.demanderNomCarte();
        for (size_t i = 0; i < cartes.size(); i++){
            if (cartes.at(i)->getNom() == nomCarteChoisieTmp){
                idChoix.push_back(i);
            }
        }
    }

    return idChoix;

}

//Afffichage

void UI::afficherDemarrage() {

    clearScreen();
    afficherTitre("DOMINION");

    sautDeLigne();

    std::cout << "Bienvenue sur ce deck builder médiéval.";
    retourALigne();
    std::cout << "Votre royaume commence ici !";

    sautDeLigne();

    separateurs();

    sautDeLigne();

    std::cout << ITALIC << "Projet de Paul Balensi & Mélodie De Marchi" << RESET;

    sautDeLigne();

}

// Annonces

void UI::annonceCarteDepuis(std::string nomCarte, Emplacement depuis) {

    switch (depuis)
    {
    case Emplacement::PIOCHE :
        std::cout << "Vous avez pioché la carte " << nomCarte << "." << std::endl;
        break;
    
    case Emplacement::DEFAUSSE :
        std::cout << "Vous avez récupérer de la défausse la carte " << nomCarte << "." << std::endl;

    default:
        break;
    }

}

void UI::annonceCarteVers(std::string nomCarte, Emplacement vers) {

    switch (vers)
    {
    case Emplacement::PIOCHE :
        std::cout << "Vous mettez sur la pioche la carte " << nomCarte << "." << std::endl;
        break;
    
    case Emplacement::DEFAUSSE :
        std::cout << "Vous défaussez la carte " << nomCarte << "." << std::endl;

    default:
        break;
    }

}

void UI::annonceRevelerCartes(const Joueur& J, std::vector <const Carte*> cartes) {

    std::cout << J.getPseudo() << ", vous révélez : [ ";

    for (const Carte* c : cartes){
        std::cout << c->getNom() + " ";
    }

    std::cout << "]" << std::endl;

}

void UI::annonceErreur(std::string message) {
    std::cout << "Erreur : " << message << "." << std::endl;
}
