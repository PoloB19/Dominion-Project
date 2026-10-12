#include "dominion.hpp"

namespace Cartes {
    // Trésor
    const Carte* cuivre() { static const Cuivre c; return &c; }
    const Carte* argent() { static const Argent c; return &c; }
    const Carte* or_()    { static const Or c; return &c; }
    // Malédiction
    const Carte* malediction() {static const Malediction c; return &c; }
    // Victoire
    const Carte* domaine()  { static const Domaine c; return &c; }
    const Carte* duche()    { static const Duche c; return &c; }
    const Carte* province() { static const Province c; return &c; }
    // Royaume
    const Carte* jardins() { static const Jardins c; return &c; }
    const Carte* atelier() { static const Atelier c;  return &c; }
    const Carte* bucheron() { static const Bucheron c;  return &c; }
    const Carte* aventurier() { static const Aventurier c;  return &c; }
    const Carte* bibliotheque() { static const Bibliotheque c;  return &c; }
    const Carte* cave() { static const Cave c;  return &c; }
    const Carte* festival() { static const Festival c;  return &c; }
    const Carte* forgeron() { static const Forgeron c;  return &c; }
    const Carte* laboratoire() { static const Laboratoire c;  return &c; }
    const Carte* chambreDuConseil() { static const ChambreDuConseil c;  return &c; }
    const Carte* chancelier() { static const Chancelier c;  return &c; }
    const Carte* chapelle() { static const Chapelle c;  return &c; }
    const Carte* festin() { static const Festin c;  return &c; }
    const Carte* marche() { static const Marche c;  return &c; }
    const Carte* mine() { static const Mine c;  return &c; }
    const Carte* preteurSurGages() { static const PreteurSurGages c;  return &c; }
    const Carte* renovation() { static const Renovation c;  return &c; }
    const Carte* salleDuTrone() { static const SalleDuTrone c;  return &c; }
    const Carte* village() { static const Village c;  return &c; }
}