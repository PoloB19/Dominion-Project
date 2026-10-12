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
        ////je vais faire pareil que pour cartes
    // CREATION COMPOSITIONS
    std::vector<const Composition*> compositions;

    std::map<const Carte*, unsigned short> compoPartie;

    // Compo "Les premières parties"
    compoPartie.insert({Cartes::atelier(),10});
    compoPartie.insert({Cartes::bucheron(),10});
    compoPartie.insert({Cartes::cave(),10});
    compoPartie.insert({Cartes::douves(),10});
    compoPartie.insert({Cartes::forgeron(),10});
    compoPartie.insert({Cartes::marche(),10});
    compoPartie.insert({Cartes::milice(),10});
    compoPartie.insert({Cartes::mine(),10});
    compoPartie.insert({Cartes::renovation(),10});
    compoPartie.insert({Cartes::village(),10});    

    compositions.push_back(&Composition("Les premières parties","",compoPartie));

    // Compo "Richesses et trésor"
    compoPartie.clear();

    compoPartie.insert({Cartes::aventurier(),10});
    compoPartie.insert({Cartes::bureaucrate(),10});
    compoPartie.insert({Cartes::chancelier(),10});
    compoPartie.insert({Cartes::chapelle(),10});
    compoPartie.insert({Cartes::festin(),10});
    compoPartie.insert({Cartes::laboratoire(),10});
    compoPartie.insert({Cartes::marche(),10});
    compoPartie.insert({Cartes::mine(),10});
    compoPartie.insert({Cartes::preteurSurGages(),10});
    compoPartie.insert({Cartes::salleDuTrone(),10});   

compositions.push_back(&Composition("Richesses et trésor","",compoPartie));   





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
    

    // 7 cuivres et 3 domaines par joueur au début


    return 0;
}