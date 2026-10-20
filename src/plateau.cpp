#include <vector>

#include "listeCartes.hpp"
#include "plateau.hpp"

#include "UI_terminal.hpp"

std::vector<Composition> Plateau::m_compositions = {};

Plateau::Plateau(std::vector<std::string> joueurs, size_t idCompositionPartie) : m_idCompositionPartie(idCompositionPartie), m_piles(Plateau::getCompositions().at(idCompositionPartie).getCompositionPartie()), m_rebut(std::stack<const Carte*>()) {
    // CREATION JOUEURS
    for (const std::string& pseudo : joueurs) {
        m_joueurs.emplace_back(pseudo); // construit le joueur directement dans le vecteur
        Joueur& j = m_joueurs.back();
        for (int i = 0; i < 7; i++) j.ajouterADefausse(Cartes::cuivre());
        for (int i = 0; i < 3; i++) j.ajouterADefausse(Cartes::domaine());
    }
    
    // CARTES COMMUNES A TOUTES LES COMPOSITIONS :
    m_piles.insert({Cartes::cuivre(),60-m_joueurs.size()*7});
    m_piles.insert({Cartes::argent(),40});
    m_piles.insert({Cartes::or_(),30});
    switch(m_joueurs.size()) {
        // nb provinces et malédiction en fonction du nb de joueurs
        case 2 :
            m_piles.insert({Cartes::domaine(),8});
            m_piles.insert({Cartes::duche(),8});
            m_piles.insert({Cartes::province(),8});
            m_piles.insert({Cartes::malediction(),10});
            break;
        case 3 :
            m_piles.insert({Cartes::malediction(),20});
            // fall through
        case 4 :
            m_piles.insert({Cartes::domaine(),12});
            m_piles.insert({Cartes::duche(),12});
            m_piles.insert({Cartes::province(),12});
            m_piles.insert({Cartes::malediction(),30});
            break;
        default :
            std::cerr << "Erreur dans le nombre de joueur passé dans le vecteur du constructeur plateau" << std::endl;
            break;
    }    
}

Plateau::~Plateau() {}

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
}

void Plateau::retirerCartePlateau(const Carte* carte){
    if (m_piles.at(carte) > 0) {
        m_piles.at(carte) -= 1;
    } else {
        UI::annonceErreur("cette pile est vide");
    }
}

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
}

std::vector<Joueur*> Plateau::determinerGagnant(){

    //On suppose le premier joueur gagnant
    std::vector<Joueur*> gagnantsTmp = {&m_joueurs.at(0)};
    short meilleurScore = m_joueurs.at(0).compterPoints();

    for (size_t i = 1; i < m_joueurs.size(); i++) {

        Joueur& j = m_joueurs.at(i);
        short score = j.compterPoints();

        //Si le joueur a un meilleur score que les gagnants actuels
        if(score > meilleurScore){
            gagnantsTmp = {&j};
            meilleurScore = score;

        //Si le joueur a un score égal aux gagnants actuels
        } else if (score == meilleurScore){

            //Si le joueur a - de tour joués que les gagnants actuels
            if (j.getNbTourJoues() < gagnantsTmp.at(0)->getNbTourJoues()){

                gagnantsTmp = {&j};

            //Si le joueur et les gagnants actuels ont le même score et le même nombre de tours joués
            } else if (j.getNbTourJoues() == gagnantsTmp.at(0)->getNbTourJoues()){
                gagnantsTmp.push_back(&j);
            }

        }
    }
    
    return gagnantsTmp;
}

void Plateau::setModeRapide() {
    for (auto& [carte, quantite] : m_piles) {
        quantite = 1;
    }
}