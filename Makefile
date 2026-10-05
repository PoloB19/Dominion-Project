# Exemple de Makefile pour le projet
# Organisation:
# créer un répertoire src/ contenant les .cpp
# créer un répertoite include/ contenant les .h
#
# Le Makefile détecte automatiquement les fichiers source ($(wildcard
# $(SRC_DIR)/*.cpp)) pour ne pas avoir à les spécifier manuellement
# Les chemins sont transformés automatiquement: $(patsubst) convertit les
# .cpp en .o dans le dossier build/ qui est créé automatiquement
# Les headers sont inclus via le flag -Iinclude

CXX = g++
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
TARGET = $(BUILD_DIR)/dominion	# nom de la cible

#Trouve récursivement tous les sous-dossiers de include/ et ajouter le flag -I à chacun
INC_DIRS = $(shell find $(INC_DIR) -type d)
INC_FLAGS = $(addprefix -I, $(INC_DIRS))
CXXFLAGS = -Wall -Wextra -Werror -std=c++11 $(INC_FLAGS)

#Trouve récursivement tous les fichiers .cpp dans src/ et ses sous-dossiers
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')

#Génére les chemins des fichiers .o correspondants dans build/
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o, $(SRCS))

# Règle de compilation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -c -o $@

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@

.PHONY: run clean

run: $(TARGET)
	$(TARGET)

clean:
	rm -rf $(BUILD_DIR)