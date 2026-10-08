#include "joueur.hpp"
#include "carte.hpp"
#include "plateau.hpp"

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

void Joueur::acheter(const Carte* carteAchetee, Plateau& P){
    m_main.push_back(carteAchetee);
    P.retirerCartePlateau(carteAchetee);
};

void Joueur::defausser(const Carte* carteDefausse){
    m_main.erase(std::find(m_main.begin(), m_main.end(), carteDefausse));
    m_defausse.push(carteDefausse);
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

//A FINIR
short Joueur::compterPoints(){

    //On vide la main dans la défausse
    while(!m_main.empty()){
        defausser(m_main.at(0));
    }

    //On reconstruit son deck dans la pioche avec sa défausse
    melangerDefausse();

    short score = 0;

    //On va vider la pioche dans la défausse petit à petit et compter

    /*
    
    while(!m_pioche.empty()){

        switch (m_pioche.top().getCardType())
        {
        case "Domaine":
            score+=1;
            break;
        case "Duché":
            score+=3;
            break;

        case "Province":
            score

        default:
            break;
        }


    }
    
    */


};