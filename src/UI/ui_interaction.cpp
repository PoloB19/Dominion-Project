#include "ui_interaction.hpp"

std::string choix;

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

// Choix

inline bool choixOuiNon(const std::string& message) {

    while (true) {
        std::cout << message << std::endl;
        std::cout << " Choix (O/N) : ";
        std::cin >> choix;

        if (choix == "DEBUG") throw std::string("DEBUG");
        
        if (choix == "O" || choix == "o" || choix == "Oui" || choix == "oui" || choix == "OUI") return true;
        if (choix == "N" || choix == "n" || choix == "Non" || choix == "non" || choix == "NON") return false;
        
        std::cout << "Choix invalide. Veuillez répondre par 'oui' ou 'non'." << std::endl;
    }
}

inline std::string getNomCarte() {

    while(true){

        std::cout << "Quel est son nom : ";
        std::cin >> choix;

        if (choix == "DEBUG") throw std::string("Debug, annulation ");

        return choix;

    }

}

std::vector<size_t> choixParmiCartes(Joueur& J, std::vector<const Carte*> cartes, unsigned short nbChoix){

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

// Annonces

inline void annonceCarteDepuis(std::string nomCarte, Emplacement depuis) {

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

inline void annonceCarteVers(std::string nomCarte, Emplacement vers) {

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

inline void annonceRevelerCartes(Joueur& J, std::vector <const Carte*> cartes) {

    std::cout << J.getPseudo() << ", vous révélez : [ ";

    for (const Carte* c : cartes){
        std::cout << c->getNom() + " ";
    }

    std::cout << "]" << std::endl;

}

// std::string demanderCible(const std::vector<Joueur*>& joueurs);

