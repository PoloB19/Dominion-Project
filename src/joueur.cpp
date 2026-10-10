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

        if (!accesPioche()){
            return;
        }

        std::cout << "Vous avez pioché la carte : " << m_pioche.top()->getNom();
        
        m_main.push_back(m_pioche.top());
        m_pioche.pop();
        
    }
}

bool Joueur::accesPioche() {
    if(m_pioche.empty()) melangerDefausse();
    if(m_pioche.empty()) {
        std::cout << "La pioche et la défausse sont vide." << std::endl;
        return false;
    }
    return true;
}

void Joueur::ajouterAPioche(const Carte* carte){
    if(carte != nullptr){
        m_pioche.push(carte);
    }
}

bool Joueur::accesDefausse() const {
    if(m_defausse.empty()) {
        std::cout << "La défausse est vide." << std::endl;
        return false;
    }
    return true; 
}

void Joueur::ajouterADefausse(const Carte* carte){
    if(carte != nullptr){
        m_defausse.push(carte);
    }
}

void Joueur::defausserDepuisMain(const Carte* carteDefausse){
    auto it = std::find(m_main.begin(), m_main.end(), carteDefausse);
    
    //Sécurité
    if (it != m_main.end()) {
        m_main.erase(it);
        ajouterADefausse(carteDefausse); 
    }
};

void Joueur::obtenirCartePlateau(const Carte* carte, Plateau& P, Emplacement destination){
    
    if (carte == nullptr || P.pileEstVide(carte)){
        return;
    }

    switch (destination)
    {
    case Emplacement::MAIN :
        m_main.push_back(carte);
        break;
    
    case Emplacement::DEFAUSSE :
        m_defausse.push(carte);
        break;  
        
    case Emplacement::PIOCHE :
        m_pioche.push(carte);    
    default:
        break;
    }

    P.retirerCartePlateau(carte);

}

void Joueur::acheter(const Carte* carteAchetee, Plateau& P){
    
    if (m_pieces >= carteAchetee->getPrix()){

        obtenirCartePlateau(carteAchetee, P, Emplacement::DEFAUSSE);
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

const Carte* Joueur::revelerCarte(Emplacement depuis){

    const Carte* carteRevelee = nullptr;

    switch (depuis)
    {
    case Emplacement::PIOCHE :

        if(!accesPioche()) return nullptr;

        carteRevelee = m_pioche.top();
        m_pioche.pop();

        break;

    case Emplacement::DEFAUSSE :

        if(!accesDefausse()) return nullptr;

        carteRevelee = m_defausse.top();
        m_defausse.pop();

        break;

    default:
        return carteRevelee;
    }

    return carteRevelee;
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

