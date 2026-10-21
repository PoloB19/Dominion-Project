#include "espion.hpp"
#include "UI_terminal.hpp"

Espion::Espion() : ActionAttaque("Espion", 4, "+1 Carte \n+1 Action \nTous les joueurs (vous incluant) révèlent leur prochaine carte à piocher et décident de la défausser ou non.") {}

Espion::~Espion() {}

void Espion::utiliser(Joueur& J, Plateau& P) const {

    J.piocher(1);
    J.ajustNbAction(+1);

    for (Joueur& j : P.getJoueurs()){

        const Carte* carteRevelee = j.revelerCarte(Emplacement::PIOCHE); 

        if (carteRevelee != nullptr) {

            if (UI::choixOuiNon("Vous avez révélé " + carteRevelee->getNom() + ". Voulez-vous la défausser ?")) {
                j.ajouterADefausse(carteRevelee);
            } else {
                j.ajouterAPioche(carteRevelee);
            }

        }
        
    }
}