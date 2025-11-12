#include "territory.h"
#include <string.h>

// Implementação da criação (sem mudanças, exceto a inicialização da adjacência)
Territory* createTerritory(const char* name, int initialArmies, int initialOwnerId) {
    Territory* newTerritory = (Territory*)malloc(sizeof(Territory));
    if (newTerritory == NULL) {
        perror("Erro ao alocar memória para o novo território.");
        exit(EXIT_FAILURE);
    }

    strncpy(newTerritory->name, name, 49);
    newTerritory->name[49] = '\0';
    newTerritory->armies = initialArmies;
    newTerritory->ownerId = initialOwnerId;
    
    // Inicializa a lista de adjacência
    newTerritory->neighbors = NULL;
    newTerritory->neighborCount = 0;
    
    return newTerritory;
}

// **Função com Alocação Dinâmica (realloc)**
// Adiciona um vizinho ao território t1 (e t2, se for bidirecional)
void addNeighbor(Territory* t1, Territory* t2) {
    // 1. Adiciona t2 como vizinho de t1
    // Usa realloc para aumentar o tamanho do array de ponteiros
    t1->neighbors = (Territory**)realloc(t1->neighbors, 
                                        (t1->neighborCount + 1) * sizeof(Territory*));
    
    if (t1->neighbors == NULL) {
        perror("Erro ao realocar memória para vizinhos.");
        exit(EXIT_FAILURE);
    }
    
    t1->neighbors[t1->neighborCount] = t2;
    t1->neighborCount++;

    // 2. (Geralmente, adjacência é bidirecional no jogo) Adiciona t1 como vizinho de t2
    t2->neighbors = (Territory**)realloc(t2->neighbors, 
                                        (t2->neighborCount + 1) * sizeof(Territory*));
    
    if (t2->neighbors == NULL) {
        perror("Erro ao realocar memória para vizinhos.");
        exit(EXIT_FAILURE);
    }
    
    t2->neighbors[t2->neighborCount] = t1;
    t2->neighborCount++;
}

// **Função com Gerenciamento de Memória (free)**
void freeTerritory(Territory* t) {
    if (t != NULL) {
        // Primeiro, libera o array de ponteiros dos vizinhos (alocado com realloc/malloc)
        if (t->neighbors != NULL) {
            free(t->neighbors);
        }
        // Segundo, libera a própria struct Territory (alocada com malloc)
        free(t);
    }
}
