#include "actionAttaque.hpp"

std::vector<Joueur*> ActionAttaque::determinerCibles(Joueur& attaquant, Plateau& P) const {

    std::vector<Joueur*> cibles;
    
    for (Joueur& j : P.getJoueurs()) {

        if (&j != &attaquant) {
            if (!j.reagirAttaque(*this, P)) cibles.push_back(&j);
        }
    }
    return cibles;
}