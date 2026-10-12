#include "bureaucrate.hpp"

Bureaucrate::Bureaucrate() : ActionAttaque("Bureaucrate", 4, "Gagnez une carte Argent, placez-la sur le dessus de votre pioche. \nChaque autre joueur révèle une carte Victoire et la place sur le dessus de sa pioche (ou révèle une main sans cartes Victoire).") {};


void Bureaucrate::utiliser(Joueur& J, Plateau& P){

    J.obtenirCartePlateau(P.getCarteParNom("Argent"), P, Emplacement::PIOCHE);
    
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
}