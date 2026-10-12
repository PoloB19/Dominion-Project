#include "bibliotheque.hpp"

Bibliotheque::Bibliotheque() : ActionSimple("Bibliothèque", 5, "Piochez jusqu'à avoir 7 cartes dans votre main, en défaussant si vous le souhaitez la carte pioché si c'est une Action ."){};

void Bibliotheque::utiliser(Joueur& J, Plateau&){

    while(J.getMain().size() < 7){

        const Carte* prochainePioche = J.revelerCarte(Emplacement::PIOCHE);
        
        try{

            if(prochainePioche->getType() == "Action" && J.demanderOuiNon(prochainePioche->getNom() + " est la carte action piochée, souhaitez vous la défausser?")){

                J.ajouterADefausse(prochainePioche);

            }

        } catch (const std::exception& e){

            std::cout << e.what() << std::endl;
            
        }
    }
}