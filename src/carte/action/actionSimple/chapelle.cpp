#include "chapelle.hpp"

Chapelle::Chapelle() : ActionSimple("Chappelle", 2, "Écartez jusqu'à 4 cartes de votre main.") {};

void Chapelle::utiliser(Joueur& J, Plateau& P){

    size_t nbCartesEcartees = 0;

    while(nbCartesEcartees < 4){

        if(J.demanderOuiNon("Voulez écarter une carte ?")) {

            P.ajoutRebut(P.getCarteParNom(J.demanderNomCarte()));
            nbCartesEcartees++;

        } else {
            
            return;
        }   
    }
}