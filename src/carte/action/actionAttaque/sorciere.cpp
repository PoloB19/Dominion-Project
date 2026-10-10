#include "sorciere.hpp"

Sorciere::Sorciere() : ActionAttaque("Sorcière", 5, "+2 Cartes \nTous les autres joueurs obtiennent une carte Malédiction.") {};

void Sorciere::utiliser(Joueur& J, Plateau& P){

    J.piocher(2);

    for (Joueur* cible : P.getJoueurs()){
        if (cible != &J){
            cible->obtenirCarte(P.getCarteParNom("Malédiction"), P, Destination::DEFAUSSE);
        }
    }
}