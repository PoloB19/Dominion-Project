#include "festival.hpp"

Festival::Festival() :ActionSimple("Festival", 5, "+2 Actions \n +1 Achat \n +2 pièces") {};

void Festival::utiliser(Joueur& J, Plateau& P){
   J.ajustNbAction(+2);
   J.ajustNbAchat(+1);
   J.ajustPiece(+2);
}