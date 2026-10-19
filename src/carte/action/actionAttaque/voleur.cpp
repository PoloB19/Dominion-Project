#include "voleur.hpp"
#include "UI_terminal.hpp"

Voleur::Voleur() : ActionAttaque("Voleur", 4, "Tous vos adversaires dévoilent les 2 premières cartes de leur deck.\nS'ils dévoilent des cartes Trésor, ils en écartent une de votre choix. Parmi ces cartes Trésor écartées, recevez celles de votre choix. Les autres cartes dévoilées sont défaussées.") {}
Voleur::~Voleur() {}

void Voleur::utiliser(Joueur& J, Plateau& P) const {

    // vecteur contenant les cartes écartées par le voleur
    std::vector<const Carte*> cartesEcartees;

    std::vector<const Carte*> tresorReveles = {};
    const Carte* carteRevelee;

    for (Joueur* j : P.getJoueurs()) {

        if (!(j == &J)){

            // IL FAUT GERER LE CAS OU UN JOUEUR POSSEDE DOUVES OU DES REACTIONS EN GENERAL car on ne révèle pas ses cartes. gérer par le plateau ?

            // On révèle les 2 cartes de la pioche d'un joueur
            carteRevelee = j->revelerCarte(Emplacement::PIOCHE);
            if (carteRevelee->getType() == "Tresor") {
                tresorReveles.push_back(carteRevelee);
            }
            else {
                j->ajouterADefausse(carteRevelee);
            }

            carteRevelee = j->revelerCarte(Emplacement::PIOCHE);
            if (carteRevelee->getType() == "Tresor") {
                tresorReveles.push_back(carteRevelee);
            }
            else {
                j->ajouterADefausse(carteRevelee);
            }
        
            // Si seulement une des 2 cartes révélées était un trésor, on l'écarte.
            if (tresorReveles.size() == 1) {
                cartesEcartees.push_back(tresorReveles.at(0));
            }
            // Sinon on laisse au voleur le choix entre les 2
            else if (tresorReveles.size() == 2) {
                UI::afficherInformation("Quelle carte de " + j->getPseudo() + " écartez-vous ?");
                size_t idxChoix = UI::choixParmiCartes(J,tresorReveles,1).at(0);
                cartesEcartees.push_back(tresorReveles.at(idxChoix));

                // la carte trésor non-selectionnée par le voleur est remise dans la défausse du joueur
                for (size_t i = 0; i<tresorReveles.size(); i++) {
                    if (i!=idxChoix) {
                        j->ajouterADefausse(tresorReveles.at(i));
                    }
                }
            }
        }
    }
    if (cartesEcartees.size()==0) {
        UI::afficherInformation("Vous n'avez rien à voler.\n"); 
    }
    else {
        UI::afficherInformation("Voici les cartes que vous venez d'écarter..."); 
        size_t idxChoix = UI::choixParmiCartes(J,cartesEcartees,1).at(0);
        J.ajouterADefausse(cartesEcartees.at(idxChoix));
        cartesEcartees.erase(cartesEcartees.begin() + idxChoix);
        for (const Carte* c : cartesEcartees) {
            P.ajoutRebut(c);
        }
    }
}