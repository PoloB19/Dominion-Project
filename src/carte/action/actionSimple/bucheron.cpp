#include "bucheron.hpp"

Bucheron::Bucheron() : ActionSimple("Bûcheron", 3, "+1 Achat \n+2 pièces") {}

Bucheron::~Bucheron() {}

void Bucheron::utiliser(Joueur& J, Plateau&) const {
    J.ajustNbAchat(+1);
    J.ajustNbPiece(+2);
}