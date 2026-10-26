#include "actionAttaque.hpp"

std::vector<Joueur*> ActionAttaque::determinerCibles(Joueur& attaquant, Plateau& P, const Carte* carteAttaque) const {

    std::vector<Joueur*> cibles;
    
    for (Joueur& j : P.getJoueurs()) {

        if (&j != &attaquant) {
            if (!j.reagirAttaque(carteAttaque, P)) cibles.push_back(&j);
        }
    }
    return cibles;
}