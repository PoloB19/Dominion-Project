#include "composition.hpp"

// constructeur
Composition::Composition(std::string nomDeComposition, std::map<const Carte*, unsigned short> compositionPartie) : m_nomDeComposition(nomDeComposition), m_compositionPartie(compositionPartie) {}

Composition::~Composition() {}

// Getters

std::string Composition::getNom() const {
    return m_nomDeComposition;
}

std::map<const Carte*, unsigned short> Composition::getCompositionPartie() const {
    return m_compositionPartie;
}
