#include "douves.hpp"
#include "UI_terminal.hpp"

Douves::Douves() : ActionReaction("Douves", 2, "+2 Cartes \nLorsqu'un autre joueur utilise une carte Attaque, vous pouvez révéler cette carte de votre main pour ne pas en être affecté.") {}

Douves::~Douves() {}

void Douves::utiliser(Joueur& J, Plateau&) const {
    J.piocher(2);
} 

bool Douves::reagir(Joueur& cible, const Carte* carteAttaque, Plateau&) const {
    if (UI::choixOuiNon("voulez-vous dévoiler Douves pour vous protéger de " + carteAttaque->getNom() + " ?")) {
        UI::annonceRevelerCartes(cible,{this});
        return true;   // immunisé
    }
    return false;
}