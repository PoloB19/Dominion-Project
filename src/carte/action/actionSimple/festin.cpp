#include "festin.hpp"

Festin::Festin() : ActionSimple("Festin", 4, "Écartez cette carte. \n Obtenez une carte coûtant au plus 5 pièces."){};

void Festin::utiliser(Joueur& J, Plateau& P) {
    
    try {

        //Horrible

        const Carte* carteVoulue = P.getCarteParNom(J.demanderNomCarte());
        J.obtenirCartePlateau(carteVoulue, P, Emplacement::DEFAUSSE);

        while(P.getCarteParNom(J.demanderNomCarte()) == nullptr){
            P.getCarteParNom(J.demanderNomCarte());
        }

        J.obtenirCartePlateau(carteVoulue, P, Emplacement::DEFAUSSE);


    } catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    P.ajoutRebut(this);
}
