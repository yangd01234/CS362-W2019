/*  Author: Derek Yang
    Program: unittest1.c
    Description:
    The following test will go through unittesting for
    the fullDeckCount() function.  The template was taken from the
    provided assignment template.
 check if anything else for the player was altered
 check if anything within the game state was altered otherwise
 check the number of cards in the deck
 check the number of cards in each player's hand
 check if the card was received
 check how many cards were received
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define TESTFUNCTION "fullDeckCount()"


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
    //returns the count of a specific card in a specific player's discard deck and hand.
    //--place card in first position hand
    //--place card in last position hand
    //--place card in first position discard
    //--place card in last position discard

    //check other players are unaffected
    //check if card is not in hand
    //check to make sure cards have not increased in game state after calling function
    //check all game state variables after calling function

    // ----------- TEST 1: Check if game states are changed--------------
    printf("==TEST 1: check if calling function changes game state\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    // ----------- Add council room to player's hand --------------
    testG.hand[thisPlayer][0] = council_room;
    deckCount = fullDeckCount(thisPlayer, council_room, &testG);

    compareGameState(&G, &testG);

    // ----------- TEST 2: Check if card is found in first hand position--------------
    printf("==TEST 2: Check if card is found in first hand position\n");
    ASSERT(deckCount, 1);
    printf("Found %d council_room in hand expected = %d\n", deckCount, 1);

    // ----------- TEST 3: Check if card is found in MAX_HAND position--------------
    printf("==TEST 3: Check if card is found in MAX_HAND hand position\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    // ----------- Add council room to player's hand --------------
    testG.hand[thisPlayer][MAX_HAND] = council_room;
    deckCount = fullDeckCount(thisPlayer, council_room, &testG);
    ASSERT(deckCount, 1);
    printf("Found %d council_room in hand expected = %d\n", deckCount, 1);

    // ----------- TEST 4: Check if card is found in first discard position--------------
    printf("==TEST 4: Check if card is found in first discard position\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    // ----------- Add council room to player's discard --------------
    testG.discard[thisPlayer][0] = council_room;
    deckCount = fullDeckCount(thisPlayer, council_room, &testG);
    ASSERT(deckCount, 1);
    printf("Found %d council_room in discard expected = %d\n", deckCount, 1);

    // ----------- TEST 5: Check if card is found in MAX_DECK discard position--------------
    printf("==TEST 5: Check if card is found in MAX_DECK discard position\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    // ----------- Add council room to player's discard --------------
    testG.discard[thisPlayer][MAX_DECK] = council_room;
    deckCount = fullDeckCount(thisPlayer, council_room, &testG);
    ASSERT(deckCount, 1);
    printf("Found %d council_room in discard expected = %d\n", deckCount, 1);

    // ----------- TEST 6: Check if card is not in discard--------------
    printf("==TEST 6: Check if undiscarded card is found\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    deckCount = fullDeckCount(thisPlayer, council_room, &testG);
    ASSERT(deckCount, 0);
    printf("Found %d council_room in discard expected = %d\n", deckCount, 0);


    // ----------- TEST 7: Check if card is not in hand--------------
    printf("==TEST 7: Check if card not in hand is found\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    deckCount = fullDeckCount(thisPlayer, council_room, &testG);
    ASSERT(deckCount, 0);
    printf("Found %d council_room in hand expected = %d\n", deckCount, 0);


    // ----------- Run tests player 2 check state of game--------------
    printf("==TEST 7: Check if player2 is unaffected STATE OF GAME\n");
    ASSERT(testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    printf("PLAYER2 hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
    ASSERT(testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
    printf("PLAYER2 discard count = %d expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
    ASSERT(testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
    printf("PLAYER2 deck count = %d expected = %d\n\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);


    printf("\n >>>>> Testing complete %s <<<<<\n\n", TESTFUNCTION);
    return 0;
}