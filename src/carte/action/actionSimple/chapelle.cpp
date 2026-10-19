#include "chapelle.hpp"
#include "UI_terminal.hpp"

Chapelle::Chapelle() : ActionSimple("Chapelle", 2, "Écartez jusqu'à 4 cartes de votre main.") {}

Chapelle::~Chapelle() {}

void Chapelle::utiliser(Joueur& J, Plateau& P) const {

    size_t nbCartesEcartees = 0;

    while(nbCartesEcartees < 4){

        if(UI::choixOuiNon("Voulez-vous écarter une carte ?")) {
            std::vector<size_t> idxChoix = UI::choixParmiCartes(J,J.getMain(), 1);
            if (!idxChoix.empty()) {

                J.ecarter(J.getMain().at(idxChoix.at(0))->getNom(), P);
                nbCartesEcartees++;
            }

        } else {
            
            return;
        }   
    }
}