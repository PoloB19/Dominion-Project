#include "festin.hpp"

Festin::Festin() : ActionSimple("Festin", 4, "Écartez cette carte. \nObtenez une carte coûtant au plus 5 pièces."){}

Festin::~Festin() {}

void Festin::utiliser(Joueur& J, Plateau& P) {

    // Vérification qu'il existe encore une cartes coûtant au plus 5 pièces sur le plateau

    bool gainPossible = false;
    for (const auto& pair : P.getPiles()) {
        if (pair.second > 0 && pair.first->getPrix() <= 5) {
            gainPossible = true;
            break; //On a trouvé une pile valable
        }
    } 
    if (!gainPossible) {
        J.annonceErreur("aucune carte coûtant au plus 5 n'est disponible sur le plateau.");
        P.ajoutRebut(this);
        return;
    }

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
