/*
Author: Derek Yang
Program: unittest4.c
Description:
 The following test will go through unittesting for
 the handCard() function.  The template was taken from the
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
#define TESTFUNCTION "handCard()"


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
    //returns the hand position of a card in a player's hand
    //--place card in first position hand
    //--place card in last position hand
    //--place card in first position discard
    //--place card in last position discard
    //--do not place card in hand

    // ----------- TEST 1: Check if game states are changed--------------
    printf("\n==TEST 1: check if calling function changes game state\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    // ----------- Add council room to player's hand --------------
    testG.hand[thisPlayer][0] = council_room;
    handCount = handCard(0, &testG);
    compareGameState(&G, &testG);

    // ----------- TEST 2: Check if card is found in first hand position--------------
    printf("\n==TEST 2: Check if card is found in first hand position\n");
    ASSERT(handCount, 8);
    printf("Found in hand position 0 = %s expected = %s\n", complete_name_list[handCount], "council_room");

    // ----------- TEST 3: Check if card is found in 4th position--------------
    printf("\n==TEST 3: Check if card is found in MAX_HAND hand position\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    // ----------- Add council room to player's hand --------------
    testG.hand[thisPlayer][MAX_HAND] = council_room;
    handCount = handCard(MAX_HAND, &testG);
    ASSERT(handCount, 8);
    printf("Found in hand position %d = %s expected = %s\n", MAX_HAND, complete_name_list[handCount], "council_room");


    // ----------- TEST 4: Check if card is not in hand--------------
    printf("\n==TEST 4: Check if card not in hand is found\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[thisPlayer][0] = -1;
    handCount = handCard(0, &testG);
    ASSERT(handCount, -1);
    printf("Found in hand position 0 = %s expected = %s\n\n", complete_name_list[handCount], "(null)");

    // ----------- TEST 5: Run all cards to see if found in hand--------------
    printf("\n==TEST 5: Run all cards in hand pos 1 to see if found in hand-\n");
    for(i = 0; i < 27; i = i + 1){
        memcpy(&testG, &G, sizeof(struct gameState));
        testG.hand[thisPlayer][1] = complete_cost_list[i];
        int posTemp = handCard(1, &testG);
        ASSERT(posTemp, i);
        printf("found %s expected = %s\n", complete_name_list[posTemp], complete_name_list[i]);
    }

    // ----------- TEST 6: Run tests player 2 check state of game--------------
    printf("\n==TEST 6: Check if player2 is unaffected STATE OF GAME\n");
    ASSERT(testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    printf("PLAYER2 hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    ASSERT(testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
    printf("PLAYER2 discard count = %d expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
    ASSERT(testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
    printf("PLAYER2 deck count = %d expected = %d\n\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);


    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTFUNCTION);
    return 0;
}