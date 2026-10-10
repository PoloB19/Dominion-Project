#include "aventurier.hpp"

Aventurier::Aventurier() : ActionSimple("Aventurier", 6, "Révélez une à une les cartes de votre pioche jusqu'à avoir trouvé 2 cartes Trésor. \nPrenez ces Trésor dans votre main et défausser les autres cartes révélées.") {};

/*
void Aventurier::utiliser(Joueur& J, Plateau&){

    unsigned short nbTresorTrouveTmp = 0;

    while(nbTresorTrouveTmp < 2) {
        
        J.piocher(1);

        if(J.getPioche().top()->getType() == "Tresor") {
            //On récupère une carte Trésor
            std::cout << "Vous avez pioché un Trésor nommé : " << J.getMain().at(-1)->getNom() << std::endl;
            nbTresorTrouveTmp++;
        } else {
            //On défausse la carte qu'on vient de piocher
            std::cout << "La carte " << J.getMain().at(-1)->getNom() << " a été défaussée." << std::endl;
            J.defausser(J.getMain().at(-1));
        }

    }

}
*/