#include "chambreDuConseil.hpp"

ChambreDuConseil::ChambreDuConseil() : ActionSimple("Chambre du conseil", 5, "+4 cartes \n+1 achat \nTous les autres joueurs piochent une carte.") {}

ChambreDuConseil::~ChambreDuConseil() {}

void ChambreDuConseil::utiliser(Joueur& J, Plateau& P) const {

    for (Joueur& j : P.getJoueurs()){
        j.piocher(1);
    }

    // Le joueur a déjà pioché 1 fois à la boucle précédente
    J.piocher(3);
    J.ajustNbAchat(+1);

}