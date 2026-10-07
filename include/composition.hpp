#pragma once

#include <vector>
#include <string>

#include "carte.hpp"

class Composition {
    
    std::string m_nomDeComposition;
    std::string m_description;
    std::map<const Carte*, unsigned short> m_compositionPartie;

public:
    Composition(std::vector<Carte> compositionPartie);
    ~Composition();
    
};