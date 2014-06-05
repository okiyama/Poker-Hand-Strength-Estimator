/*
 * Main method for parallel monte carlo estimation of poker hand strength.
 * Author: Julian
 *
 */

#include "card.h"
#include "hand.h"
#include "deck.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//Tests out the functions
void testFunctions()
{
//    printf("About to created deck.\n");
    char* deck = createOrderedDeck();
//    printf("Deck is of size: %d\n", getDeckSize(deck));
//    printf("About to print deck.\n");
//    printDeck(deck);
//    printf("Now dealing one card.\n");
//    char dealt = dealRandomCard(deck);
//    printf("Deck is of size: %d\n", getDeckSize(deck));
//    printf("Dealt:\n");
//    printCard(dealt);
//    printDeck(deck);
//    char* newDeck = getDeckCopy(deck, getDeckSize(deck));
//    printf("Copied deck\n");
//    printDeck(newDeck);
    char* hand1 = getRandHand(deck, HAND_SIZE);
    char* hand2 = getRandHand(deck, HAND_SIZE);
    printHand(hand1, HAND_SIZE);
    printf("vs\n");
    printHand(hand2, HAND_SIZE);

    printf("Result is %d!\n", testHands(hand1, hand2));
}


int main(int argc, char* argv[])
{
    srand(time(NULL));
    testFunctions();
}
