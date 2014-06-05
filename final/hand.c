/*
 * Represents a poker hand. Used also for testing two poker hands against each other.
 * Author: Julian Jocque
 * Date: 6/3/14
 *
 */

#include "card.h"
#include "hand.h"
#include <stdio.h>

//Gets a random hand of size out of the given deck with the given hand size
//Removes the cards from the deck
char* getRandHand(char* deck, int size)
{
    char* hand = malloc(size * sizeof(char));
    for(int i = 0; i < size; i++) {
        hand[i] = dealRandomCard(deck);
    }
    return hand;
}

//Gets the values of the given hand with the given size as an array of values
int* getvalues(char* hand, int size)
{
    int* values = malloc(size * sizeof(int));
    for(int i = 0; i < size; i++) {
        values[i] = getValue(hand[i]);
    }
    return values;
}

//Gets the suits of the given hand with the given size as an array of suits
int* getvalues(char* hand, int size)
{
    int* suits = malloc(size * sizeof(int));
    for(int i = 0; i < size; i++) {
        suits[i] = getSuit(hand[i]);
    }
    return suit;
}

//Returns the rank of the given hand.
//Assumes 5 card hand and standard poker rules.
//Assumes cards are not repeated.
//Ranks are:
//  0 - high card
//  1 - one pair
//  2 - two pair
//  3 - three of a kind
//  4 - straight
//  5 - flush
//  6 - full house
//  7 - four of a kind
//  8 - straight flush
int getHandRank(card* hand)
{
    int* values = getValues(hand, HAND_SIZE);
    int* suits = getSuits(hand, HAND_SIZE);
}

//Returns which hand wins out of two given hands.
//-1 if the first hand wins, 0 if tie, 1 if second hand wins
//Makes the hard assumption that the hands are 5 cards each with no cards
//repeated among the two hands.
int testHands(char* hand1, char* hand2)
{
    int hand1Rank = getHandRank(hand1);
    int hand2Rank = getHandRank(hand2);
}

//Prints out a hand
void printHand(char* hand, int size)
{
    printf("Hand contains:\n");
    for(int i = 0; i < size; i++) {
        printCard(hand[i]);
    }
    printf("\n");
}
