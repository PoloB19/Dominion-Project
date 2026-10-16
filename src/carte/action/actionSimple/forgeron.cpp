#include "forgeron.hpp"

Forgeron::Forgeron() : ActionSimple("Forgeron", 4, "+3 Cartes") {}

Forgeron::~Forgeron() {}

void Forgeron::utiliser(Joueur& J, Plateau&) const {
    J.piocher(3);
}