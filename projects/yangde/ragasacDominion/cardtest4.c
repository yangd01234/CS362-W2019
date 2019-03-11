/*
Author: Derek Yang
Program: cardtest4.c
Description:
 The following test will go through unittesting for
 the village card.  The template was taken from the
 provided assignment template.
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"


void ASSERT(int a, int b){
    if (a == b) {
        printf("PASS:  ");
    } else {
        printf("FAIL:  ");
    }
}


// compares the previous game state to next
void compareGameState(struct gameState *originState, struct gameState *testState){
    int numStatesChanged = 0;
    ASSERT(testState->numPlayers, originState->numPlayers);
    printf("numPlayers count = %d  expected = %d\n", testState->numPlayers, originState->numPlayers);

    ASSERT(testState->outpostPlayed, originState->outpostPlayed);
    printf("outpostPlayed count = %d  expected = %d\n", testState->outpostPlayed, originState->outpostPlayed);

    ASSERT(testState->outpostTurn, originState->outpostTurn);
    printf("outpostTurn count = %d  expected = %d\n", testState->outpostTurn, originState->outpostTurn);

    ASSERT(testState->whoseTurn, originState->whoseTurn);
    printf("whoseTurn count = %d  expected = %d\n", testState->whoseTurn, originState->whoseTurn);

    ASSERT(testState->phase, originState->phase);
    printf("phase count = %d  expected = %d\n", testState->phase, originState->phase);

    ASSERT(testState->numActions, originState->numActions+2);
    printf("numActions count = %d  expected = %d\n", testState->numActions, originState->numActions+2);

    ASSERT(testState->coins, originState->coins);
    printf("coins count = %d  expected = %d\n", testState->coins, originState->coins);

    ASSERT(testState->numBuys, originState->numBuys);
    printf("numBuys count = %d  expected = %d\n", testState->numBuys, originState->numBuys);

    ASSERT(testState->playedCardCount, originState->playedCardCount);
    printf("playedCardCount count = %d  expected = %d\n\n", testState->playedCardCount, originState->playedCardCount);
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

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    // ----------- TEST 1: village draws +1 card for current player--------------

    memcpy(&testG, &G, sizeof(struct gameState));

    // ----------- Add village to player's hand --------------
    testG.hand[thisPlayer][0] = village;

    // ----------- Run tests player 1--------------
    cardEffect(village,choice1, choice2, choice3, &testG, handpos, &bonus);

    // ----------- Check state of game, should have +2 actions -------------
    compareGameState(&G, &testG);

    printf("\n==TEST 1: village draws +1 card\n");
    printf("TEST 1a: Check player 1 changes\n");
    ASSERT(testG.handCount[thisPlayer], G.handCount[thisPlayer]+1);
    printf("PLAYER1 hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]+1);
    ASSERT(testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    printf("PLAYER1 discard count = %d expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    ASSERT(testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    printf("PLAYER1 deck count = %d expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]-1);
    ASSERT(testG.numBuys, G.numBuys);
    printf("Number of buys count = %d expected = %d\n", testG.numBuys, G.numBuys);
    ASSERT(testG.numActions, G.numActions+2);
    printf("Number of actions count = %d expected = %d\n\n", testG.numActions, G.numActions+2);

    // ----------- Run tests player 2 check state of game--------------
    printf("TEST 1b: Check if player2 is unaffected STATE OF GAME\n");
    ASSERT(testG.handCount[nextPlayer], G.handCount[nextPlayer]+1);
    printf("PLAYER2 hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]+1);
    ASSERT(testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
    printf("PLAYER2 discard count = %d expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
    ASSERT(testG.deckCount[nextPlayer], G.deckCount[nextPlayer]-1);
    printf("PLAYER2 deck count = %d expected = %d\n\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]-1);


    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);



    return 0;
}