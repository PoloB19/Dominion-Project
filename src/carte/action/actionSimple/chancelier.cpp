#include "chancelier.hpp"

Chancelier::Chancelier(): ActionSimple("Chancelier", 3, "Gagnez 2 pièces. Vous pouvez mettre votre pioche dans votre défausse.") {};

void Chancelier::utiliser(Joueur& J, Plateau& P){

    J.ajustNbPiece(+2);

    if(J.demanderOuiNon("voulez-vous mettre votre pioche dans votre défausse?")){
        //On "pioche" la carte puis on la met directement dans la défausse
        while(J.getPioche().size() > 0){

            J.piocher(1);
            J.enleverDepuisMain(J.getMain().back()->getNom(), Emplacement::DEFAUSSE);

        }
    }
}