#include "composition.hpp"

// constructeur
Composition::Composition(std::string nomDeComposition, std::string description, std::map<const Carte*, unsigned short> compositionPartie) : m_nomDeComposition(nomDeComposition), m_description(description), m_compositionPartie(compositionPartie) {}

// destructeur
Composition::~Composition() {}


// getters

std::string Composition::getNomDeComposition() const {
    return m_nomDeComposition;
}

std::string Composition::getDescription() const {
    return m_description;
}

std::map<const Carte*, unsigned short> Composition::getCompositionPartie() const {
    return m_compositionPartie;
}

