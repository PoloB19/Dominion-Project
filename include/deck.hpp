#pragma once

#include <vector>
#include "carte.h"

class Deck {

    private:

        std::vector<Carte> cartes;

    public:

        Deck();
        ~Deck();

        const std::vector<Carte>& getCartes() const;
};