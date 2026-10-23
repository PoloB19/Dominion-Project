#include "sauvegarde.hpp"
#include "listeCartes.hpp"

#include <fstream>
#include <sstream>

// Utilitaires

const Carte* Sauvegarde::trouverCarteParNom(const std::string& nom) {
    for (const Carte* c : Cartes::catalogue()) {
        if (c->getNom() == nom) {
            return c;
        }
    }
    return nullptr;
}

std::vector<std::string> Sauvegarde::decouperLigne(const std::string& ligne) {
    std::vector<std::string> elements;
    std::stringstream flux(ligne);
    std::string element;

    while (std::getline(flux, element, ';')) {
        elements.push_back(element);
    }
    return elements;
}

static void ecrirePile(std::ofstream& fichier, const std::string& prefixe, std::stack<const Carte*> copiePile) {
    std::vector<const Carte*> temp;
    while (!copiePile.empty()) {
        temp.push_back(copiePile.top());
        copiePile.pop();
    }

    fichier << prefixe;
    // Lecture à l'envers du fond de la pile vers le dessus
    for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
        fichier << ";" << (*it)->getNom();
    }
    fichier << "\n";
}

bool Sauvegarde::sauvegarder(const Plateau& P, size_t numJoueur, bool phaseAchat, const std::string& cheminFichier) {
    std::ofstream fichier(cheminFichier);
    if (!fichier.is_open()) {
        return false;
    }

    // Informations sur le tour en cours
    fichier << "TOUR;" << numJoueur << ";" << (phaseAchat ? 1 : 0) << "\n";

    // Piles du plateau
    for (const auto& [carte, quantite] : P.m_piles) {
        fichier << "PILE;" << carte->getNom() << ";" << quantite << "\n";
    }

    ecrirePile(fichier, "REBUT", P.m_rebut);

    // Joueurs et leurs 4 zones de cartes
    for (const Joueur& j : P.m_joueurs) {
        fichier << "JOUEUR;" << j.m_pseudo << ";"
                << j.m_nbAction << ";"
                << j.m_nbAchat << ";"
                << j.m_pieces << ";"
                << j.m_nbToursJoues << "\n";

        fichier << "MAIN";
        for (const Carte* c : j.m_main) {
            fichier << ";" << c->getNom();
        }
        fichier << "\n";

        fichier << "EN_JEU";
        for (const Carte* c : j.m_enJeu) {
            fichier << ";" << c->getNom();
        }
        fichier << "\n";

        ecrirePile(fichier, "PIOCHE", j.m_pioche);
        ecrirePile(fichier, "DEFAUSSE", j.m_defausse);
    }

    return true;
}

bool Sauvegarde::charger(Plateau& P, size_t& numJoueur, bool& phaseAchat, const std::string& cheminFichier) {
    std::ifstream fichier(cheminFichier);
    if (!fichier.is_open()) {
        return false;
    }

    // Initialisation
    P.m_joueurs.clear();
    P.m_piles.clear();
    P.m_rebut = std::stack<const Carte*>();

    std::string ligne;
    while (std::getline(fichier, ligne)) {
        if (ligne.empty()) continue;

        std::vector<std::string> elements = decouperLigne(ligne);
        if (elements.empty()) continue;

        const std::string& prefixe = elements.at(0);

        if (prefixe == "TOUR" && elements.size() >= 3) {
            numJoueur = std::stoul(elements.at(1));
            phaseAchat = (std::stoul(elements.at(2)) != 0);
        }
        else if (prefixe == "PILE" && elements.size() >= 3) {
            const Carte* c = trouverCarteParNom(elements.at(1));
            unsigned short qte = std::stoul(elements.at(2));
            if (c != nullptr) {
                P.m_piles[c] = qte;
            }
        }
        else if (prefixe == "REBUT") {
            for (size_t i = 1; i < elements.size(); i++) {
                const Carte* c = trouverCarteParNom(elements.at(i));
                if (c != nullptr) P.m_rebut.push(c);
            }
        }

        else if (prefixe == "JOUEUR" && elements.size() >= 6) {
            P.m_joueurs.emplace_back(elements.at(1));
            Joueur& j = P.m_joueurs.back();
            j.m_nbAction     = std::stoul(elements.at(2));
            j.m_nbAchat      = std::stoul(elements.at(3));
            j.m_pieces       = std::stoul(elements.at(4));
            j.m_nbToursJoues = std::stoul(elements.at(5));
        }

        else if (prefixe == "MAIN" && !P.m_joueurs.empty()) {
            Joueur& j = P.m_joueurs.back();
            for (size_t i = 1; i < elements.size(); i++) {
                const Carte* c = trouverCarteParNom(elements.at(i));
                if (c != nullptr) j.m_main.push_back(c);
            }
        }
        else if (prefixe == "EN_JEU" && !P.m_joueurs.empty()) {
            Joueur& j = P.m_joueurs.back();
            for (size_t i = 1; i < elements.size(); i++) {
                const Carte* c = trouverCarteParNom(elements.at(i));
                if (c != nullptr) j.m_enJeu.push_back(c);
            }
        }
        else if (prefixe == "PIOCHE" && !P.m_joueurs.empty()) {
            Joueur& j = P.m_joueurs.back();
            for (size_t i = 1; i < elements.size(); i++) {
                const Carte* c = trouverCarteParNom(elements.at(i));
                if (c != nullptr) j.m_pioche.push(c);
            }
        }
        else if (prefixe == "DEFAUSSE" && !P.m_joueurs.empty()) {
            Joueur& j = P.m_joueurs.back();
            for (size_t i = 1; i < elements.size(); i++) {
                const Carte* c = trouverCarteParNom(elements.at(i));
                if (c != nullptr) j.m_defausse.push(c);
            }
        }
    }

    // Vérifie que la sauvegarde est correcte
    return !P.m_joueurs.empty() && !P.m_piles.empty();
}
