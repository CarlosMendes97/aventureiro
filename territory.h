#ifndef TERRITORY_H
#define TERRITORY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Territory Territory; // Declaração forward

// Definindo um Território com Adjacência Não-Linear
struct Territory {
    char name[50];
    int armies;
    int ownerId;
    
    // Lista de Adjacência: Array dinâmico de ponteiros para vizinhos
    Territory** neighbors;
    int neighborCount;
};

// Protótipos de Funções
Territory* createTerritory(const char* name, int initialArmies, int initialOwnerId);
void addNeighbor(Territory* t1, Territory* t2);
void freeTerritory(Territory* t); // Função de liberação (Memória)

#endif // TERRITORY_H
