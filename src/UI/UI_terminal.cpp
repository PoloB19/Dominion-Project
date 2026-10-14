#include "UI_terminal.hpp"

// Outils A MODIFIER DUCOUP

void UI::sautDeLigne(){
    std::cout << std::endl << std::endl;
}

void UI::separateurs() {
    std::cout << "================================================================";
    sautDeLigne();
}

void UI::separateurTitre(std::string& titre){

    do {
        titre = "=" + titre + "=";
    } while (titre.size() < 64);    

    std::cout << titre;

    sautDeLigne();

}

// Choix

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
        std::cout << std::endl;

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

    //A DEFINIR

    std::cout << std::endl;


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
