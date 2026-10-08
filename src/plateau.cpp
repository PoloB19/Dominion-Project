#include "plateau.hpp"

Plateau::Plateau(std::vector<Joueur> joueurs, Composition compositionPartie) : m_joueurs(joueurs), m_compositionPartie(compositionPartie), m_rebut(std::stack<const Carte*>()), m_piles(std::map<const Carte*, unsigned short>()) {}

//A RAJOUTER SUR UML
void Plateau::retirerCartePlateau(const Carte* carteAchetee){
    m_piles[carteAchetee] -= 1;
};

//Il faut que ce soit au action turn, au buy turn
//Gemini dit l'inverse et dit que c'est à la fin d'un tour
bool Plateau::checkerEndCondition(){ 

    unsigned short compteur_tmp = 0 ;

    for (const auto& pair : m_piles){

        //On compte le nombre de piles vides
        if (pair.second == 0){
            compteur_tmp++;

            //On regarde aussi si la pile des Province est vide
            if(pair.first->getCarteType() == "Province"){
                return true;
            }
        }
    }

    return compteur_tmp >= 3;
};

Joueur determinerGagnant(); 