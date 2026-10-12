#include "aventurier.hpp"

Aventurier::Aventurier() : ActionSimple("Aventurier", 6, "Révélez une à une les cartes de votre pioche jusqu'à avoir trouvé 2 cartes Trésor. \nPrenez ces Trésor dans votre main et défausser les autres cartes révélées.") {};


void Aventurier::utiliser(Joueur& J, Plateau&){

    unsigned short nbTresorTrouveTmp = 0;
    const Carte* carteRevelee;

    while(nbTresorTrouveTmp < 2) {
        
        carteRevelee = J.revelerCarte(Emplacement::PIOCHE);

        if(carteRevelee->getType() == "Tresor") {
            //On récupère une carte Trésor
            J.annonceCarteDepuis(carteRevelee->getNom(), Emplacement::PIOCHE);
            J.ajouterAPioche(carteRevelee);
            nbTresorTrouveTmp++;
        } else {
            //On défausse la carte qu'on vient de piocher
            J.annonceCarteVers(carteRevelee->getNom(), Emplacement::DEFAUSSE);
            J.ajouterADefausse(carteRevelee);
        }
        
    }

}
