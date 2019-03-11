/* Author: Derek Yang
 * Random Testing Card Adventurer
 * Template taken from Random Testing Quiz
 * Random test for the: Adventurer Card
 * Add +3 card and discard 1 card.
 * Method under test: adventurer_card
 * Dependencies: int currentPlayer, struct gameState *state
 * Tests all three treasures: copper, silver, and gold

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

#define TESTFUNCTION "adventurer_card()"
#define TESTPARAMS "int currentPlayer, struct gameState *state"

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
 * treasurePrint(CARD testCard)
 * prints type of treasure card
 * returns string
 **********************************************/
const char *treasurePrint(enum CARD testCard){

    switch(testCard){
        case copper:
            return "copper";
        case silver:
            return "silver";
        case gold:
            return "gold";
    }
}

/***********************************************
 * adventurerTest()
 * Random test for adventurer_card() function
 * Checks for:
 * +2 cards in hand from deck
 * +n in discard where n == number of drawn cards
 * -n from deck where n == number of drawn cards
 **********************************************/
void advenurerTest(enum CARD testCard ) {
    srand(time(NULL));
    int numPlayers = 2;
    int currPlayer = 0;
    int seed = 1000;
    int numTests = 100000;
    int currTest = 0;
    int playerDeck, playerHandPos, playerDiscard, playerAction, playerHandCount;
    int playerDeckRes, playerHandCountRes, playerDiscardRes, playerActionRes;

    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    initializeGame(numPlayers, k, seed, &G);

    // STEP 1: Identify function under test
    printf("----------------- Random Testing Function: %s ", TESTFUNCTION);
    printf("with treasure: %s------\n",treasurePrint(testCard));

    // STEP 2: Identify params
    printf("Params: %s ----------------\n", TESTPARAMS);

    while(currTest < numTests){
        // clear the game states
        memcpy(&testG, &G, sizeof(struct gameState));
        // STEP 3: generate random inputs for params
        playerDeck = rand() % (MAX_DECK);
        playerHandPos = rand() % (MAX_HAND);
        playerDiscard = rand() % (MAX_DECK);
        int treasurePosOne = rand() % (MAX_DECK);
        int treasurePosTwo = rand() % (MAX_DECK);

        playerAction = rand() % 100;

        // assign random inputs
        testG.deckCount[0] = playerDeck;
        testG.discardCount[0] = playerDiscard;
        testG.numActions = playerAction;
        testG.handCount[0] = playerHandCount;
        testG.deck[0][treasurePosOne] == testCard;
        testG.deck[0][treasurePosTwo] == testCard;

        // STEP 4: Invoke function
        adventurerEffect(&testG);
        //adventurer_card(currPlayer, &testG);

        // STEP 5: Check if stopping criteria met
        // check if new deck count == old deck count - discard count
        if (testG.deckCount[0] == (playerDeck-testG.discardCount[0])) playerDeckRes++;
        // check if hand count + 2
        if (testG.handCount[0] == playerHandCount+2) playerHandCountRes++;
        // check if discard count == old deck count - new deck count
        if (testG.discardCount[0] == (playerDiscard-testG.deckCount[0])) playerDiscardRes++;
        currTest++;
    }

    // return test summary
    printf("Total number of tests ran: %d\n", currTest);
    ASSERT(playerDeckRes, numTests);
    printf("Deck Count -3 success rate: %d out of %d\n",playerDeckRes, numTests);
    ASSERT(playerHandCountRes, numTests);
    printf("Hand Count +3 success rate: %d out of %d\n",playerHandCountRes, numTests);
    ASSERT(playerDiscardRes, numTests);
    printf("Discard Count +1 success rate: %d out of %d\n",playerDiscardRes, numTests);
    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTFUNCTION);
}


int main(int argc, char *argv[])
{
    // test for copper, silver, and gold
    advenurerTest(copper);
    advenurerTest(silver);
    advenurerTest(gold);

    return 0;
}