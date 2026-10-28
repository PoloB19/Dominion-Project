#include "sorciere.hpp"

Sorciere::Sorciere() : ActionAttaque("Sorcière", 5, "+2 Cartes \nTous les autres joueurs obtiennent une carte Malédiction.") {}

Sorciere::~Sorciere() {}

void Sorciere::utiliser(Joueur& J, Plateau& P) const {

    J.piocher(2);
    
    std::vector<Joueur*> ciblesAttaque = ActionAttaque::determinerCibles(J, P, this);
    for (Joueur* cible : ciblesAttaque){

        if (cible == nullptr) continue; // Sécurité
        Joueur& j = *cible; // On transforme le pointeur en référence

        j.obtenirCartePlateau(P.getCarteParNom("Malediction"), P, Emplacement::DEFAUSSE);
    }
}