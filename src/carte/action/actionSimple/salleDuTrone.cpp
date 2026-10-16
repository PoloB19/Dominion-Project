#include "salleDuTrone.hpp"

#include "UI_terminal.hpp"

SalleDuTrone::SalleDuTrone() : ActionSimple("Salle du trône", 4, "Choisissez une carte Action de votre main. \nJouez-la deux fois.") {}

SalleDuTrone::~SalleDuTrone() {}

void SalleDuTrone::utiliser(Joueur& J, Plateau& P) const {

    while(true){

        std::vector<const Carte*> mainAction;

        for (const Carte* c : J.getMain()){
            if (c->getType() == "Action"){
                mainAction.push_back(c);
            }
        }

        if(mainAction.size() <= 1){
            UI::annonceErreur("vous n'avez pas de cartes Action dans votre main.");
            return;
        }

        const size_t idCarteChoisie = J.choixParmiCartes(mainAction, 1).at(0);

        mainAction.at(idCarteChoisie)->utiliser(J, P);
        mainAction.at(idCarteChoisie)->utiliser(J, P);

        J.enleverDepuisMain(mainAction.at(idCarteChoisie)->getNom(),Emplacement::DEFAUSSE);
    }
}