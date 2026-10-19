#include "atelier.hpp"
#include "UI_terminal.hpp"

Atelier::Atelier() : ActionSimple("Atelier", 3, "Obtenez une carte coûtant au plus 4 pièces.") {}

Atelier::~Atelier() {}

void Atelier::utiliser(Joueur &J, Plateau &P) const {

    const Carte* carteVoulue;

    while(true){

        carteVoulue = UI::choixParmiPiles(P);

        if (carteVoulue->getPrix() > 4){

            UI::annonceErreur("cette carte dépasse la valeur autorisée (max. 4) ou n'existe pas");

        } else {

            J.obtenirCartePlateau(carteVoulue, P, Emplacement::DEFAUSSE);
            return;
            
        }

    }
}