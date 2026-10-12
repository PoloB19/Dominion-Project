#include "forgeron.hpp"

Forgeron::Forgeron() : ActionSimple("Forgeron", 4, "+3 Cartes") {};

void Forgeron::utiliser(Joueur& J, Plateau&){
    J.piocher(3);
}