#pragma once

#include "actionAttaque.hpp"

class Voleur : public ActionAttaque {
    //Creer une map temporaire qui relie chaque joueurs à ses cartes montrés
    //Clé nom joueur value les cartes
    //Le voleur choisis son trésor dans un vector des trésor disponible
    //Tous les autres trésor sont mis au rebut
    //Les joueurs peuvent chacun défausser les cartes qu'ils ont montré

    //Finalement pas besoin de faire la map de merde
    //On va juste faire un vector de trésor pour le voleur, toutes les autres cartes sont défaussés
    
    public :
        Voleur();
        ~Voleur();

        void utiliser(Joueur& J, Plateau& P);
};