// main.c
#include "territory.h"
#include "combat.h"
#include <time.h>

int main() {
    // Inicializa o gerador de números aleatórios para simulação de dados
    srand(time(NULL)); 

    // 1. Criação dos territórios (Alocação Dinâmica)
    Territory* t_att = createTerritory("Ataque", 5, 1);
    Territory* t_def = createTerritory("Defesa", 2, 2);

    // 2. Conexão dos territórios (Estrutura Não-Linear / realloc)
    addNeighbor(t_att, t_def);
    
    printf("--- Estrutura Inicial ---\n");
    printf("%s (Dono: %d) tem %d exércitos.\n", t_att->name, t_att->ownerId, t_att->armies);
    printf("%s (Dono: %d) tem %d exércitos.\n", t_def->name, t_def->ownerId, t_def->armies);
    printf("Vizinhos de %s: %s\n", t_att->name, t_att->neighbors[0]->name);
    
    // 3. Inicia o Ataque (Uso de Ponteiro para Função)
    // Passamos a função 'standardDiceRollCombat' como parâmetro.
    initiateAttack(t_att, t_def, standardDiceRollCombat);
    
    printf("\n--- Resultado Final ---\n");
    printf("%s (Dono: %d) tem %d exércitos.\n", t_att->name, t_att->ownerId, t_att->armies);
    printf("%s (Dono: %d) tem %d exércitos.\n", t_def->name, t_def->ownerId, t_def->armies);

    // 4. Liberação da Memória (Uso de free)
    // Se o território t_def foi conquistado, ele ainda precisa ser liberado.
    freeTerritory(t_att); 
    freeTerritory(t_def);
    
    printf("\n--- Memória liberada ---\n");
    return 0;
}
