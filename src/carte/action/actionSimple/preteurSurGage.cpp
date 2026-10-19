#include "preteurSurGages.hpp"
#include "UI_terminal.hpp"

PreteurSurGages::PreteurSurGages() : ActionSimple("Prêteur sur gages", 4, "Vous pouvez écarter un Cuivre de votre main. \nSi vous le faites, gagnez 3 pièces.") {}

PreteurSurGages::~PreteurSurGages() {}

void PreteurSurGages::utiliser(Joueur& J, Plateau& P) const {

    if(UI::choixOuiNon("Voulez-vous écarter un Cuivre de votre main ?")){
        
        for (const Carte* c : J.getMain()){

            if (c->getNom() == "Cuivre"){
                J.ecarter(c->getNom(), P);
                J.ajustNbPiece(3);
                return;
            }

        } 

        UI::annonceErreur("vous n'avez pas de carte Cuivre dans votre main");
        UI::retourALigne();
        return;
    }
}
