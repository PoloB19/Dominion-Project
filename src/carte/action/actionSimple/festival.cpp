#include "festival.hpp"

Festival::Festival() :ActionSimple("Festival", 5, "+2 Actions \n+1 Achat \n+2 pièces") {}

Festival::~Festival() {}

void Festival::utiliser(Joueur& J, Plateau&) const {
   J.ajustNbAction(+2);
   J.ajustNbAchat(+1);
   J.ajustNbPiece(+2);
}