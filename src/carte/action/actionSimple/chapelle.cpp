#include "chapelle.hpp"

Chapelle::Chapelle() : ActionSimple("Chapelle", 2, "Écartez jusqu'à 4 cartes de votre main.") {}

Chapelle::~Chapelle() {}

void Chapelle::utiliser(Joueur& J, Plateau& P) const {

    size_t nbCartesEcartees = 0;

    while(nbCartesEcartees < 4){

        if(J.demanderOuiNon("Voulez-vous écarter une carte ?")) {
            std::vector<size_t> idxChoix = J.choixParmiCartes(J.getMain(), 1);
            if (!idxChoix.empty()) {

                J.ecarter(J.getMain().at(idxChoix.at(0))->getNom(), P);
                nbCartesEcartees++;
            }

        } else {
            
            return;
        }   
    }
}