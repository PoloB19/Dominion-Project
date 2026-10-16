#pragma once
#include "carte.hpp"

namespace Cartes {
    // Trésor
    const Carte* cuivre();
    const Carte* argent();
    const Carte* or_();
    // Malédiction
    const Carte* malediction();
    // Victoire
    const Carte* domaine();
    const Carte* duche();
    const Carte* province();
    // Royaume
    const Carte* atelier();
    const Carte* aventurier();
    const Carte* bibliotheque();
    const Carte* bucheron();
    const Carte* bureaucrate();
    const Carte* cave();
    const Carte* chambreDuConseil();
    const Carte* chancelier();
    const Carte* chapelle();
    const Carte* douves();
    const Carte* espion();
    const Carte* festin();
    const Carte* festival();
    const Carte* forgeron();
    const Carte* jardins();
    const Carte* laboratoire();
    const Carte* marche();
    const Carte* milice();
    const Carte* mine();
    const Carte* preteurSurGages();
    const Carte* renovation();
    const Carte* salleDuTrone();
    const Carte* sorciere();
    const Carte* village();
    const Carte* voleur();

    const std::vector<const Carte*>& catalogue();
    
    const std::vector<const Carte*>& royaume();
}