#pragma once

#include <string>

class Carte {

    private:
        static unsigned short m_nextId;
        unsigned short m_id;
        unsigned short m_prix;
        std::string m_description;

    public:
        Carte(unsigned short prix, std::string description);
        ~Carte();

        virtual std::string getCarteType() const = 0;
        
};
