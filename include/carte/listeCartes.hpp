#pragma once

#include <vector>

#include "carte.hpp"

namespace Cartes {

    template <typename T>
    const Carte* getCarte(){
        static const T instanceCarte;
        return &instanceCarte;
    }

    const std::vector<const Carte*>& catalogue();
    
    const std::vector<const Carte*>& royaume();
}