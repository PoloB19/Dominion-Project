#include "milice.hpp"
#include "UI_terminal.hpp"

Milice::Milice() : ActionAttaque("Milice", 4, "+2 pièces \nTous les autres joueurs doivent défausser des cartes jusqu'à n'en avoir que 3 en main.") {}

Milice::~Milice() {}

void Milice::utiliser(Joueur& J, Plateau& P) const {
    J.ajustNbPiece(2);

    std::vector<Joueur*> ciblesAttaque = ActionAttaque::determinerCibles(J, P, this);

    for (Joueur* ptr_j : ciblesAttaque){
        
        if (ptr_j == nullptr) continue; // Sécurité
        Joueur& j = *ptr_j; // On transforme le pointeur en référence

        std::vector<const Carte*> mainj = j.getMain();
        
        while (mainj.size() > 3) {
        
            size_t idCarteChoisie = UI::choixParmiCartes(J,mainj,1).at(0);
            j.enleverDepuisMain(mainj.at(idCarteChoisie)->getNom(),Emplacement::DEFAUSSE);

            mainj = j.getMain();
        }
    }
}

