#include "plateau.hpp"
#include "dominion.hpp"

std::vector<Composition> Plateau::m_compositions = {};

Plateau::Plateau(std::vector<std::string> joueurs, size_t idCompositionPartie) : m_idCompositionPartie(idCompositionPartie), m_piles(Plateau::getCompositions().at(idCompositionPartie).getCompositionPartie()), m_rebut(std::stack<const Carte*>()) {
    // CREATION JOUEURS
    for (const std::string& pseudo : joueurs) {
        m_joueurs.emplace_back(pseudo); // construit le joueur directement dans le vecteur
        Joueur& j = m_joueurs.back();
        for (int i = 0; i < 7; i++) j.ajouterADefausse(Cartes::getCarte<Cuivre>());
        for (int i = 0; i < 3; i++) j.ajouterADefausse(Cartes::getCarte<Domaine>());
        j.piocher(5);
    }
    
    // CARTES COMMUNES A TOUTES LES COMPOSITIONS
    m_piles.insert({Cartes::getCarte<Cuivre>(),60-m_joueurs.size()*7});
    m_piles.insert({Cartes::getCarte<Argent>(),40});
    m_piles.insert({Cartes::getCarte<Or>(),30});
    switch(m_joueurs.size()) {
        // nb provinces et malédiction en fonction du nb de joueurs
        case 2 :
            m_piles.insert({Cartes::getCarte<Domaine>(),8});
            m_piles.insert({Cartes::getCarte<Duche>(),8});
            m_piles.insert({Cartes::getCarte<Province>(),8});
            m_piles.insert({Cartes::getCarte<Malediction>(),10});
            break;
        case 3 :
            m_piles.insert({Cartes::getCarte<Malediction>(),20});
            // fall through
        case 4 :
            m_piles.insert({Cartes::getCarte<Domaine>(),12});
            m_piles.insert({Cartes::getCarte<Duche>(),12});
            m_piles.insert({Cartes::getCarte<Province>(),12});
            m_piles.insert({Cartes::getCarte<Malediction>(),30});
            break;
        default :
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

std::vector<Joueur*> Plateau::determinerClassement() {
    std::vector<Joueur*> classement;
    classement.reserve(m_joueurs.size());

    for (Joueur& j : m_joueurs) {
        classement.push_back(&j);
    }

    // On trie le vecteur avec une fonction lambda (règle de tri)
    std::sort(classement.begin(), classement.end(), [](Joueur* a, Joueur* b) {
        short scoreA = a->compterPoints();
        short scoreB = b->compterPoints();

        // Si les scores sont différents, le plus grand score passe devant
        if (scoreA != scoreB) {
            return scoreA > scoreB; 
        }
        //En cas d'égalité parfaite, celui qui a joué le moins de tours gagne
        return a->getNbTourJoues() < b->getNbTourJoues();
    });
    
    return classement;
}


void Plateau::setModeRapide() {
    for (auto& [carte, quantite] : m_piles) {
        quantite = 1;
    }
}