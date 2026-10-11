#include "atelier.hpp"

Atelier::Atelier() : ActionSimple("Atelier", 3, "Obtenez une carte coûtant au plus 4 pièces.") {};

void Atelier::utiliser(Joueur &J, Plateau &P){

    std::cout << "Vous pouvez obtenir une carte du plateau coûtant au plus 4 pièces." << std::endl;

    while(true){

        const Carte* carteVoulue = P.getCarteParNom(J.demanderNomCarte());

        if (carteVoulue->getPrix() > 4){

            std::cout << "Cette carte dépasse la valeur autorisé (max. 4);" << std::endl;

        } else {

            J.obtenirCartePlateau(carteVoulue, P, Emplacement::DEFAUSSE);

        }

    }

}