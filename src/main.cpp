#include "dominion.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <map>

enum Ecran {
    ACCUEIL,
    NOUVELLE_PARTIE,
    CREATION_COMPOSITION,
    COMPO_ALEATOIRE,
    MODE_RAPIDE,
    TOUR_JOUEUR_ACTION,
    TOUR_JOUEUR_ACHAT,
    QUITTER_PARTIE,
    QUITTER_JEU
};


int main(){
       
    // CREATION COMPOSITIONS
    std::vector<Composition> compositions;

    compositions.push_back(Composition("Les premières parties", {
        {Cartes::atelier(),10},
        {Cartes::bucheron(),10},
        {Cartes::cave(),10},
        {Cartes::douves(),10},
        {Cartes::forgeron(),10},
        {Cartes::marche(),10},
        {Cartes::milice(),10},
        {Cartes::mine(),10},
        {Cartes::renovation(),10},
        {Cartes::village(),10},
    }));
    compositions.push_back(Composition("Richesses et trésor", { 
        {Cartes::aventurier(),10},
        {Cartes::bureaucrate(),10},
        {Cartes::chancelier(),10},
        {Cartes::chapelle(),10},
        {Cartes::festin(),10},
        {Cartes::laboratoire(),10},
        {Cartes::marche(),10},
        {Cartes::mine(),10},
        {Cartes::preteurSurGages(),10},
        {Cartes::salleDuTrone(),10}, 
    }));
    compositions.push_back(Composition("Interaction", { 
        {Cartes::bibliotheque(),10},
        {Cartes::bureaucrate(),10},
        {Cartes::chambreDuConseil(),10},
        {Cartes::chancelier(),10},
        {Cartes::douves(),10},
        {Cartes::espion(),10},
        {Cartes::festival(),10},
        {Cartes::milice(),10},
        {Cartes::village(),10},
        {Cartes::voleur(),10}, 
    }));
    compositions.push_back(Composition("Changement de taille", { 
        {Cartes::atelier(),10},
        {Cartes::bucheron(),10},
        {Cartes::cave(),10},
        {Cartes::chapelle(),10},
        {Cartes::festin(),10},
        {Cartes::jardins(),10},
        {Cartes::laboratoire(),10},
        {Cartes::sorciere(),10},
        {Cartes::village(),10},
        {Cartes::voleur(),10}, 
    }));
    compositions.push_back(Composition("Place du village", { 
        {Cartes::bibliotheque(),10},
        {Cartes::bucheron(),10},
        {Cartes::bureaucrate(),10},
        {Cartes::cave(),10},
        {Cartes::festival(),10},
        {Cartes::forgeron(),10},
        {Cartes::marche(),10},
        {Cartes::renovation(),10},
        {Cartes::salleDuTrone(),10},
        {Cartes::village(),10}, 
    }));

    Plateau::setCompositions(compositions);


    // VARIABLES GLOBALES 
    Plateau P = Plateau({},0);
    size_t numJoueur = 0;

    Ecran ecran = Ecran::ACCUEIL;


    // DEMARRAGE DU JEU
    while (true) {

        switch (ecran) 
        {
        case Ecran::ACCUEIL :

            switch (UI::ecranAccueil()) 
            {
            case 1 : 
                ecran = Ecran::NOUVELLE_PARTIE;
                break;
            case 2 :
                // faire ce qui est fait quand reprise de sauvegarde
                UI::ecranMessageDemarragePartie(true);
                ecran = Ecran::TOUR_JOUEUR;
                break;
            case 0 :
                ecran = Ecran::QUITTER_JEU;
                break;
            }
            break;

        case Ecran::NOUVELLE_PARTIE :
        {
            size_t choix = UI::ecranNouvellePartie();
            if (choix > 0 && choix < 6) {
                P = Plateau(UI::ecranChoixJoueurs(),choix-1);
                ecran = Ecran::MODE_RAPIDE;
            }
            else if (choix == 6) {
                ecran = Ecran::CREATION_COMPOSITION;
            }
            else {
                ecran = Ecran::ACCUEIL;
            }
            /* j'ai pas mis de switch ici parce que redondant sinon :
            switch (UI::ecranNouvellePartie()) 
            {
                case 1 :
                    P = Plateau(UI::ecranChoixJoueurs(),0);
                    ecran = Ecran::MODE_RAPIDE;
                    break;
                case 2 :
                    P = Plateau(UI::ecranChoixJoueurs(),1);
                    ecran = Ecran::MODE_RAPIDE;
                    break;
                case 3 :
                    P = Plateau(UI::ecranChoixJoueurs(),2);
                    ecran = Ecran::MODE_RAPIDE;
                    break;
                case 4 :
                    P = Plateau(UI::ecranChoixJoueurs(),3);
                    ecran = Ecran::MODE_RAPIDE;
                    break;
                case 5 :
                    P = Plateau(UI::ecranChoixJoueurs(),4);
                    ecran = Ecran::MODE_RAPIDE;
                    break;
                case 6 :
                    ecran = Ecran::CREATION_COMPOSITION;
                    break;
                case 0 :
                    ecran = Ecran::ACCUEIL;
                    break;
            }
            */
            break;
        }

        case Ecran::CREATION_COMPOSITION :

            switch (UI::ecranCreationComposition()) 
            {
            case 1 :
            {
                Joueur j_tmp = Joueur("Joueurs");
                std::vector<size_t> idCartesCompo = UI::ongletChoixCartesComposition(j_tmp);
                if (idCartesCompo.empty()) {
                    ecran = Ecran::ACCUEIL;
                    break;
                }
                std::map<const Carte*, unsigned short> newCompo;
                for (auto idCarte : idCartesCompo) {
                    newCompo.insert({Cartes::royaume().at(idCarte),10});
                }
                Plateau::addComposition(Composition("CompoTemporaire",newCompo));
                P = Plateau(UI::ecranChoixJoueurs(),Plateau::getCompositions().size()-1);
                
                ecran = Ecran::MODE_RAPIDE;
                break;
            }
            case 2 :
                ecran = Ecran::COMPO_ALEATOIRE;
                break;
            case 3 :
                UI::ongletDescriptionCartes(Cartes::royaume());
                // on ne change pas la valeur de la variable écran pour revenir dans ce menu
                break;
            case 0 :
                ecran = Ecran::ACCUEIL;
                break;
            }
            break;

        case Ecran::COMPO_ALEATOIRE :
        {
            Composition newCompo;
            switch (UI::ongletChoixAleatoireCartesComposition(newCompo))
            {
                case 1 :
                    Plateau::addComposition(newCompo);
                    P = Plateau(UI::ecranChoixJoueurs(),Plateau::getCompositions().size()-1);
                    ecran = Ecran::MODE_RAPIDE;
                    break;
                case 2 :
                    // on revient sur l'écran compo_aléatoire
                    break;
                case 0 :
                    ecran = Ecran::ACCUEIL;
                    break;
            }
            break;
        }

        case Ecran::MODE_RAPIDE :

            if (UI::ecranModeRapide()) {
                P.setModeRapide();
            }
            UI::ecranMessageDemarragePartie();
            ecran = Ecran::TOUR_JOUEUR;
            break;

        case Ecran::TOUR_JOUEUR_ACTION :

            if (numJoueur == P.getJoueurs().size()) {numJoueur = 0;}
            switch (UI::ecranTourJoueur(P.getJoueurs().at(numJoueur),P,0)) 
            {
            case 1 :
                UI::ongletDescriptionCartes(Cartes::catalogue());
                break;
            case 2 :
                // utiliser une carte : créer fonction dans joueur, choixParmiCartes de la main concerné
                break;
            case 3 : // ecarter une carte
                UI::
                break;
            case 4 :
                ecran = Ecran::TOUR_JOUEUR_ACHAT;
                break;
            case 0 :
                ecran = Ecran::QUITTER_PARTIE;
                break;
            }
            break;

        case Ecran::TOUR_JOUEUR_ACHAT :

            switch (UI::ecranTourJoueur(P.getJoueurs().at(numJoueur),P,1)) 
            {
            case 1 :
                UI::ongletDescriptionCartes(Cartes::catalogue());
                break;
            case 2 :
                // acheter une carte : créer fonction dans joueur ou UI à voir mais c'est choix piles concernés
                break;
            case 3 :
                P.getJoueurs().at(numJoueur).finDeTour();
                numJoueur++;
                ecran = Ecran::TOUR_JOUEUR_ACTION;
                break;
            case 0 :
                ecran = Ecran::QUITTER_PARTIE;
                break;
            }
            break;

        case Ecran::QUITTER_PARTIE :
            // à faire dans UI
            break;

        case Ecran::QUITTER_JEU :
            return 0;
        }
    }

    return 0;
}


