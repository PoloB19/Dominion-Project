#include "cave.hpp"

Cave::Cave() : ActionSimple("Cave", 2, "+1 Action \nDéfaussez autant de carte que vous le souhaitez. +1 Carte par carte défaussée.") {}

void Cave::utiliser(Joueur& J,  Plateau& P){

    J.ajustNbAction(+1);

    std::cout << "Vous pourrez piocher autant de carte que vous défaussez." << std::endl;

    std::string choix;

    while(choix != "STOP"){
        std::cout << "Quelle carte souhaitez vous défausser de votre main? Indiquez son nom." << std::endl;
        std::cout << "Choix :";

        std::cin >> choix;

        if (choix != "STOP"){
            for(size_t i; i < J.getMain().size(); i++){
                if(J.getMain().at(i)->getNom() == choix) {
                    std::cout << "La carte " << J.getMain().at(i)->getNom() << " a été défaussée." << std::endl;
                    J.defausser(J.getMain().at(i));
                    break;
                }
            }

        }

    }
        
}