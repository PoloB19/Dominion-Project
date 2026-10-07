#include "joueur.hpp"
#include "carte.hpp"

Joueur::Joueur(std::string pseudo) {
    m_pseudo = pseudo ; 
    m_pioche = std::stack<const Carte*>(); 
    m_main = std::vector<const Carte*>(); 
    m_defausse = std::stack<const Carte*>();
    m_nbAction = 1;
    m_nbAchat = 1;
    m_monnaie = 0;
};

void Joueur::piocher(){

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
    }

}

void acheter(const Carte* carte);
void defausser(const Carte* carte);
void ecarter(const Carte* carte);

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
        m_pioche.push(tas_temporaire[0]); //
        tas_temporaire.erase(tas_temporaire.begin());
    }

}
void resetTour();

short compterPoints();