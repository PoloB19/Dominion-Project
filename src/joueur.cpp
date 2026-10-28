#include "joueur.hpp"

#include "plateau.hpp"
#include "carte.hpp"

#include "UI_terminal.hpp"

Joueur::Joueur(std::string pseudo) : m_pseudo (pseudo){

    m_pioche = std::stack<const Carte*>(); 
    m_main = std::vector<const Carte*>(); 
    m_defausse = std::stack<const Carte*>();

    m_nbAction = 1;
    m_nbAchat = 1;
    m_pieces = 0;
    
    m_nbToursJoues = 0;
}

Joueur::~Joueur() {}

// Accès sécurisé

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


// Pioche
void Joueur::piocher(unsigned short nbPioche){

    for(size_t i = 0; i < nbPioche; i++){

        if (!accesPioche()){
            return;
        }        
        m_main.push_back(m_pioche.top());
        UI::annonceCarteDepuis(m_pioche.top()->getNom(),Emplacement::PIOCHE);
        m_pioche.pop();
    }
}

void Joueur::ajouterAPioche(const Carte* carte){
    if(carte != nullptr){
        m_pioche.push(carte);
        UI::annonceCarteVers(carte,Emplacement::PIOCHE); //on garde??? à voir en testant si ça sert
    }
}


// Défausse
void Joueur::ajouterADefausse(const Carte* carte){
    if(carte != nullptr){
        m_defausse.push(carte);
    }
}


// En jeu

void Joueur::ajouterAEnJeu(const Carte* carte){
    if(carte != nullptr){
        m_enJeu.push_back(carte);
        UI::annonceCarteVers(carte,Emplacement::EN_JEU);
    }
}

bool Joueur::enleverDepuisMain(const std::string& nomCarte, Emplacement vers){

    const Carte* carteEnlevee = nullptr;

    for (size_t i = 0; i < m_main.size(); i++) {
            
        if (m_main.at(i)->getNom() == nomCarte) {
            
            carteEnlevee = m_main.at(i);
            m_main.erase(m_main.begin() + i);
                    
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
            return true;
        }
    }
    return false; 
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
    
    if (m_nbAchat >= 1) {

        if (m_pieces >= carteAchetee->getPrix()){

            obtenirCartePlateau(carteAchetee, P, Emplacement::DEFAUSSE);
            ajustNbPiece(-carteAchetee->getPrix());
            ajustNbAchat(-1);

        } else {
            UI::annonceErreur("vous n'avez pas assez de pièces pour acheter cette carte");
            UI::retourALigne();
            UI::animationChargement(2);
        }
    } else {
        UI::annonceErreur("vous avez épuisé votre quantité d'achat pour ce tour");
        UI::retourALigne();
        UI::animationChargement(2);
    }
}

void Joueur::ecarter(std::string nomCarteEcartee, Plateau& P, Emplacement depuis, bool actionJoueur) {
    if (actionJoueur && m_nbAction < 1) {
        UI::annonceErreur("vous n'avez plus d'action disponible");
        UI::retourALigne();
        UI::animationChargement(2);
        return;
    }

    if (depuis == Emplacement::MAIN) {

        for (const Carte* c : m_main) {
            if (c->getNom()==nomCarteEcartee) {
                m_main.erase(std::find(m_main.begin(), m_main.end(), c));
                P.ajoutRebut(c);

                UI::afficherInformation("Vous rebutez " + c->getNom());
                UI::sautDeLigne();

                if(actionJoueur) {m_nbAction--;}
                return;
            }
        }
    }
    else if (depuis == Emplacement::EN_JEU) {
        for (const Carte* c : m_enJeu) {
            if (c->getNom()==nomCarteEcartee) {
                m_enJeu.erase(std::find(m_enJeu.begin(), m_enJeu.end(), c));
                P.ajoutRebut(c);

                UI::afficherInformation("Vous rebutez " + c->getNom());
                UI::sautDeLigne();

                if(actionJoueur) {m_nbAction--;}
                return;
            }
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
        m_pioche.push(tas_temporaire.at(0)); 
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

void Joueur::utiliserCarte(Plateau& P, const Carte* carte) {
    if (accesMain()) {

        if (enleverDepuisMain(carte->getNom(),Emplacement::EN_JEU)) {

            if (carte->getType()=="Action"){
                if (m_nbAction < 1) {
                    UI::annonceErreur("vous n'avez plus d'action disponible");
                    UI::retourALigne();
                    UI::animationChargement(2);
                    return;
                }
                m_nbAction--;
            }
            carte->utiliser(*this, P);
        }
        else UI::annonceErreur("bug dans enleverDepuisMain");
    }
    else {
        UI::annonceErreur("votre main est vide");
        UI::retourALigne();
        UI::animationChargement(2);
    }
}

bool Joueur::reagirAttaque(const Carte* carteAttaque, Plateau& P) {
    for (const Carte* c : m_main) {
        if (c->getSousType() == "ActionReaction" && c->reagir(*this, carteAttaque, P)) {
            return true;
        }
    }
    return false;
}

// --- Rafraîchir attributs ---

void Joueur::compterPiecesEnMain(Plateau& P) {

    std::vector<const Carte*> copieMain = m_main;

    for (const Carte* carteEnMain : copieMain) {
        if (carteEnMain->getType() == "Tresor") {
            utiliserCarte(P,carteEnMain);
        }
    }
}

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