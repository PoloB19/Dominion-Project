#include "mine.hpp"

Mine::Mine() : ActionSimple("Mine", 5, "Écarter une carte de sa main pour recevoir une carte Trésor valant jusqu'à 3 pièces de plus. \nLa carte reçue est immédiatement utilisable.") {}

Mine::~Mine() {}

void Mine::utiliser(Joueur& J, Plateau& P) const {

    size_t idxChoix = J.choixParmiCartes(J.getMain(),1).at(0);
    if (!idxChoix.empty()) {
        //on récupère le prix de la carte avant de l'écarter
        unsigned short prixMax = J.getMain().at(idxChoix)->getPrix() + 3; 
        J.ecarter(J.getMain().at(idxChoix)->getNom(), P);

        const Carte* carteVoulue;
        while (true){

            carteVoulue = P.getCarteParNom(J.demanderNomCarte());

            if (carteVoulue->getPrix() > prixMax){

                J.annonceErreur("cette carte est trop chère");

            } else if (carteVoulue == nullptr){
                
                J.annonceErreur("cette carte n'existe pas");

            } else {

                J.obtenirCartePlateau(carteVoulue, P, Emplacement::DEFAUSSE);
                return;

            }
        }

        if (J.demanderOuiNon("Souhaitez-vous utiliser cette nouvelle carte ?")){
            
            carteVoulue->utiliser(J,P);
        }
    }
}
