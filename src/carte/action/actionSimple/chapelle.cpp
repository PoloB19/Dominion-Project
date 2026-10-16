#include "chapelle.hpp"

Chapelle::Chapelle() : ActionSimple("Chapelle", 2, "Écartez jusqu'à 4 cartes de votre main.") {}

Chapelle::~Chapelle() {}

void Chapelle::utiliser(Joueur& J, Plateau& P) const {

    size_t nbCartesEcartees = 0;

    while(nbCartesEcartees < 4){

        if(J.demanderOuiNon("Voulez-vous écarter une carte ?")) {

            P.ajoutRebut(P.getCarteParNom(J.demanderNomCarte()));
            nbCartesEcartees++;

        } else {
            
            return;
        }   
    }
}