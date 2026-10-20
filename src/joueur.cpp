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

    // ICI QUE DOIVENT ETRE MISES DANS LA DEFAUSSE LES CARTES DE DEMARRAGE DE CHAQUE JOUEUR : 7cuivres et 3 domaines
}

Joueur::~Joueur() {}

// --- Accès sécurisé ---

bool Joueur::accesMain() const {
    return m_main.size() > 0;
}

bool Joueur::accesPioche() {
    if(m_pioche.empty()) melangerDefausse();
    if(m_pioche.empty()) {
        UI::afficherInformation("La pioche et la défausse sont vide.");
        UI::retourALigne();
        return false;
    }
    return true;
}

bool Joueur::accesDefausse() const {
    if(m_defausse.empty()) {
        UI::afficherInformation("La défausse est vide.");
        UI::retourALigne();
        return false;
    }
    return true; 
}


//Pioche
void Joueur::piocher(unsigned short nbPioche){

    for(size_t i = 0; i < nbPioche; i++){

        if (!accesPioche()){
            return;
        }

        UI::annonceCarteDepuis(m_pioche.top()->getNom(),Emplacement::PIOCHE);
        
        m_main.push_back(m_pioche.top());
        m_pioche.pop();
        
    }
}

//APPELER ANNONCE VERS PIOCHE
void Joueur::ajouterAPioche(const Carte* carte){
    if(carte != nullptr){
        m_pioche.push(carte);
        UI::annonceCarteVers(carte->getNom(),Emplacement::PIOCHE);
    }
}


// Défausse
void Joueur::ajouterADefausse(const Carte* carte){
    if(carte != nullptr){
        m_defausse.push(carte);
        UI::annonceCarteVers(carte->getNom(),Emplacement::DEFAUSSE);
    }
}


// En jeu

void Joueur::ajouterAEnJeu(const Carte* carte){
    if(carte != nullptr){
        m_enJeu.push_back(carte);
        UI::annonceCarteVers(carte->getNom(),Emplacement::EN_JEU);
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
        UI::annonceErreur("vous n'avez pas assez de pièces pour acheter cette carte");
        UI::retourALigne();
    }

};

void Joueur::ecarter(std::string nomCarteEcartee, Plateau& P) {
    for (const Carte* c : m_main) {
        if (c->getNom()==nomCarteEcartee) {
            m_main.erase(std::find(m_main.begin(), m_main.end(), c));
            P.ajoutRebut(c);

            UI::afficherInformation("Vous rebutez " + c->getNom());
            UI::sautDeLigne();

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

void utiliserCarte() {
    UI::afficherInformation("Quelle carte souhaitez-vous utiliser ?");
    std::vector<size_t> idChoix = UI::choixParmiCartes(*this,m_main,1);
    // à finir
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