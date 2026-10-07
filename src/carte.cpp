#include "carte.hpp"

unsigned short Carte::m_nextId = 1;

Carte::Carte(unsigned short prix, std::string description) : m_prix(prix), m_description(description), m_id(m_nextId++){};