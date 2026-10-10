#include "espion.hpp"

#include "ui_interaction.hpp"

Espion::Espion() : ActionAttaque("Espion", 4, "+1 Carte \n +1 Action \nTous les joueurs (vous incluant) révèlent leur prochaine carte à piocher et décident de la défausser ou non.") {};

void Espion::utiliser(Joueur& J, Plateau& P){

    J.piocher(1);
    J.ajustNbAction(+1);

    std::string choix;

    for (Joueur* j : P.getJoueurs()){

        if (j->getPioche().empty()) j->melangerDefausse();

        if (!j->getPioche().empty()){

            std::cout << "Cette carte est votre prochaine pioche : " << j->getPioche().top()->getNom()<< std::endl; 
            if (UI::choixOuiNon("souhaitez-vous la défausser")){
                /**/
            }
        } 
    }
}