/* ICI UN SKETCH DE COMMENT JE VOIS LE MAIN

int main(){

    ... instanciation de tout ce qui doit être instancié ...
    A limite appeler la fonction barreChargement de UI pour faire stylé

    while(true){ //Pour faire tourner l'écran de démarrage en boucle
    
    switch(ecranDemarrage):
        case 0 : 
            exit()
        case 1 : 

            switch(ecranNouvellePartie):
                case 0 : 
                    break; (car retour au menu du démarrage quoi)
                case 1 :
                    .....
                case 2 : 
                    ...
    
    }
}

OU ALORS on peut aussi faire des "fonctions" qui correspondent aux écrans et qui sont appelées dans les case des switch
Par exemple au lieu d'avoir un autre switch dans le case 1, on appelrait une fonction qui gererait l'écran de nouvelle partie)

C'est des idées par ci par là mais normalement il y a très peu a coder dans le main : 
AUCUNE vérification, AUCUNE variable, AUCUN cas bizarre, AUCUNE fonction utile
--> juste des appels de fonction de UI associé à des switch c'est TOUT

*/


//pour moi il faut 3 variables : joueur J, pateau P, size_t numTour

/* CONTRE PROPOSITION POUR NE PAS ÊTRE DANS UN SWITCH DE SWITCH. enum Ecran

    Ecran ecran;

    switch (ecran) :
        case Ecran::Accueil :
            switch (ecranAccueil()) {
                case 1:
                    ecran = Ecran::NouvellePartie;
                    break;
            }
            break;

        case Ecran::NouvellePartie :
            switch (ecranNouvellePartie()) {
                case 1:
                    ecran = Ecran::NouvellePartie;
                    break;
            }
            break;
                

*/
