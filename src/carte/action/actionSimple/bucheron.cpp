#include "bucheron.hpp"

Bucheron::Bucheron() : ActionSimple("Bucheron", 3, "+1 Achat \n+2 pièces") {}

Bucheron::~Bucheron() {}

void Bucheron::utiliser(Joueur& J, Plateau&){
    J.ajustNbAchat(+1);
    J.ajustNbPiece(+2);
}