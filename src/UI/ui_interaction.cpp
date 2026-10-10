#include "ui_interaction.hpp"
#include "carte.hpp"

std::string choix;

inline bool choixOuiNon(const std::string& message) {

    while (true) {
        std::cout << message << " Choix (O/N) : ";
        std::cin >> choix;

        if (choix == "DEBUG") return NULL;
        
        if (choix == "O" || choix == "o" || choix == "Oui" || choix == "oui" || choix == "OUI") return true;
        if (choix == "N" || choix == "n" || choix == "Non" || choix == "non" || choix == "NON") return false;
        
        std::cout << "Choix invalide. Veuillez répondre par 'oui' ou 'non'." << std::endl;
    }
}

inline std::string getNomCarte() {

    while(true){

        std::cout << " Quel est son nom : ";
        std::cin >> choix;

        if (choix == "DEBUG") return NULL;

        return choix;

    }

}


// Plus tard
// int demanderChoix(const std::string& message, int maxChoix);
// std::string demanderCible(const std::vector<Joueur*>& joueurs);

