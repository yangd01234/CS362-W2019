/* Author: Derek Yang
 * Random Testing Card 1
 * Template taken from Random Testing Quiz
 * Random test for the: Village Card
 * Add +1 card, +2 actions, and discard 1 card.
 * Method under test: village_card
 * Dependencies: int currentPlayer, struct gameState *state, int handPos
 * 
 * Random Testing Guidelines:
 * 1.  identify method under test
 * 2.  identify dependencies (params)
 * 3.  write code to generate random inputs for method
 * 4.  invoke method
 * 5.  check if stopping criterion (ex num of loops) satisfied, if not go to step 2
 */



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <assert.h>
#include "rngs.h"

#define TESTFUNCTION "village_card()"
#define TESTPARAMS "int currentPlayer, struct gameState *state, int handPos"

/***********************************************
 * ASSERT(int a, int b)
 * prints PASS: if a == b or FAIL: if a != b
 **********************************************/
void ASSERT(int a, int b){
    if (a == b) {
        printf("PASS:  ");
    } else {
        printf("FAIL:  ");
    }
}

/***********************************************
 * villageTest()
 * Random test for village_card() function
 * Checks for:
 * +1 card to player hand
 * +2 actions
 * +1 discard after function call
 * Test Stopping Criteria: Success or 10,000 runs
 **********************************************/
void villageTest() {
    srand(time(NULL));
    int numPlayers = 2;
    int currPlayer = 0;
    int seed = 1000;
    int numTests = 1000000;
    int currTest = 0;
    int playerDeck, playerHandPos, playerDiscard, playerAction, playerHandCount;
    int playerDeckRes, playerHandCountRes, playerDiscardRes, playerActionRes;

    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    initializeGame(numPlayers, k, seed, &G);

    // STEP 1: Identify function under test
    printf("----------------- Random Testing Function: %s ----------------\n", TESTFUNCTION);
    // STEP 2: Identify params
    printf("Params: %s ----------------\n", TESTPARAMS);

    while(currTest < numTests){
        // clear the game states
        memcpy(&testG, &G, sizeof(struct gameState));
        // STEP 3: generate random inputs for params
        playerDeck = rand() % (MAX_DECK);
        playerHandPos = rand() % (MAX_HAND);

        playerDiscard = rand() % (MAX_DECK);
        playerAction = rand() % 100;

        // assign random inputs
        testG.deckCount[0] = playerDeck;
        testG.discardCount[0] = playerDiscard;
        testG.numActions = playerAction;
        testG.handCount[0] = playerHandCount;

        // STEP 4: Invoke function
        village_card(currPlayer, &testG, playerHandPos);

        // STEP 5: Check if stopping criteria met
        if (testG.deckCount[0] == playerDeck-1) playerDeckRes++;
        if (testG.handCount[0] == playerHandCount) playerHandCountRes++;
        if (testG.discardCount[0] == playerDiscard+1) playerDiscardRes++;
        if (testG.numActions == playerAction+2) playerActionRes++;
        currTest++;
    }

    // return test summary
    printf("Total number of tests ran: %d\n", currTest);
    ASSERT(playerDeckRes, numTests);
    printf("Deck Count -1 success rate: %d out of %d\n",playerDeckRes, numTests);
    ASSERT(playerHandCountRes, numTests);
    printf("Hand Count unchanged success rate: %d out of %d%\n",playerHandCountRes, numTests);
    ASSERT(playerDiscardRes, numTests);
    printf("Discard Count +1 success rate: %d out of %d%\n",playerDiscardRes, numTests);
    ASSERT(playerActionRes, numTests);
    printf("Action Count +2 success rate: %d out of %d%\n",playerActionRes, numTests);
    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTFUNCTION);
}


int main(int argc, char *argv[])
{
    villageTest();
    return 0;
}