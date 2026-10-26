#include "espion.hpp"
#include "UI_terminal.hpp"

Espion::Espion() : ActionAttaque("Espion", 4, "+1 Carte \n+1 Action \nTous les joueurs (vous incluant) révèlent leur prochaine carte à piocher et décident de la défausser ou non.") {}

Espion::~Espion() {}

void Espion::utiliser(Joueur& J, Plateau& P) const {

    J.piocher(1);
    J.ajustNbAction(+1);

    // D'abord sur le joueur qui utilise la carte :
    const Carte* carteRevelee = J.revelerCarte(Emplacement::PIOCHE); 
    if (carteRevelee != nullptr) {

        if (UI::choixOuiNon("Vous avez révélé " + carteRevelee->getNom() + ". Voulez-vous la défausser ?")) {
            J.ajouterADefausse(carteRevelee);
        } else {
            J.ajouterAPioche(carteRevelee);
        }
    }

    // Ensuite sur les joueurs sans défense :
    std::vector<Joueur*> ciblesAttaque = ActionAttaque::determinerCibles(J, P, this);

    for (Joueur* ptr_j : ciblesAttaque){

        if (ptr_j == nullptr) continue; // Sécurité
        Joueur& j = *ptr_j; // On transforme le pointeur en référence

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