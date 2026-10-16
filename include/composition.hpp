#pragma once

#include <map>
#include <string>

#include "carte.hpp"

class Composition {
    
    std::string m_nomDeComposition;
    std::string m_description;
    std::map<const Carte*, unsigned short> m_compositionPartie;

public:
    Composition(std::string nomDeComposition, std::map<const Carte*, unsigned short> compositionPartie);
    ~Composition();

    //Getters
    std::string getNom() const;
    std::map<const Carte*, unsigned short> getCompositionPartie() const;
};