#include "voleur.hpp"

Voleur::Voleur() : ActionAttaque(4, "Tous les autres joueurs révélent les 2 première cartes de leur deck. \ni l'un de ces joueurs a dévoilé une ou plusieurs cartes Trésor (Cuivre, Argent, Or), vous choisissez laquelle de ces cartes il écarter du jeu. Si deux cartes Trésor sont dévoilées chez un même joueur, vous choisissez laquelle est éliminée. \nVous pouvez prendre n'importe laquelle, ou la totalité, des cartes Trésor ainsi éliminées et les placer dans votre propre défausse. \nToutes les autres cartes dévoilées (Trésor non choisis et cartes non-Trésor) sont défaussées par les joueurs.", 0, 0) {}

void Voleur::utiliser(const Plateau& P, size_t idJoueur){
    //A FAIRE
}