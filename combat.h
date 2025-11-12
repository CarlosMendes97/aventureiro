#ifndef COMBAT_H
#define COMBAT_H

#include "territory.h"

// **Ponteiro para Função (Tipo Abstrato)**
// Define um tipo de ponteiro para função que aceita dois ponteiros Territory
// e retorna um int (o número de exércitos perdidos pelo defensor, por exemplo).
typedef int (*CombatStrategy)(Territory* attacker, Territory* defender);

// Protótipo da função de ataque principal
void initiateAttack(Territory* attacker, Territory* defender, CombatStrategy strategy);

// Protótipo de uma estratégia específica
int standardDiceRollCombat(Territory* attacker, Territory* defender);

#endif // COMBAT_H
