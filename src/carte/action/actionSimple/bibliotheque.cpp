#include "bibliotheque.hpp"

Bibliotheque::Bibliotheque() : ActionSimple("Bibliothèque", 5, "Piochez jusqu'à avoir 7 cartes dans votre main, en défaussant si vous le souhaitez la carte pioché si c'est une Action ."){}

Bibliotheque::~Bibliotheque() {}

void Bibliotheque::utiliser(Joueur& J, Plateau&){

    while(J.getMain().size() < 7){

        J.piocher(1);

        const Carte* cartePiochee = J.getMain().back();
        
        if(cartePiochee->getType() == "Action" && J.demanderOuiNon(cartePiochee->getNom() + " est la carte action piochée, souhaitez vous la défausser?")){

            J.enleverDepuisMain(cartePiochee->getNom(), Emplacement::DEFAUSSE);

        }
    }
}