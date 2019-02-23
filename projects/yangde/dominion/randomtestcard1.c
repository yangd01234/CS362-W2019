/*Derek Yang
 * Random Testing Card 1
 * Template taken from Random Testing Quiz
 * Random test for the: Village Card
 * Add +1 card, +2 actions, and discard 1 card.
 * Method under test: village_card
 * Dependencies: int currentPlayer, struct gameState *state, int handPos
 * 
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <assert.h>
#include "rngs.h"

/*
int village_card(int currentPlayer, struct gameState *state, int handPos){
    //+1 Card
    drawCard(currentPlayer, state);

    //+2 Actions

    //BUG + 10 actions, making this card super over poweed
    state->numActions = state->numActions + 10;

    //discard played card from hand
    //BUG no longer have to discard played card from hand due to lazy commenting
    //discardCard(handPos, currentPlayer, state, 0);
    return 0;
}
*/
// custom asset function
void ASSERT(int a, int b){
    if (a == b) {
        printf("PASS:  ");
    } else {
        printf("FAIL:  ");
    }
}



int villageTest():
    // test a random interval of times
    // test a random number of cards in hand and deck
    // review the before and after states for Add +1 card, +2 actions, and discard 1 card, 

    // create game state and start a loop of random from 10000 to 10000
    // first test to 10000
    int numPlayers = 2; //turn to random
    int seed = 1000;    //turn to random

    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
     remodel, smithy, village, baron, great_hall};

    initializeGame(numPlayers, k, seed, &G);

    memcpy(&testG, &G, sizeof(struct gameState));
    // 
    // return number of failed tests
    // return percentage of failed tests
    return 1;


void testme()
{
    int tcCount = 0;
    char *s;
    char c;
    int state = 0;
    while (1)
    {
        tcCount++;
        c = inputChar();
        s = inputString();
        printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

        if (c == '[' && state == 0) state = 1;
        if (c == '(' && state == 1) state = 2;
        if (c == '{' && state == 2) state = 3;
        if (c == ' '&& state == 3) state = 4;
        if (c == 'a' && state == 4) state = 5;
        if (c == 'x' && state == 5) state = 6;
        if (c == '}' && state == 6) state = 7;
        if (c == ')' && state == 7) state = 8;
        if (c == ']' && state == 8) state = 9;
        if (s[0] == 'r' && s[1] == 'e'
            && s[2] == 's' && s[3] == 'e'
            && s[4] == 't' && s[5] == '\0'
            && state == 9)
        {
            printf("error ");
            exit(200);
        }
    }
}


int main(int argc, char *argv[])
{
    

    srand(time(NULL));
    villageTest();
    return 0;
}