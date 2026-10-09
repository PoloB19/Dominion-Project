#include "forgeron.hpp"

Forgeron::Forgeron() : ActionSimple("Forgeron", 4, "+3 Cartes") {};

void Forgeron::utiliser(Joueur& J, Plateau& P){
    J.piocher(3);
    std::cout << "Vous avez pioché 3 cartes (au plus)." << std::endl;
}