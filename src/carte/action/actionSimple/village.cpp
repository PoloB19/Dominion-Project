#include "village.hpp"

Village::Village() : ActionSimple("Village", 5, "+1 Carte \n+2 Actions") {}

Village::~Village() {}

void Village::utiliser(Joueur& J, Plateau &) const {
    J.piocher(1);
    J.ajustNbAction(+2);
}