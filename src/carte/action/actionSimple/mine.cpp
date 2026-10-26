#include "mine.hpp"
#include "UI_terminal.hpp"

Mine::Mine() : ActionSimple("Mine", 5, "Écarter une carte de sa main pour recevoir une carte Trésor valant jusqu'à 3 pièces de plus. \nAjoutez cette carte à votre main.") {}

Mine::~Mine() {}

void Mine::utiliser(Joueur& J, Plateau& P) const {

    UI::afficherInformation("Écartez une carte de votre main.");
    UI::retourALigne();

    std::vector<size_t> idxChoix = UI::choixParmiCartes(J, J.getMain(), 1);
    if (!idxChoix.empty()) {
        //on récupère le prix de la carte avant de l'écarter
        unsigned short prixMax = J.getMain().at(idxChoix.at(0))->getPrix() + 3; 
        J.ecarter(J.getMain().at(idxChoix.at(0))->getNom(), P, Emplacement::MAIN);

        const Carte* carteVoulue;

        while (true) {

            carteVoulue = UI::choixParmiPiles(P);

            if (carteVoulue->getPrix() > prixMax){

                UI::annonceErreur("cette carte est trop chère");

            } 
            else if (carteVoulue->getType() != "Tresor") {

                UI::annonceErreur("cette carte n'est pas un Trésor");

            }
            else {

                J.obtenirCartePlateau(carteVoulue, P, Emplacement::MAIN);
                return;

            }
        }
    }
}
