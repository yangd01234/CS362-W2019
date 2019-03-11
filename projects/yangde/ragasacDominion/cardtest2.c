/*
Author: Derek Yang
Program: cardtest2.c
Description:
 The following test will go through unittesting for
 the adventerur card.  The template was taken from the
 provided assignment template.
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"


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

    /*adventurer info: http://wiki.dominionstrategy.com/index.php/File:Adventurer.jpg
     * Reveal cards from deck until 2 treasure cards are revealed.
     * Put two treasure cards into hand
     * discard other revealed cards
     */
    printf("----------------- Testing Card cardEffect(): %s ----------------\n", TESTCARD);
    // ----------- TEST 1: Adventurer gives +2 copper and discards 0--------------
    printf("==TEST 1 cardEffect(): Adventurer gives +2 copper and discards 0\ncards in deck pos 0,1\n\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    // ----------- Add adventurer to player's hand --------------
    testG.hand[thisPlayer][0] = adventurer;

    // ----------- Set 2 treasures in the first two positions --------------
    testG.deck[thisPlayer][0] = copper;
    testG.deck[thisPlayer][1] = copper;
    testG.deckCount[thisPlayer] = 2;

    // ----------- Run tests player 1--------------
    cardEffect(adventurer,choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("TEST 1a: Check player 1 changes\n");
    ASSERT(testG.handCount[thisPlayer], G.handCount[thisPlayer]+2);
    printf("PLAYER1 hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]+2);
    ASSERT(testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    printf("PLAYER1 discard count = %d expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    ASSERT(testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    printf("PLAYER1 deck count = %d expected = %d\n\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]-2);
    // ----------- Run tests player 2 check state of game--------------
    printf("TEST 1b: Check if player2 is unaffected STATE OF GAME\n");
    ASSERT(testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    printf("PLAYER2 hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    ASSERT(testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
    printf("PLAYER2 discard count = %d expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
    ASSERT(testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
    printf("PLAYER2 deck count = %d expected = %d\n\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);




    // ----------- TEST 2: Copper placed deeper in deck-------------
    printf("==TEST 2 cardEffect(): Adventurer gives +2 copper and discards 2\n"
           "cards in deck pos 2,3\n\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    // ----------- Add adventurer to player's hand --------------
    testG.hand[thisPlayer][0] = adventurer;

    // ----------- Set 2 treasures in the 3rd and 4th positions --------------
    testG.deck[thisPlayer][0] = adventurer;
    testG.deck[thisPlayer][1] = adventurer;
    testG.deck[thisPlayer][2] = copper;
    testG.deck[thisPlayer][3] = copper;
    testG.deckCount[thisPlayer] = 4;

    // ----------- Run tests player 1--------------
    cardEffect(adventurer,choice1, choice2, choice3, &testG, handpos, &bonus);
    printf("TEST 2a: Check player 1 changes\n");
    ASSERT(testG.handCount[thisPlayer], G.handCount[thisPlayer]+2);
    printf("PLAYER1 hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]+2);
    ASSERT(testG.discardCount[thisPlayer], G.discardCount[thisPlayer]+2);
    printf("PLAYER1 discard count = %d expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]+2);
    ASSERT(testG.deckCount[thisPlayer], 0);
    printf("PLAYER1 deck count = %d expected = %d\n\n", testG.deckCount[thisPlayer], 0);

    // ----------- Run tests player 2 check state of game--------------
    printf("TEST 2b: Check if player2 is unaffected STATE OF GAME\n");
    ASSERT(testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    printf("PLAYER2 hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    ASSERT(testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
    printf("PLAYER2 discard count = %d expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
    ASSERT(testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
    printf("PLAYER2 deck count = %d expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);

    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTCARD);





    return 0;
}