#include "bucheron.hpp"

Bucheron::Bucheron() : ActionSimple("Bucheron", 3, "+1 Achat \n+2 pièces") {}

void Bucheron::utiliser(Joueur& J, Plateau& P){

    std::cout << "Vous obtenez 1 achat et 2 pièces supplémentaires." << std::endl;

    J.ajustNbAchat(+1);
    J.ajustNbPiece(+2);
}