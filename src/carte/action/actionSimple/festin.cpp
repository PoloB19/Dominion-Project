#include "festin.hpp"
#include "UI_terminal.hpp"

Festin::Festin() : ActionSimple("Festin", 4, "Utilisez cette carte pour l'écarter. \nObtenez une carte coûtant au plus 5 pièces."){}

Festin::~Festin() {}

void Festin::utiliser(Joueur& J, Plateau& P) const {

    // Vérification qu'il existe encore une carte coûtant au plus 5 pièces sur le plateau

    bool gainPossible = false;
    for (const auto& pair : P.getPiles()) {
        if (pair.second > 0 && pair.first->getPrix() <= 5) {
            gainPossible = true;
            break; //On a trouvé une pile valable
        }
    } 
    if (!gainPossible) {
        UI::annonceErreur("aucune carte coûtant au plus 5 n'est disponible sur le plateau");
        P.ajoutRebut(this);
        return;
    }
    
    J.ecarter(this->getNom(),P,Emplacement::MAIN);

    while(true){

        const Carte* carteVoulue = UI::choixParmiPiles(P);

        if (carteVoulue->getPrix() > 5){

            UI::annonceErreur("cette carte est trop chère");

        } else if (carteVoulue == nullptr){
            
            UI::annonceErreur("cette carte n'existe pas");

        } else {

            J.obtenirCartePlateau(carteVoulue, P, Emplacement::DEFAUSSE);
            P.ajoutRebut(this);
            return;
        }
    }
}
