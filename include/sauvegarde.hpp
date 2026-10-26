#pragma once

#include <string>
#include <vector>

#include <fstream>
#include <sstream>

#include "plateau.hpp"
#include "joueur.hpp"
#include "carte.hpp"

class Sauvegarde {
    private:
        static const Carte* trouverCarteParNom(const std::string& nom);
        static std::vector<std::string> decouperLigne(const std::string& ligne);
        static void ecrirePile(std::ofstream& fichier, const std::string& prefixe, std::stack<const Carte*> copiePile);

    public:
        static bool sauvegarder(const Plateau& P, size_t numJoueur, bool phaseAchat, const std::string& cheminFichier = "sauvegarde.txt");
        static bool charger(Plateau& P, size_t& numJoueur, bool& phaseAchat, const std::string& cheminFichier = "sauvegarde.txt");
        static bool effacer(const std::string& cheminFichier = "sauvegarde.txt");
    };
