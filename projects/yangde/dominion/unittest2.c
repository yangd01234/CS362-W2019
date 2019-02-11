/*
Author: Derek Yang
Program: unittest2.c
Description:
 The following test will go through unittesting for
 the getCost() function.  The template was taken from the
 provided assignment template.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define TESTFUNCTION "getCost()"


// custom asset function
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

    ASSERT(testState->numActions, originState->numActions);
    printf("numActions count = %d  expected = %d\n", testState->numActions, originState->numActions);

    ASSERT(testState->coins, originState->coins);
    printf("coins count = %d  expected = %d\n", testState->coins, originState->coins);

    ASSERT(testState->numBuys, originState->numBuys);
    printf("numBuys count = %d  expected = %d\n", testState->numBuys, originState->numBuys);

    ASSERT(testState->playedCardCount, originState->playedCardCount);
    printf("playedCardCount count = %d  expected = %d\n\n", testState->playedCardCount, originState->playedCardCount);
}


int main() {
    int i;
    int deckCount;
    int seed = 1000;
    int numPlayer = 2;
    int numPlayers = 2;
    int thisPlayer = 0;
    int nextPlayer = 1;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall};

    int complete_cost_list[27] =   {curse,
            estate,
            duchy,
            province,
            copper,
            silver,
            gold,
            adventurer,
            council_room,
            feast,
            gardens,
            mine,
            remodel,
            smithy,
            village,
            baron,
            great_hall,
            minion,
            steward,
            tribute,
            ambassador,
            cutpurse,
            embargo,
            outpost,
            salvager,
            sea_hag,
            treasure_map
    };

    const char *complete_name_list[27] = {"curse",
            "estate",
            "duchy",
            "province",
            "copper",
            "silver",
            "gold",
            "adventurer",
            "council_room",
            "feast",
            "gardens",
            "mine",
            "remodel",
            "smithy",
            "village",
            "baron",
            "great_hall",
            "minion",
            "steward",
            "tribute",
            "ambassador",
            "cutpurse",
            "embargo",
            "outpost",
            "salvager",
            "sea_hag",
            "treasure_map"
    };

    int cost[27] =  {0, 2, 5 ,8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};
    struct gameState G, testG;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);
    //Gets the current cost of a card using a switch statement
    //--check all card values
    //--check to make sure cards have not increased in game state after calling function
    //--check all game state variables after calling function

    // ----------- TEST 1: Check if game states are changed--------------
    printf("==TEST 1: check if calling function changes game state\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    getCost(smithy);
    compareGameState(&G, &testG);

    // ----------- TEST 2: Check if card values match--------------
    printf("==TEST 2: Check if card values match with hardcoded referenced via web\n");
    for(i = 0; i < 27; i = i + 1){
        int costTemp = getCost(complete_cost_list[i]);
        ASSERT(costTemp, cost[i]);
        printf("Cost of %s = %d, expected = %d\n", complete_name_list[i], costTemp, complete_cost_list[i]);
    }
    // ----------- TEST 3: Run tests player 1 check state of game--------------
    printf("\n==TEST 3: Check if player1 is unaffected STATE OF GAME\n");
    ASSERT(testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    printf("PLAYER1 hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
    ASSERT(testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    printf("PLAYER1 discard count = %d expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
    ASSERT(testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    printf("PLAYER1 deck count = %d expected = %d\n\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
    
    // ----------- TEST 4: Run tests player 2 check state of game--------------
    printf("==TEST 4: Check if player2 is unaffected STATE OF GAME\n");
    ASSERT(testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    printf("PLAYER2 hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    ASSERT(testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
    printf("PLAYER2 discard count = %d expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
    ASSERT(testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
    printf("PLAYER2 deck count = %d expected = %d\n\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);

    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTFUNCTION);
    return 0;
}