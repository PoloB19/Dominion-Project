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

std::vector<Joueur> Plateau::determinerGagnant(){

    std::vector<Joueur> gagnantsTmp ={m_joueurs.at(0)};

    for (auto J = m_joueurs.begin() + 1; J != m_joueurs.end(); ++J){

        //Si le joueur a un meilleur score que les gagnants actuels

        if(J->compterPoints() > gagnantsTmp.at(0).compterPoints()){
            gagnantsTmp.at(0) = *J;

        //Si le joueur a un score égal aux gagnants actuels
        } else if (J->compterPoints() == gagnantsTmp.at(0).compterPoints()){

            //Si le joueur a - de tour joués que les gagnants actuels
            if (J->getNbTourJoues() > gagnantsTmp.at(0).getNbTourJoues()){
                gagnantsTmp.clear(); 
                gagnantsTmp.at(0) = *J;

            //Si le joueur et les gagnants actuels ont le même score et le même nombre de tour joués
            } else if (J->getNbTourJoues() == gagnantsTmp.at(0).getNbTourJoues()){
                gagnantsTmp.push_back(*J);
            }

        }
    }

    return gagnantsTmp;

}; 