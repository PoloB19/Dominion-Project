#include "joueur.hpp"

#include "plateau.hpp"
#include "carte.hpp"

#include "ui_interaction.hpp"

unsigned short m_nextId = 0;

Joueur::Joueur(std::string pseudo) : m_idJoueur(m_nextId++), m_pseudo (pseudo){

    m_pioche = std::stack<const Carte*>(); 
    m_main = std::vector<const Carte*>(); 
    m_defausse = std::stack<const Carte*>();

    m_nbAction = 1;
    m_nbAchat = 1;
    m_pieces = 0;
    
    m_nbToursJoues = 0;
};

void Joueur::piocher(unsigned short nbPioche){

    for(size_t i = 0; i < nbPioche; i++){

        //On refait une pioche si elle est vide
        if(m_pioche.empty()){ 
            melangerDefausse();
        }

        //On pioche seulement si la pioche n'est pas vide
        if (!m_pioche.empty()){
            m_main.push_back(m_pioche.top());
            m_pioche.pop();
        } else {
            std::cout << "Aucune carte à piocher." << std::endl;
            break;
        }
    }

}

void Joueur::defausser(const Carte* carteDefausse){
    m_main.erase(std::find(m_main.begin(), m_main.end(), carteDefausse));
    m_defausse.push(carteDefausse);
};

void Joueur::obtenirCarte(const Carte* carte, Plateau& P, Destination dest){
    
    if (carte == nullptr || P.pileEstVide(carte)){
        return;
    }

    switch (dest)
    {
    case Destination::MAIN :
        m_main.push_back(carte);
        break;
    
    case Destination::DEFAUSSE :
        m_defausse.push(carte);
        break;  
        
    case Destination::PIOCHE :
        m_pioche.push(carte);    
    default:
        break;
    }

    P.retirerCartePlateau(carte);

}

void Joueur::acheter(const Carte* carteAchetee, Plateau& P){
    
    if (m_pieces >= carteAchetee->getPrix()){
        obtenirCarte(carteAchetee, P, Destination::DEFAUSSE);
        ajustNbPiece(-carteAchetee->getPrix());
    } else {
        std::cout << "Vous n'avez pas assez de pièces pour acheter cette carte ! " << std::endl;
    }


};

void Joueur::ecarter(Carte* carteRebutee, Plateau& P) {
    m_main.erase(std::find(m_main.begin(), m_main.end(), carteRebutee));
    P.ajoutRebut(carteRebutee);
}

void Joueur::melangerDefausse(){

    std::vector<const Carte*> tas_temporaire = {};

    //On transforme la défausse en tableau temporaire
    while(!m_defausse.empty()){
        tas_temporaire.push_back(m_defausse.top());
        m_defausse.pop();
    }

    //Randomiser
    std::random_device seed; 
    std::mt19937 random_number(seed());
    std::shuffle(tas_temporaire.begin(), tas_temporaire.end(), random_number);

    //On remplit la pioche
    while(!tas_temporaire.empty()){
        m_pioche.push(tas_temporaire.at(0)); //
        tas_temporaire.erase(tas_temporaire.begin());
    }

}

void Joueur::resetTour() {
    m_nbAchat = 1;
    m_nbAction = 1;
};

short Joueur::compterPoints() const {

    short score = 0;

    // On construit le deck total du joueur en regroupant ses cartes
    std::vector<const Carte*> deck = m_main;
    deck.reserve(m_pioche.size() + m_defausse.size() + m_main.size());

    std::stack<const Carte*> piocheTmp = m_pioche;
    while (!piocheTmp.empty()) {
        deck.push_back(piocheTmp.top());
        piocheTmp.pop();
    }

    std::stack<const Carte*> defausseTmp = m_defausse;
    while (!defausseTmp.empty()) {
        deck.push_back(defausseTmp.top());
        defausseTmp.pop();
    }
    
    //On calcul son score
    for (const Carte* c : deck){
        score += c->getPointsVictoire(*this);
    }

    return score;
};

bool Joueur::demanderOuiNon(const std::string& question) const {
    return UI::choixOuiNon(m_pseudo + ", " + question);
}

