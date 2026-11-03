#include "voleur.hpp"
#include "UI_terminal.hpp"

#include "string"

Voleur::Voleur() : ActionAttaque("Voleur", 4, "Tous vos adversaires dévoilent les 2 premières cartes de leur deck.\nS'ils dévoilent des cartes Trésor, ils en écartent une de votre choix. Parmi ces cartes Trésor écartées, recevez celles de votre choix. Les autres cartes dévoilées sont défaussées.") {}
Voleur::~Voleur() {}

void Voleur::utiliser(Joueur& J, Plateau& P) const {

    // vecteur contenant les cartes écartées par le voleur
    std::vector<const Carte*> cartesEcartees;

    const Carte* carteRevelee;
    std::vector<const Carte*> tresorReveles;

    // on parcout les joueurs attaquables
    std::vector<Joueur*> ciblesAttaque = ActionAttaque::determinerCibles(J, P, this);
    for (Joueur* ptr_j : ciblesAttaque) {

        if (ptr_j == nullptr) continue; // Sécurité
        Joueur& j = *ptr_j; // On transforme le pointeur en référence

        tresorReveles = {}; 

        // On révèle les 2 cartes de la pioche d'un joueur
        for (int k = 0; k < 2; k++) {
            carteRevelee = j.revelerCarte(Emplacement::PIOCHE);
            if (carteRevelee == nullptr) break;
            UI::annonceRevelerCartes(j, {carteRevelee});
            if (carteRevelee->getType() == "Tresor") tresorReveles.push_back(carteRevelee);
            else j.ajouterADefausse(carteRevelee);
        }
    
        // Si seulement une des 2 cartes révélées était un trésor, on l'écarte.
        if (tresorReveles.size() == 1) {
            cartesEcartees.push_back(tresorReveles.at(0));
        }
        // Sinon on laisse au voleur le choix entre les 2
        else if (tresorReveles.size() == 2) {
            UI::afficherInformation("Quelle carte de " + j.getPseudo() + " écartez-vous ? ");
            size_t idxChoix = UI::choixParmiCartes(J,tresorReveles,1).at(0);
            cartesEcartees.push_back(tresorReveles.at(idxChoix));

            // la carte trésor non-selectionnée par le voleur est remise dans la défausse du joueur
            for (size_t i = 0; i<tresorReveles.size(); i++) {
                if (i!=idxChoix) {
                    j.ajouterADefausse(tresorReveles.at(i));
                }
            }
        }
    }
    
    if (cartesEcartees.size()==0) {
        UI::afficherInformation("Vous n'avez rien à voler.\n"); 
        UI::animationChargement(4);
    }
    else {
        // on affiche les cartes écartées
        UI::afficherInformation("Voici les cartes que vous allez écarter : "); 
        std::string texte = "|";
        for (auto carte : cartesEcartees) {
            texte += carte->getNom() + "|";
        }
        texte += " ";
        UI::afficherInformation(texte);

        // on demande au joueur s'il veut en voler une
        std::vector<size_t> idxChoix = {};
        if (UI::choixOuiNon("Souhaitez-vous en voler une ?")) {
            idxChoix = UI::choixParmiCartes(J,cartesEcartees,1);
        }
        
        // si une carte est volée :
        if (!idxChoix.empty()) {
            J.ajouterADefausse(cartesEcartees.at(idxChoix.at(0)));
            cartesEcartees.erase(cartesEcartees.begin() + idxChoix.at(0));
        }
        // on met dans le rebut les autres
        for (const Carte* c : cartesEcartees) {
            P.ajoutRebut(c);
        }
    }
}