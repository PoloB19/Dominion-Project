#include "carte.hpp"

Carte::Carte(std::string description, unsigned short prix) : m_description(description), m_prix(prix), m_id(m_nextId++){};

