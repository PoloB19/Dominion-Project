#include "joueur.hpp"

#include "plateau.hpp"
#include "carte.hpp"

#include "UI_terminal.hpp"

unsigned short Joueur::m_nextId = 0;

Joueur::Joueur(std::string pseudo) : m_idJoueur(m_nextId++), m_pseudo (pseudo){

    m_pioche = std::stack<const Carte*>(); 
    m_main = std::vector<const Carte*>(); 
    m_defausse = std::stack<const Carte*>();

    m_nbAction = 1;
    m_nbAchat = 1;
    m_pieces = 0;
    
    m_nbToursJoues = 0;
};

Joueur::~Joueur() {}

// --- Accès sécurisé ---

bool Joueur::accesMain() const {
    return m_main.size() > 0;
}

bool Joueur::accesPioche() {
    if(m_pioche.empty()) melangerDefausse();
    if(m_pioche.empty()) {
        std::cout << "La pioche et la défausse sont vide." << std::endl;
        return false;
    }
    return true;
}

bool Joueur::accesDefausse() const {
    if(m_defausse.empty()) {
        std::cout << "La défausse est vide." << std::endl;
        return false;
    }
    return true; 
}


//Pioche
//APPELER ANNONCE DEPUIS PIOCHE
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

//APPELER ANNONCE VERS PIOCHE
void Joueur::ajouterAPioche(const Carte* carte){
    if(carte != nullptr){
        m_pioche.push(carte);
    }
}


// Défausse
//APPELER ANNONCE VERS DEFAUSSE
void Joueur::ajouterADefausse(const Carte* carte){
    if(carte != nullptr){
        m_defausse.push(carte);
    }
}


// En jeu

void Joueur::ajouterAEnJeu(const Carte* carte){
    if(carte != nullptr){
        m_enJeu.push_back(carte);
    }
}


void Joueur::enleverDepuisMain(const std::string& nomCarte, Emplacement vers){

    const Carte* carteEnlevee = nullptr;

    for (size_t i = 0; i < m_main.size(); i++) {
            
            if (m_main.at(i)->getNom() == nomCarte) {
                
                carteEnlevee = m_main.at(i);
                m_main.erase(m_main.begin() + i);
                      
                break; //Pour n'enlever qu'une seule carte
            }
        }

    switch (vers)
    {
    case Emplacement::DEFAUSSE :
        ajouterADefausse(carteEnlevee);
        break;
    
    case Emplacement::PIOCHE : 
        ajouterAPioche(carteEnlevee);
        break;

    case Emplacement::EN_JEU :
        ajouterAEnJeu(carteEnlevee);
        break;

    default:
        break;
    }
    
}

// --- Méthodes ---

void Joueur::obtenirCartePlateau(const Carte* carte, Plateau& P, Emplacement destination){
    
    if (carte == nullptr || P.pileEstVide(carte)) return;

    P.retirerCartePlateau(carte);

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

}

void Joueur::acheter(const Carte* carteAchetee, Plateau& P){
    
    if (m_pieces >= carteAchetee->getPrix()){

        obtenirCartePlateau(carteAchetee, P, Emplacement::DEFAUSSE);
        ajustNbPiece(-carteAchetee->getPrix());

    } else {

        std::cout << "Vous n'avez pas assez de pièces pour acheter cette carte ! " << std::endl;

    }

};

//APPELER ANNONCE VERS REBUT
void Joueur::ecarter(std::string nomCarteEcartee, Plateau& P) {
    for (const Carte* c : m_main) {
        if (c->getNom()==nomCarteEcartee) {
            m_main.erase(std::find(m_main.begin(), m_main.end(), c));
            P.ajoutRebut(c);
            return;
        }
    }
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

//APPELER ANNONCE REVELER CARTE !
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


void Joueur::utiliserCarte(Plateau& P, const Carte* carte) {
    enleverDepuisMain(carte->getNom(),Emplacement::EN_JEU);
    carte->utiliser(*this, P);
}

// --- Rafraîchir attributs ---

short Joueur::compterPoints() const {

    short score = 0;

    // On construit le deck total du joueur en regroupant ses cartes
    std::vector<const Carte*> deck = m_main;
    deck.reserve(this->getTailleDeck());

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
    
    //On calcule son score
    for (const Carte* c : deck){
        score += c->getPointsVictoire(*this);
    }

    return score;
}


void Joueur::finDeTour() {

    //Vide les cartes en Main et en Jeu dans la défausse
    for(const Carte* c : m_main){
        ajouterADefausse(c);
    }
    m_main.clear();
    for(const Carte* c : m_enJeu){
        ajouterADefausse(c);
    }
    m_enJeu.clear();

    //Pioche et mise à jour des attributs
    piocher(5);

    m_nbAchat = 1;
    m_nbAction = 1;
    m_pieces = 0;
    m_nbToursJoues++;
}

// --- Interactions ---

// Choix

bool Joueur::demanderOuiNon(const std::string& question) const {
    return UI::choixOuiNon(m_pseudo + ", " + question);
}

std::vector<size_t> Joueur::choixParmiCartes(std::vector<const Carte*> cartes, unsigned short nbChoix) {
    if (cartes.empty()) { return {}; }
    return UI::choixParmiCartes(*this, cartes, nbChoix);
}

// Annonces

void Joueur::annonceCarteDepuis(std::string nomCarte, Emplacement depuis) const {
    UI::annonceCarteDepuis(nomCarte, depuis);
}

void Joueur::annonceCarteVers(std::string nomCarte, Emplacement vers) const {
    UI::annonceCarteVers(nomCarte, vers);
}

void Joueur::annonceRevelerCartes(std::vector<const Carte*> cartes) const {
    UI::annonceRevelerCartes(*this, cartes);
}

void Joueur::annonceErreur(std::string message) const {
    UI::annonceErreur(message);
}