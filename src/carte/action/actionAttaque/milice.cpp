#include "milice.hpp"

Milice::Milice() : ActionAttaque("Milice", 4, "+2 pièces \nTous les autres joueurs doivent défausser des cartes jusqu'à n'en avoir que 3 en main.") {}

Milice::~Milice() {}

void Milice::utiliser(Joueur& J, Plateau& P) const {
    J.ajustNbPiece(2);
    /*
    for (Joueur* j : P.getJoueurs()){
    
        if (!(j == &J)){
            
            std::vector<const Carte*> mainj = j->getMain();
            std::vector<const Carte*> victoireEnMain;
            for (const Carte* c : mainj) {
                if (c->getType()=="Victoire" || c->getSousType() == "ActionVictoire") {
                    victoireEnMain.push_back(c);
                }
            }
            
            if(victoireEnMain.empty()) {
                // si le joueur ne possède pas de carte victoire
                j->annonceRevelerCartes(mainj);
            }
            else {
                // s'il en possède au moins une
                std::vector<size_t> idCarteChoisie = j->choixParmiCartes(victoireEnMain,1);
                j->enleverDepuisMain(victoireEnMain.at(idCarteChoisie.at(0))->getNom(),Emplacement::PIOCHE);
                j->annonceRevelerCartes({victoireEnMain.at(idCarteChoisie.at(0))});
                j->annonceCarteVers(victoireEnMain.at(idCarteChoisie.at(0))->getNom(),Emplacement::PIOCHE);
            }
        }
    }
        */
}

