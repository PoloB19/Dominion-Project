#include "dominion.hpp" 

#include <iostream>
#include <string>
#include <sstream>
#include <limits>


// Fonction qui vérifie et convertit la saisie en unsigned short
bool essayerConvertirNbJoueurs(const std::string& saisie, unsigned short& resultat) {
    if (saisie.empty()) return false;

    // Vérifier qu'il n'y a que des chiffres (pas de signe négatif '-' ou d'espaces)
    for (char c : saisie) {
        if (!std::isdigit(c)) return false;
    }

    try {
        // Convertir en valeur numérique plus large pour détecter le dépassement de capacité
        unsigned long valeur = std::stoul(saisie);
        
        // Vérifier si la valeur entre dans les limites d'un unsigned short
        if (valeur > std::numeric_limits<unsigned short>::max()) {
            return false;
        }
        
        resultat = static_cast<unsigned short>(valeur);
        return true;
    } 
    catch (...) {
        // Gère les erreurs si le nombre est trop grand pour un unsigned long
        return false;
    }
}


int main(){

    // CREATION CARTES DU JEU
    //Tresor
    Carte argent = Argent();
    Carte cuivre = Cuivre();
    Carte or_ = Or();

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

    // CREATION JOUEURS
    std::string saisie;
    unsigned short nbJoueur = 0;

    bool saisieValide = false;
    while (!saisieValide) {
        std::cout << "Entrez le nombre de joueurs : ";
        std::cin >> saisie;

        if (essayerConvertirNbJoueurs(saisie, nbJoueur)) {
            saisieValide = true;
        } else {
            std::cout << "Erreur : Saisie invalide (entrez un nombre entier positif valide).\n\n";
        }
    }

    std::vector<Joueur> joueurs;

    for (int i=0; i<nbJoueur ; i++) {
        std::string pseudo;

        std::cout << "Entrez votre pseudo : ";
        std::cin >> pseudo;
        //confirmer ? o/n de UI
        joueurs.push_back(Joueur(pseudo));
    }


    // CREATION COMPOSITION
    




    return 0;
}