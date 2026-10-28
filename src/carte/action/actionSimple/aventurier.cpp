#include "aventurier.hpp"
#include "UI_terminal.hpp"

Aventurier::Aventurier() : ActionSimple("Aventurier", 6, "Révélez une à une les cartes de votre pioche jusqu'à avoir trouvé 2 cartes Trésor. \nPrenez ces Trésor dans votre main et défausser les autres cartes révélées.") {};

Aventurier::~Aventurier() {}

void Aventurier::utiliser(Joueur& J, Plateau&) const {

    unsigned short nbTresorTrouveTmp = 0;
    const Carte* carteRevelee;

    while(nbTresorTrouveTmp < 2) {
        
        carteRevelee = J.revelerCarte(Emplacement::PIOCHE);

        if(carteRevelee->getType() == "Tresor") {
            //On récupère une carte Trésor
            UI::annonceCarteDepuis(carteRevelee->getNom(), Emplacement::PIOCHE);
            J.ajouterAPioche(carteRevelee);
            nbTresorTrouveTmp++;
        } else {
            //On défausse la carte qu'on vient de piocher
            UI::annonceCarteVers(carteRevelee, Emplacement::DEFAUSSE);
            J.ajouterADefausse(carteRevelee);
        }
        
    }

}
