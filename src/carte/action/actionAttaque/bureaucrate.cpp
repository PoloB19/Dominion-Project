#include "bureaucrate.hpp"
#include "UI_terminal.hpp"

Bureaucrate::Bureaucrate() : ActionAttaque("Bureaucrate", 4, "Gagnez une carte Argent, placez-la sur le dessus de votre pioche. \nChaque autre joueur révèle une carte Victoire et la place sur le dessus de sa pioche (ou révèle une main sans cartes Victoire).") {}
Bureaucrate::~Bureaucrate() {}

void Bureaucrate::utiliser(Joueur& J, Plateau& P) const {

    J.obtenirCartePlateau(P.getCarteParNom("Argent"), P, Emplacement::PIOCHE);
    
    for (Joueur& j : P.getJoueurs()){
        
        if (&j != &J){
            
            std::vector<const Carte*> mainj = j.getMain();
            std::vector<const Carte*> victoireEnMain;
            for (const Carte* c : mainj) {
                if (c->getType()=="Victoire" || c->getSousType() == "ActionVictoire") {
                    victoireEnMain.push_back(c);
                }
            }
            
            if(victoireEnMain.empty()) {
                // si le joueur ne possède pas de carte victoire
                UI::annonceRevelerCartes(J,mainj);
            }
            else {
                // s'il en possède au moins une
                std::vector<size_t> idCarteChoisie = UI::choixParmiCartes(j,victoireEnMain,1);
                UI::annonceRevelerCartes(J,{victoireEnMain.at(idCarteChoisie.at(0))});
                j.enleverDepuisMain(victoireEnMain.at(idCarteChoisie.at(0))->getNom(),Emplacement::PIOCHE);
            }
        }
    }
}