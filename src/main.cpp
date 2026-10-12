#include "dominion.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <map>
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
       
    // CREATION COMPOSITIONS
    std::vector<Composition> compositions;

    compositions.push_back(Composition("Les premières parties", "", {
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
    compositions.push_back(Composition("Richesses et trésor", "", { 
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
    compositions.push_back(Composition("Interaction", "", { 
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
    compositions.push_back(Composition("Changement de taille", "", { 
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
    compositions.push_back(Composition("Place du village", "", { 
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

    std::vector<Joueur*> joueurs;

    for (int i=0; i<nbJoueur ; i++) {
        std::string pseudo;

        std::cout << "Entrez votre pseudo : ";
        std::cin >> pseudo;
        //confirmer ? o/n de UI
        //CORRIGER CA CAR JOUEURS EST UN VECTOR DE POINTEURS DONC IL FAUT CREER DE FACON DURABLE LES ADRESSES DES JOUEURS
        //joueurs.push_back(Joueur(pseudo));
    }

    // CHOIX COMPOSITION avant de creer le plateau vu que la compo est passée en paramètre
    
    Plateau P = Plateau(joueurs,0);
    // 7 cuivres et 3 domaines par joueur au début


    return 0;
}