#pragma once

#include <string>
#include <vector>

#include "plateau.hpp"
#include "joueur.hpp"
#include "carte.hpp"

class Sauvegarde {
    private:
        static const Carte* trouverCarteParNom(const std::string& nom);
        static std::vector<std::string> decouperLigne(const std::string& ligne);

    public:
        static bool sauvegarder(const Plateau& P, size_t numJoueur, bool phaseAchat, const std::string& cheminFichier = "sauvegarde.txt");
        static bool charger(Plateau& P, size_t& numJoueur, bool& phaseAchat, const std::string& cheminFichier = "sauvegarde.txt");
};
