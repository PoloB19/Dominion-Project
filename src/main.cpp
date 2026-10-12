#include "dominion.hpp" 

#include <iostream>

int main(){

    // CREATION CARTES DU JEU
    //Tresor
    Carte argent = Argent();
    Carte cuivre = Cuivre();
    Carte or = Or();

    //Malédiction
    Carte mal = Malediction();

    //Victoire
    Carte domaine = Domaine();
    Carte duche = Duche();
    Carte jardins = Jardins();
    Carte province = Province();

    //Action
    Carte c1 = Atelier();
    Carte c2 = Aventurier();
    Carte c3 = Bibliotheque();
    Carte c4 = Bucheron();
    Carte c5 = Cave();
    Carte c6 = Festival();
    Carte c7 = Forgeron();
    Carte c8 = Laboratoire();
    //à finir

    // CREATION COMPOSITION
    std::cout << "Combien de joueurs êtes-vous ?" << std::endl;
    unsigned short nbJoueur;
    //creer fonction pour vérifier que le nb est valide 
    //std::cin >> unsigned short(nbJoueur);



    return 0;
}