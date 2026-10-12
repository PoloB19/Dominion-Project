#include "preteurSurGages.hpp"

PreteurSurGages::PreteurSurGages() : ActionSimple("Prêteur sur gages", 4, "Vous pouvez écarter un Cuivre de votre main. \nSi vous le faites, gagnez 3 pièces.") {}

PreteurSurGages::~PreteurSurGages() {}
/*
void PreteurSurGages::utiliser(Joueur& J, Plateau& P){

    if(J.demanderOuiNon("voulez vous défausser un Cuivre de votre main ?")){
        
        for (Carte* c : J.getMain()){

            if (c->getNom() == "Cuivre"){
                J.ecarter(c, P)
            }


        }
        
    }
}
*/