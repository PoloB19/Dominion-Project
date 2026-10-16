#include "milice.hpp"

Milice::Milice() : ActionAttaque("Milice", 4, "+2 pièces \nTous les autres joueurs doivent défausser des cartes jusqu'à n'en avoir que 3 en main.") {}

Milice::~Milice() {}

void Milice::utiliser(Joueur& J, Plateau& P) const {
    J.ajustNbPiece(2);
    for (Joueur* j : P.getJoueurs()){
    
        if (!(j == &J)){
            
            std::vector<const Carte*> mainj = j->getMain();
            
            while (mainj.size()>3) {
                /*
                size_t idCarteChoisie = j->choixParmiCartes(mainj,1).at(0);
                j->enleverDepuisMain(victoireEnMain.at(idCarteChoisie.at(0))->getNom(),Emplacement::PIOCHE);
                j->annonceRevelerCartes({victoireEnMain.at(idCarteChoisie.at(0))});
                j->annonceCarteVers(victoireEnMain.at(idCarteChoisie.at(0))->getNom(),Emplacement::PIOCHE);
            */}
        }
    }
}

