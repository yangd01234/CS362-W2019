/*
Author: Derek Yang
Program: unittest3.c
Description:
 The following test will go through unittesting for
 the whoseTurn() function.  The template was taken from the
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
#define TESTFUNCTION "whoseTurn()"


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
    int currTurn;
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
    //returns integer of whose turn it is right now
    //--Start game and get turn
    //--check if any other factors are modified
    //--Increment game state turn by 1
    //--Set game state turn to 10000
    //--Set game state turn to -1

    // ----------- TEST 1: Check if game states are changed--------------
    printf("\n==TEST 1: check if calling function changes game state\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    // ----------- Get current turn --------------
    currTurn = whoseTurn(&testG);
    // ----------- Check if game state has changed --------------
    compareGameState(&G, &testG);

    printf("\n==TEST 2: Check if turn is current player's\n");
    ASSERT(thisPlayer, currTurn);
    printf("Current turn = %d expected = %d\n", currTurn, thisPlayer);

    // ----------- TEST 3: Change to player 2 turn --------------
    printf("\n==TEST 3: Check if turn is player 2 turn\n");
    testG.whoseTurn = nextPlayer;
    currTurn = whoseTurn(&testG);
    ASSERT(nextPlayer, currTurn);
    printf("Current turn = %d expected = %d\n", currTurn, nextPlayer);

    // ----------- TEST 4: Change to player 10,000 turn --------------
    printf("\n==TEST 3: Check if turn is player 2 turn\n");
    testG.whoseTurn = 10000;
    currTurn = whoseTurn(&testG);
    ASSERT(10000, currTurn);
    printf("Current turn = %d expected = %d\n", currTurn, 10000);


    // ----------- TEST 4: Change to player  -1 turn --------------
    printf("\n==TEST 3: Check if turn is player -1 turn\n");
    testG.whoseTurn = -1;
    currTurn = whoseTurn(&testG);
    ASSERT(-1, currTurn);
    printf("Current turn = %d expected = %d\n", currTurn, -1);


    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTFUNCTION);
    return 0;
}