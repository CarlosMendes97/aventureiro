#include "combat.h"
#include <time.h>
#include <stdlib.h>

// Implementação da Estratégia de Combate (Exemplo Simples)
int standardDiceRollCombat(Territory* attacker, Territory* defender) {
    // Simulação simplificada de um dado: 1-6
    // O atacante ganha se tirar um valor maior que o defensor.
    int attackerRoll = (rand() % 6) + 1;
    int defenderRoll = (rand() % 6) + 1;
    
    if (attackerRoll > defenderRoll) {
        // Atacante vence: Defensor perde 1 exército
        if (defender->armies > 0) {
            defender->armies--;
            printf("  -> Vitória do Atacante! %s perde 1 exército.\n", defender->name);
            return 1; // 1 exército perdido pelo defensor
        }
    } else {
        // Defensor vence/Empate: Atacante perde 1 exército
        if (attacker->armies > 1) { // Precisa ter pelo menos 2 para atacar e perder 1
            attacker->armies--;
            printf("  -> Vitória do Defensor! %s perde 1 exército.\n", attacker->name);
        }
    }
    return 0; // Exércitos perdidos (para efeitos de simplicidade, focamos na perda do defensor)
}

// Função Principal que aceita um ponteiro para função
void initiateAttack(Territory* attacker, Territory* defender, CombatStrategy strategy) {
    if (attacker->ownerId == defender->ownerId) {
        printf("Ataque Inválido: Territórios pertencem ao mesmo jogador.\n");
        return;
    }
    
    printf("\n--- ATAQUE INICIADO ---\n");
    printf("%s (Jogador %d) ataca %s (Jogador %d).\n", 
           attacker->name, attacker->ownerId, defender->name, defender->ownerId);

    // Loop de combate até que um exército seja zerado ou o atacante pare
    while (attacker->armies > 1 && defender->armies > 0) {
        printf("  [Luta] %s (%d) vs %s (%d)\n", attacker->name, attacker->armies, defender->name, defender->armies);
        
        // **Chamada através do Ponteiro para Função:**
        // A lógica real de combate é delegada à função apontada por 'strategy'.
        strategy(attacker, defender); 
        
        // Verificação de vitória/continuação (simplificada)
        if (defender->armies == 0) {
            printf(">>> VITÓRIA! %s conquistou %s!\n", attacker->name, defender->name);
            defender->ownerId = attacker->ownerId;
            // Movimentação de exércitos e outras regras iriam aqui
            break;
        }
        // Se o atacante não tem mais exércitos suficientes (1 é o mínimo para permanecer)
        if (attacker->armies == 1) {
             printf(">>> O Atacante não tem mais exércitos suficientes para continuar o ataque.\n");
             break;
        }
    }
}
