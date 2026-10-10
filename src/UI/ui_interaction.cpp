#include "ui_interaction.hpp"
#include "carte.hpp"

inline bool choixOuiNon(const std::string& message) {

    std::string choix;

    while (true) {
        std::cout << message << " (O/N) : ";
        std::cin >> choix;
        
        if (choix == "O" || choix == "o" || choix == "Oui" || choix == "oui" || choix == "OUI") return true;
        if (choix == "N" || choix == "n" || choix == "Non" || choix == "non" || choix == "NON") return false;
        
        std::cout << "Choix invalide. Veuillez répondre par 'oui' ou 'non'." << std::endl;
    }
}

// Plus tard
// int demanderChoix(const std::string& message, int maxChoix);
// std::string demanderCible(const std::vector<Joueur*>& joueurs);

