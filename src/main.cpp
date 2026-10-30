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
        {Cartes::getCarte<Atelier>(),10},
        {Cartes::getCarte<Bucheron>(),10},
        {Cartes::getCarte<Cave>(),10},
        {Cartes::getCarte<Douves>(),10},
        {Cartes::getCarte<Forgeron>(),10},
        {Cartes::getCarte<Marche>(),10},
        {Cartes::getCarte<Milice>(),10},
        {Cartes::getCarte<Mine>(),10},
        {Cartes::getCarte<Renovation>(),10},
        {Cartes::getCarte<Village>(),10},
    }));
    compositions.push_back(Composition("Richesses et trésor", { 
        {Cartes::getCarte<Aventurier>(), 10},
        {Cartes::getCarte<Bureaucrate>(), 10},
        {Cartes::getCarte<Chancelier>(), 10},
        {Cartes::getCarte<Chapelle>(), 10},
        {Cartes::getCarte<Festin>(), 10},
        {Cartes::getCarte<Laboratoire>(), 10},
        {Cartes::getCarte<Marche>(), 10},
        {Cartes::getCarte<Mine>(), 10},
        {Cartes::getCarte<PreteurSurGages>(), 10},
        {Cartes::getCarte<SalleDuTrone>(), 10}, 
    }));
    compositions.push_back(Composition("Interaction", { 
        {Cartes::getCarte<Bibliotheque>(), 10},
        {Cartes::getCarte<Bureaucrate>(), 10},
        {Cartes::getCarte<ChambreDuConseil>(), 10},
        {Cartes::getCarte<Chancelier>(), 10},
        {Cartes::getCarte<Douves>(), 10},
        {Cartes::getCarte<Espion>(), 10},
        {Cartes::getCarte<Festival>(), 10},
        {Cartes::getCarte<Milice>(), 10},
        {Cartes::getCarte<Village>(), 10},
        {Cartes::getCarte<Voleur>(), 10},
    }));
    compositions.push_back(Composition("Changement de taille", { 
        {Cartes::getCarte<Atelier>(), 10},
        {Cartes::getCarte<Bucheron>(), 10},
        {Cartes::getCarte<Cave>(), 10},
        {Cartes::getCarte<Chapelle>(), 10},
        {Cartes::getCarte<Festin>(), 10},
        {Cartes::getCarte<Jardins>(), 10},
        {Cartes::getCarte<Laboratoire>(), 10},
        {Cartes::getCarte<Sorciere>(), 10},
        {Cartes::getCarte<Village>(), 10},
        {Cartes::getCarte<Voleur>(), 10}, 
    }));
    compositions.push_back(Composition("Place du village", { 
        {Cartes::getCarte<Bibliotheque>(), 10},
        {Cartes::getCarte<Bucheron>(), 10},
        {Cartes::getCarte<Bureaucrate>(), 10},
        {Cartes::getCarte<Cave>(), 10},
        {Cartes::getCarte<Festival>(), 10},
        {Cartes::getCarte<Forgeron>(), 10},
        {Cartes::getCarte<Marche>(), 10},
        {Cartes::getCarte<Renovation>(), 10},
        {Cartes::getCarte<SalleDuTrone>(), 10},
        {Cartes::getCarte<Village>(), 10}, 
    }));

    Plateau::setCompositions(compositions);
}

int main(){
       
    initCompo();

    // VARIABLES GLOBALES 
    Plateau P = Plateau({},0);
    size_t numJoueur = 0;
    Ecran ecran = Ecran::ACCUEIL;
    Ecran dernierEcranTour = Ecran::TOUR_JOUEUR_ACTION;

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
            {
                size_t chargementNumJoueur = 0;
                bool chargementPhase = false;

                if (Sauvegarde::charger(P, chargementNumJoueur, chargementPhase, "sauvegarde.txt")) {
                    numJoueur = chargementNumJoueur;
                    UI::ecranMessageDemarragePartie(true);
                    ecran = chargementPhase ? Ecran::TOUR_JOUEUR_ACHAT : Ecran::TOUR_JOUEUR_ACTION;
                } else {
                    UI::annonceErreur("aucune sauvegarde valide trouvée");
                    UI::sautDeLigne();
                    UI::animationChargement(2);
                    ecran = Ecran::ACCUEIL;
                }
                break;
            }
            case 3 :
                if (Sauvegarde::effacer()){
                    UI::afficherInformation("Votre sauvegarde a bien été effacée.");
                    UI::sautDeLigne();
                    UI::animationChargement(2);
                    ecran = Ecran::ACCUEIL;
                } else {
                    UI::annonceErreur("aucune sauvegarde valide trouvée");
                    UI::sautDeLigne();
                    UI::animationChargement(2);
                    ecran = Ecran::ACCUEIL;
                }
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
            dernierEcranTour = Ecran::TOUR_JOUEUR_ACTION;

            if (numJoueur == P.getJoueurs().size()) {numJoueur = 0;}
            Joueur& J = P.getJoueurs().at(numJoueur);

            switch (UI::ecranTourJoueur(P.getJoueurs().at(numJoueur),P,0)) 
            {
            case 1 :
                UI::ongletDescriptionCartes(Cartes::catalogue());
                break;
            case 2 :
            {
                std::vector<size_t> idxCarte = UI::choixParmiCartes(J,J.getMain(),1,"Retour");
                if (!idxCarte.empty()) {
                    J.utiliserCarte(P,J.getMain().at(idxCarte.at(0)));
                }
                break;
            }
            case 3 : 
            {
                std::vector<size_t> idxCarte = UI::choixParmiCartes(J,J.getMain(),1,"Retour");
                if (!idxCarte.empty()) {
                    J.ecarter(J.getMain().at(idxCarte.at(0))->getNom(),P,Emplacement::MAIN,true);
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
            dernierEcranTour = Ecran::TOUR_JOUEUR_ACHAT;

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
            case 1 : {
                bool phaseAchat = (dernierEcranTour == Ecran::TOUR_JOUEUR_ACHAT);
                if (Sauvegarde::sauvegarder(P, numJoueur, phaseAchat, "sauvegarde.txt")) {
                    UI::afficherInformation(UI::BLUE + "Partie sauvegardée avec succès !" + UI::RESET);
                    UI::sautDeLigne();
                    UI::animationChargement(2);
                } else {
                    UI::annonceErreur("échec de la sauvegarde");
                    UI::sautDeLigne();
                    UI::animationChargement(2);
                }
                ecran = Ecran::ACCUEIL;
                break;
            }
            case 2 :
                ecran = Ecran::ACCUEIL;
                break;
            case 0 :
                ecran = dernierEcranTour;
                break;
            }
            break;

        case Ecran::QUITTER_JEU :
            return 0;
        }
    }

    return 0;
}
