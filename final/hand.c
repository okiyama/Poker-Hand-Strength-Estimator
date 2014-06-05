/*
 * Represents a poker hand. Used also for testing two poker hands against each other.
 * Author: Julian Jocque
 * Date: 6/3/14
 *
 */

#include "card.h"
#include "hand.h"
#include "deck.h"
#include <stdio.h>
#include <stdlib.h>

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
int* getValues(char* hand, int size)
{
    int* values = malloc(size * sizeof(int));
    for(int i = 0; i < size; i++) {
        values[i] = getValue(hand[i]);
    }
    return values;
}

//Gets the suits of the given hand with the given size as an array of suits
int* getSuits(char* hand, int size)
{
    int* suits = malloc(size * sizeof(int));
    for(int i = 0; i < size; i++) {
        suits[i] = getSuit(hand[i]);
    }
    return suits;
}

//Borrowed from here: http://www.anyexample.com/programming/c/qsort__sorting_array_of_strings__integers_and_structs.xml
/* qsort int comparison function */ 
int int_cmp(const void *a, const void *b) 
{ 
    const int *ia = (const int *)a; // casting pointer types 
    const int *ib = (const int *)b;
    return *ia  - *ib; 
} 

//Returns -1 if this hand doesn't have a three of a kind, otherwise
//returns the card value of the three of a kind.
int getThreeOfAKind(int* sortedValues, int handSize)
{
    if(sortedValues[0] == sortedValues[1] && sortedValues[2] == sortedValues[3] &&
            sortedValues[1] == sortedValues[2]) {
        return sortedValues[0];
    }
    else if((sortedValues[1] == sortedValues[2] && 
                sortedValues[3] == sortedValues[4] && 
                sortedValues[2] == sortedValues[3])) {
        return sortedValues[1];
    }
    return -1;
}

//Returns -1 if this hand doesn't have a four of a kind, otherwise
//returns the card value of the four of a kind.
//
//TODO: This is three of a kind! Make 4 of a kind!!
int getFourOfAKind(int* sortedValues, int handSize)
{
    if(sortedValues[0] == sortedValues[1] && sortedValues[2] == sortedValues[3] &&
            sortedValues[1] == sortedValues[2]) {
        return sortedValues[0];
    }
    else if((sortedValues[1] == sortedValues[2] && 
                sortedValues[3] == sortedValues[4] && 
                sortedValues[2] == sortedValues[3])) {
        return sortedValues[1];
    }
    return -1;
}

//Returns -1 if this hand doesn't have a straight, otherwise
//returns the card value of the highest card in the straight.
int getStraight(int* sortedValues, int handSize)
{
    for(int i = 0; i < handSize; i++) {
        if(sortedValues[i + 1] - sortedValues[i] != 1) {
            return -1;
        }
    }
    return sortedValues[handSize - 1];
}


//Returns -1 if this hand doesn't have a flush, otherwise
//returns the card value of the highest card in the flush.
int getFlush(int* suits, int* sortedValues, int handSize)
{
    for(int i = 0; i < handSize; i++) {
        if(suits[i] != suits[i+1]) {
            return -1;
        }
    }
    return sortedValues[handSize - 1];
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
int getHandRank(char* hand)
{
    int* sortedValues = getValues(hand, HAND_SIZE);
    qsort(sortedValues, HAND_SIZE, sizeof(char), int_cmp);

    int* suits = getSuits(hand, HAND_SIZE);

    int hasFourOfAKind = getFourOfAKind(sortedValues, HAND_SIZE);
    //Immediately return 7
    int hasStraight = getStraight(sortedValues, HAND_SIZE);
    int hasFlush = getFlush(suits, sortedValues, HAND_SIZE);
    //Now, we can return 8 if both straight and flush were there,
    //
    int hasThreeOfAKind = getThreeOfAKind(sortedValues, HAND_SIZE);
    //If no 3 of a kind, and we have flush, return 5
    //if no 3 of a kind and we have straight, return 4
    int numPairs = getNumPairs(sortedValues, HAND_SIZE);
    //if we have 3 of a kind and numPairs == 1, return 3
    //else if we have 3 of a kind and numPairs == 2, return 6
    //if numPairs == 2, return 2
    //elif numPairs == 1, return 1
    //else return 0


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
