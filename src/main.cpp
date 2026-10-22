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

// CREATION COMPOSITIONS
void initCompo() {
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
}

int main(){
       
    initCompo();

    // VARIABLES GLOBALES 
    Plateau P = Plateau({},0);
    size_t numJoueur = 0;
    Ecran ecran = Ecran::ACCUEIL;

    // DÉMARRAGE DU JEU
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
                ecran = Ecran::TOUR_JOUEUR_ACTION;
                break;
            case 0 :
                ecran = Ecran::QUITTER_JEU;
                break;
            }
            break;

        case Ecran::NOUVELLE_PARTIE :
        {
            size_t choix = UI::ecranNouvellePartie();
            if (choix > 0 && choix <= Plateau::getCompositions().size()) {
                P = Plateau(UI::ecranChoixJoueurs(),choix-1);
                if (P.getJoueurs().empty()){
                    ecran = Ecran::NOUVELLE_PARTIE;
                } else {
                    ecran = Ecran::MODE_RAPIDE;
                }
            }
            else if (choix == Plateau::getCompositions().size()+1) {
                ecran = Ecran::CREATION_COMPOSITION;
            }
            else {
                ecran = Ecran::ACCUEIL;
            }
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
                Plateau::addComposition(Composition("Composition Personnelle",newCompo));
                P = Plateau(UI::ecranChoixJoueurs(),Plateau::getCompositions().size()-1);

                if (P.getJoueurs().empty()){
                    ecran = Ecran::NOUVELLE_PARTIE;
                } else {   
                    ecran = Ecran::MODE_RAPIDE;
                }

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
                ecran = Ecran::NOUVELLE_PARTIE;
                break;
            }
            break;

        case Ecran::COMPO_ALEATOIRE :
        {
            Composition newCompo = Composition ("tmp",{});
            switch (UI::ongletChoixAleatoireCartesComposition(newCompo))
            {
                case 1 :
                    Plateau::addComposition(newCompo);
                    P = Plateau(UI::ecranChoixJoueurs(),Plateau::getCompositions().size()-1);

                    if (P.getJoueurs().empty()){
                    ecran = Ecran::NOUVELLE_PARTIE;
                    } else {   
                        ecran = Ecran::MODE_RAPIDE;
                    }
                    
                    break;
                case 2 :
                    // on revient sur l'écran compo_aléatoire donc pas de changement de ecran
                    break;
                case 0 :
                    ecran = Ecran::CREATION_COMPOSITION;
                    break;
            }
            break;
        }

        case Ecran::MODE_RAPIDE :

            if (UI::ecranModeRapide()) {
                P.setModeRapide();
            }
            UI::ecranMessageDemarragePartie();
            ecran = Ecran::TOUR_JOUEUR_ACTION;
            break;

        case Ecran::TOUR_JOUEUR_ACTION :
        {
            if (numJoueur == P.getJoueurs().size()) {numJoueur = 0;}
            Joueur& J = P.getJoueurs().at(numJoueur);

            switch (UI::ecranTourJoueur(P.getJoueurs().at(numJoueur),P,0)) 
            {
            case 1 :
                UI::ongletDescriptionCartes(Cartes::catalogue());
                break;
            case 2 :
            {
                std::vector<size_t> idxCarte = UI::choixParmiCartes(J,J.getMain(),1);
                if (!idxCarte.empty()) {
                    J.utiliserCarte(P,J.getMain().at(idxCarte.at(0)));
                }
                break;
            }
            case 3 : 
            {
                std::vector<size_t> idxCarte = UI::choixParmiCartes(J,J.getMain(),1);
                if (!idxCarte.empty()) {
                    J.ecarter(J.getMain().at(idxCarte.at(0))->getNom(),P,true);
                }
                break;
            }
            case 4 :
                ecran = Ecran::TOUR_JOUEUR_ACHAT;
                break;
            case 0 :
                ecran = Ecran::QUITTER_PARTIE;
                break;
            }
            break;
        }

        case Ecran::TOUR_JOUEUR_ACHAT :
        {
            Joueur& J = P.getJoueurs().at(numJoueur);
            J.compterPiecesEnMain(P);

            switch (UI::ecranTourJoueur(J,P,1)) 
            {
            case 1 :
                UI::ongletDescriptionCartes(Cartes::catalogue());
                break;
            case 2 :
            {
                const Carte* carteAchat = UI::choixParmiPiles(P);
                if (carteAchat != nullptr) J.acheter(carteAchat,P);
                break;
            }
            case 3 :
                J.finDeTour();
                numJoueur++;
                if (P.checkerEndCondition()) {
                    UI::ecranFinDePartie(P);
                    ecran = Ecran::ACCUEIL;
                }
                else ecran = Ecran::TOUR_JOUEUR_ACTION;
                break;
            case 0 :
                ecran = Ecran::QUITTER_PARTIE;
                break;
            }
            break;
        }

        case Ecran::QUITTER_PARTIE :
            switch (UI::ecranQuitterPartie())
            {
            case 1 :
                // sauvegarder A FAIRE
                // fall through
            case 2 :
                ecran = Ecran::ACCUEIL;
                break;
            case 0 :
                ecran = Ecran::TOUR_JOUEUR_ACTION;
                break;
            }
            break;

        case Ecran::QUITTER_JEU :
            return 0;
        }
    }

    return 0;
}

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
