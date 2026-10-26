#include "renovation.hpp"
#include "UI_terminal.hpp"

Renovation::Renovation() : ActionSimple("Rénovation", 4, "Écartez une carte de votre main. \nObtenez une carte coûtant jusqu'à 2 Pièces de plus que la carte écartée.") {}

Renovation::~Renovation() {}

void Renovation::utiliser(Joueur& J, Plateau& P) const {

    std::vector<size_t> idxChoix = UI::choixParmiCartes(J,J.getMain(),1);
    if (!idxChoix.empty()) {

        //on récupère le prix max de la nouvelle carte avant d'écarter l'ancienne
        unsigned short prixMax = J.getMain().at(idxChoix.at(0))->getPrix() + 2; 
        J.ecarter(J.getMain().at(idxChoix.at(0))->getNom(), P, Emplacement::MAIN);

        const Carte* carteVoulue;
        while (true){

            carteVoulue = UI::choixParmiPiles(P);

            if (carteVoulue->getPrix() > prixMax){

                UI::annonceErreur("cette carte est trop chère");

            } else {

                J.obtenirCartePlateau(carteVoulue, P, Emplacement::DEFAUSSE);
                return;

            }
        }
    }
}