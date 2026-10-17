#include "voleur.hpp"

Voleur::Voleur() : ActionAttaque("Voleur", 4, "Tous vos adversaires dévoilent les 2 premières cartes de leur deck.\nS'ils dévoilent des cartes Trésor, ils en écartent une de votre choix. Parmis ces cartes Trésor écartées, recevez celles de votre choix. Les autres cartes dévoilées sont défaussées.") {}
Voleur::~Voleur() {}

// IL FAUDRAIT QU'ON AJOUTE UNE FONCTION DANS L'UI QUI PERMET DE FAIRE UN CHOIX PARMI DES CARTES ET QUE CA AFFICHE A QUEL JOUEUR APPARTIENT LA CARTE

void Voleur::utiliser(Joueur& J, Plateau& P) const {

    // vecteur contenant les paires (joueur, carte écartée par le voleur)
    std::vector<(Joueur*, const Carte*)> cartesEcartees;

    std::vector<const Carte*> tresorReveles = {};
    const Carte* carteRevelee;

    for (Joueur* j : P.getJoueurs()) {

        if (!(j == &J)){

            // IL FAUT GERER LE CAS OU UN JOUEUR POSSEDE DOUVES OU DES REACTIONS EN GENERAL car on ne révèle pas ses cartes. gérer par le plateau !

            // On révèle les 2 cartes de la pioche d'un joueur
            carteRevelee = j->revelerCarte(Emplacement::PIOCHE);
            if (carteRevelee->getType() == "Tresor") {
                tresorReveles.push_back(carteRevelee);
            }
            else {
                j->ajouterADefausse(carteRevelee);
            }

            carteRevelee = j->revelerCarte(Emplacement::PIOCHE);
            if (carteRevelee->getType() == "Tresor") {
                tresorReveles.push_back(carteRevelee);
            }
            else {
                j->ajouterADefausse(carteRevelee);
            }
        
            // Si seulement une des 2 cartes révélées était un trésor, on l'écarte.
            if (tresorReveles.size() == 1) {
                cartesEcartees.push_back(j,tresorReveles.at(0));
            }
            // Sinon on laisse au voleur le choix entre les 2
            else if (tresorReveles.size() == 2) {
                //voir pour ce cout comment faire pour que ça passe par UI ou s'il est vrm nécessaire ?
                std::cout << "Quelle carte de " << j->getPseudo() << " écartez-vous ?" << std::endl;
                size_t idxChoix = J.choixParmiCartes(tresorReveles,1).at(0);
                cartesEcartees.push_back(j,tresorReveles.at(idxChoix));

                // la carte trésor non-selectionnée par le voleur est remise dans la défausse du joueur
                for (size_t i = 0; i<tresorReveles.size(); i++) {
                    if (i!=idxChoix) {
                        j->ajouterADefausse(tresorReveles.at(i));
                    }
                }
            }
        }
    }
    // Toutes les cartes écartées ont été réunies. Il faut maintenant que le voleur choississe celle qu'il vole
    // PROBLEME LA FONCTION UI POUR LE FAIRE N'EXISTE PAS OU ALORS IL FAUT TOUTES LES AFFICHER ?
}