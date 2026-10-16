#include "renovation.hpp"

Renovation::Renovation() : ActionSimple("Rénovation", 4, "Écartez une carte de votre main. \nObtenez une carte coûtant jusqu'à 2 Pièces de plus que la carte écartée.") {}

Renovation::~Renovation() {}

void Renovation::utiliser(Joueur& , Plateau &) const {

    std::vector<size_t> idxChoix = J.choixParmiCartes(J.getMain(),1);
    if (!idxChoix.empty()) {

        //on récupère le prix max de la nouvelle carte avant d'écarter l'ancienne
        unsigned short prixMax = J.getMain().at(idxChoix.at(0))->getPrix() + 2; 
        J.ecarter(J.getMain().at(idxChoix.at(0))->getNom(), P);

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
    }
}