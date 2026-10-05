#pragma once

#include <string>

class Carte {

    private:

        unsigned short id;
        static unsigned short nextId;

        std::string description;
        unsigned short prix;

    public:
        Carte(std::string description, unsigned short prix);
        ~Carte();

};
