#include "laboratoire.hpp"
#include "joueur.hpp"

Laboratoire::Laboratoire() : ActionSimple("Laboratoire", 5, "+2 Cartes \n+1 Action") {}

Laboratoire::~Laboratoire() {}

void Laboratoire::utiliser(Joueur&J, Plateau&){
    J.piocher(2);
    J.ajustNbAction(+1);
}