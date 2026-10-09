#include "laboratoire.hpp"
#include "joueur.hpp"

Laboratoire::Laboratoire() : Action(5 , "description") {}

void Laboratoire::utiliser(Joueur J){
    J.piocher();
    J.piocher();
    J.augmenterNbAction();
}