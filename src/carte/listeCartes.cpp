#include "dominion.hpp"

namespace Cartes {

    // Catalogue de toutes les cartes
    const std::vector<const Carte*>& catalogue() {
        static const std::vector<const Carte*> v = {
            // Trésors
            getCarte<Cuivre>(), getCarte<Argent>(), getCarte<Or>(),
            // Malédiction
            getCarte<Malediction>(),
            // Victoire
            getCarte<Domaine>(), getCarte<Duche>(), getCarte<Province>(),
            // Royaume
            getCarte<Jardins>(), getCarte<Atelier>(), getCarte<Aventurier>(), getCarte<Bibliotheque>(), 
            getCarte<Bucheron>(), getCarte<Cave>(), getCarte<ChambreDuConseil>(), getCarte<Chancelier>(), 
            getCarte<Chapelle>(), getCarte<Douves>(), getCarte<Espion>(), getCarte<Festin>(), 
            getCarte<Festival>(), getCarte<Forgeron>(), getCarte<Laboratoire>(), getCarte<Marche>(), 
            getCarte<Milice>(), getCarte<Mine>(), getCarte<PreteurSurGages>(), getCarte<Renovation>(),
            getCarte<SalleDuTrone>(), getCarte<Sorciere>(), getCarte<Village>(), getCarte<Voleur>(), 
            getCarte<Bureaucrate>()
        };
        return v;
    }

    constexpr size_t NB_CARTES_COMMUNES = 7; // cuivre, argent, or, malédiction, domaine, duché, province
    
    // Catalogue des cartes Royaume
    const std::vector<const Carte*>& royaume() {
        static const std::vector<const Carte*> v(catalogue().begin() + NB_CARTES_COMMUNES, catalogue().end());
        return v;
    }
}