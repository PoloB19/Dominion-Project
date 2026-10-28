#include "cave.hpp"
#include "UI_terminal.hpp"

Cave::Cave() : ActionSimple("Cave", 2, "+1 Action \nDéfaussez autant de carte que vous le souhaitez. +1 Carte par carte défaussée.") {}

Cave::~Cave() {}

void Cave::utiliser(Joueur& J,  Plateau&) const {

    J.ajustNbAction(+1);

    unsigned short compt_tmp = 0;

    while(UI::choixOuiNon("Souhaitez-vous défausser une carte ?") && J.getMain().size()!=0){

        size_t idxChoix = UI::choixParmiCartes(J,J.getMain(),1).at(0);
        J.enleverDepuisMain(J.getMain().at(idxChoix)->getNom(),Emplacement::DEFAUSSE);
        compt_tmp ++;
        UI::annonceCarteDepuis(J.getPioche().top()->getNom(),Emplacement::PIOCHE);
    }

    J.piocher(compt_tmp);
}