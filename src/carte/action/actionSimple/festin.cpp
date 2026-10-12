#include "festin.hpp"

Festin::Festin() : ActionSimple("Festin", 4, "Écartez cette carte. \nObtenez une carte coûtant au plus 5 pièces."){};

void Festin::utiliser(Joueur& J, Plateau& P) {

    while(true){

        const Carte* carteVoulue = P.getCarteParNom(J.demanderNomCarte());

        if (carteVoulue->getPrix() > 5){

            J.annonceErreur("la carte est trop chère");

        } else if (carteVoulue == nullptr){
            
            J.annonceErreur("cette carte n'existe pas");

        } else {

            J.obtenirCartePlateau(carteVoulue, P, Emplacement::DEFAUSSE);
            P.ajoutRebut(this);
            return;

        }
    }
}
