#pragma once

#include <string>

class Carte {

    private:

        static unsigned short m_nextId;
        unsigned short m_id;
        unsigned short m_prix;
        std::string m_description;

    public:
        Carte(std::string description, unsigned short prix);
        ~Carte();

};
