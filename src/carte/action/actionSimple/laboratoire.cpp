#include "laboratoire.hpp"
#include "joueur.hpp"

Laboratoire::Laboratoire() : ActionSimple("Laboratoire", 5, "+2 Cartes \n+1 Action") {}

/* void Laboratoire::utiliser(const Plateau& P, size_t idJoueur){
    P.getJoueurs().at(idJoueur)->piocher();
    P.getJoueurs().at(idJoueur)->piocher();
    P.getJoueurs().at(idJoueur)->augmenterNbAction();
} */