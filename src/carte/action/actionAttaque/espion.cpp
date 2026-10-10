#include "espion.hpp"

#include "ui_interaction.hpp"

Espion::Espion() : ActionAttaque("Espion", 4, "+1 Carte \n +1 Action \nTous les joueurs (vous incluant) révèlent leur prochaine carte à piocher et décident de la défausser ou non.") {};

void Espion::utiliser(Joueur& J, Plateau& P){

    J.piocher(1);
    J.ajustNbAction(+1);

    for (Joueur* j : P.getJoueurs()){

        if(j->accesPioche()){

            const Carte* carteRevelee = j->revelerCarte(Emplacement::PIOCHE); 

            if (carteRevelee != nullptr) {

                if (j->demanderOuiNon("vous avez révélé " + carteRevelee->getNom() + ". Voulez-vous la défausser ?")) {
                    j->ajouterADefausse(carteRevelee);
                } else {
                    j->ajouterAPioche(carteRevelee);
                }

            };
        }
    }
}