#include "sorciere.hpp"

Sorciere::Sorciere() : ActionAttaque("Sorcière", 5, "+2 Cartes \nTous les autres joueurs obtiennent une carte Malédiction.") {}

Sorciere::~Sorciere() {}

void Sorciere::utiliser(Joueur& J, Plateau& P) const {

    J.piocher(2);

    for (Joueur* cible : P.getJoueurs()){
        if (cible != &J){
            cible->obtenirCartePlateau(P.getCarteParNom("Malédiction"), P, Emplacement::DEFAUSSE);
        }
    }
}