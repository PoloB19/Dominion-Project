#include "carte.hpp"

Carte::Carte(std::string description, unsigned short prix) : description(description), prix(prix), id(nextId++){};

