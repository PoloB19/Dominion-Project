#include "cave.hpp"

Cave::Cave() : ActionSimple("Cave", 2, "+1 Action \nDéfaussez autant de carte que vous le souhaitez. +1 Carte par carte défaussée.") {}

Cave::~Cave() {}

void Cave::utiliser(Joueur& J,  Plateau&) const {

    J.ajustNbAction(+1);

    std::cout << "Vous pourrez piocher autant de carte que vous défaussez." << std::endl;

    unsigned short compt_tmp = 0;

    while(J.demanderOuiNon("souhaitez vous défausser une carte ?")){

        std::string nomCarteSelectionnee = J.demanderNomCarte();
 
        if (!nomCarteSelectionnee.empty() && J.accesMain()) {
            J.enleverDepuisMain(nomCarteSelectionnee,Emplacement::DEFAUSSE);
            compt_tmp ++;
        }
    }

    J.piocher(compt_tmp);
}