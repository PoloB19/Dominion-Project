#include <vector>

#include "plateau.hpp"

//A COMPLETER LES COMPO
std::vector<const Composition*> Plateau::m_compositions = {};

Plateau::Plateau(std::vector<Joueur*> joueurs, size_t idCompositionPartie) : m_joueurs(joueurs), m_idCompositionPartie(idCompositionPartie), m_piles(Plateau::getCompositions().at(idCompositionPartie)->getCompositionPartie()), m_rebut(std::stack<const Carte*>()) {};

const Carte* Plateau::getCarteParNom(const std::string& nomCarte) const {
    for (const auto& c : m_piles) {
        if (c.first->getNom() == nomCarte) {
            return c.first;
        }
    }
    return nullptr;
}

void Plateau::ajoutRebut(const Carte* carteRebutee) {
    m_rebut.push(carteRebutee);
};

void Plateau::retirerCartePlateau(const Carte* carte){
    if (m_piles.at(carte) > 0) {
        m_piles.at(carte) -= 1;
    }
};

bool Plateau::checkerEndCondition(){ 

    unsigned short compteur_tmp = 0 ;

    for (const auto& pair : m_piles){

        //On compte le nombre de piles vides
        if (pair.second == 0){
            compteur_tmp++;

            //On regarde aussi si la pile des Province est vide
            if(pair.first->getNom() == "Province"){
                return true;
            }
        }
    }

    return compteur_tmp >= 3;
};

std::vector<Joueur> Plateau::determinerGagnant(){

    std::vector<Joueur> gagnantsTmp = {*m_joueurs.at(0)};

    for (auto J = m_joueurs.begin() + 1; J != m_joueurs.end(); ++J){

        //Si le joueur a un meilleur score que les gagnants actuels

        if((*J)->compterPoints() > gagnantsTmp.at(0).compterPoints()){
            gagnantsTmp.at(0) = **J;

        //Si le joueur a un score égal aux gagnants actuels
        } else if ((*J)->compterPoints() == gagnantsTmp.at(0).compterPoints()){

            //Si le joueur a - de tour joués que les gagnants actuels
            if ((*J)->getNbTourJoues() > gagnantsTmp.at(0).getNbTourJoues()){
                gagnantsTmp.clear(); 
                gagnantsTmp.at(0) = **J;

            //Si le joueur et les gagnants actuels ont le même score et le même nombre de tour joués
            } else if ((*J)->getNbTourJoues() == gagnantsTmp.at(0).getNbTourJoues()){
                gagnantsTmp.push_back(**J);
            }

        }
    }

    return gagnantsTmp;

}; 