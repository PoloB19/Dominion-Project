#include "marche.hpp"

Marche::Marche() : ActionSimple("Marché", 5, "+1 Carte \n+1 Action \n+1 Achat \n+1 pièce") {}

Marche::~Marche() {}

void Marche::utiliser(Joueur& J, Plateau& P) {
    J.piocher(1);
    J.ajustNbAction(+1);
    J.ajustNbAchat(+1);
    J.ajustNbPiece(+1);
}