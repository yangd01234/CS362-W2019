/*
Author: Derek Yang
Program: cardtest1.c
Description:
 The following test will go through unittesting for
 the smithy card.  The template was taken from the
 provided assignment template.
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"


void ASSERT(int a, int b){
    if (a == b) {
        printf("PASS:  ");
    } else {
        printf("FAIL:  ");
    }
}


int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int nextPlayer = 1;

    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    /*smithy
     * Draw 3 cards
     * discard one card from hand
     */
    printf("----------------- Testing Card cardEffect(): %s ----------------\n", TESTCARD);
    // ----------- TEST 1: Adventurer gives +2 copper and discards 0--------------
    printf("==TEST 1 cardEffect(): Smithy draws +3 cards and discards 1\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    // ----------- Add smithy to player's hand --------------
    testG.hand[thisPlayer][0] = smithy;

    // ----------- Run tests player 1--------------
    cardEffect(smithy,choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("TEST 1a: Check player 1 changes\n");
    ASSERT(testG.handCount[thisPlayer], G.handCount[thisPlayer]+2);
    printf("PLAYER1 hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]+2);
    ASSERT(testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    printf("PLAYER1 discard count = %d expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]+1);
    ASSERT(testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    printf("PLAYER1 deck count = %d expected = %d\n\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]-3);

    // ----------- Run tests player 2 check state of game--------------
    printf("TEST 1b: Check if player2 is unaffected STATE OF GAME\n");
    ASSERT(testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    printf("PLAYER2 hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    ASSERT(testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
    printf("PLAYER2 discard count = %d expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
    ASSERT(testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
    printf("PLAYER2 deck count = %d expected = %d\n\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);


    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);





    return 0;
}