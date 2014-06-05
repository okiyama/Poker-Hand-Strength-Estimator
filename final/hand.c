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

//Returns an array where the indices are the num of cards in the hand
//for each card value
int* getNumOfValuesArray(int* sortedValues, int handSize)
{
    int* numInValues = calloc(NUM_VALUES, sizeof(int));
    for(int i = 0; i < handSize; i++) {
        numInValues[sortedValues[i]]++;
    }
    return numInValues;
}

//Borrowed from here: http://rosettacode.org/wiki/Sort_an_integer_array#C
int intcmp(const void *aa, const void *bb)
{
    const int *a = aa, *b = bb;
    return (*a < *b) ? -1 : (*a > *b);
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

//Returns the number of pairs in a hand while setting the tieBreaker
//value to the value of the highest pair in the hand.
//If one of the pairs is a three of a kind, tieBreaker is always set to the value
//of the three of a kind.
int getNumPairs(int* sortedValues, int* tieBreaker, int handSize)
{
    int* numInValues = getNumOfValuesArray(sortedValues, handSize);
    int numPairs = 0;
    for(int i = 0; i < NUM_VALUES; i++) {
        if(numInValues[i] == 2) {
            numPairs++;
            *tieBreaker = i;
        }
    }
    //Although this seems silly, it's the cleanest way to correctly deal with
    //the tie breaker of full houses.
    for(int i = 0; i < NUM_VALUES; i++) {
        if(numInValues[i] == 3) {
            numPairs++;
            *tieBreaker = i;
        }
    }
    return numPairs;
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
//
//  Also sets the tieBreaker variable to the appropriate value.
//  This will be used in case the rank of two hands is equal, the tie breaker value
//  can be used to determine the true winner.
int getHandRank(char* hand, int* tieBreaker)
{
    int* sortedValues = getValues(hand, HAND_SIZE);
//    printf("unsorted[0,1,2,3,4]: %d,%d,%d,%d,%d\n", sortedValues[0], 
//        sortedValues[1], sortedValues[2], sortedValues[3], sortedValues[4]);
//    printf("just got values.\n");
    qsort(sortedValues, HAND_SIZE, sizeof(int), intcmp);
//    printf("sorted[0,1,2,3,4]: %d,%d,%d,%d,%d\n", sortedValues[0], 
//        sortedValues[1], sortedValues[2], sortedValues[3], sortedValues[4]);
//    printf("Just sorted\n");

    int* suits = getSuits(hand, HAND_SIZE);
//    printf("Just got suits\n");

    int hasFourOfAKind = getFourOfAKind(sortedValues, HAND_SIZE);
//    printf("Just got four of a kind\n");
    if(hasFourOfAKind != -1) {
        *tieBreaker = hasFourOfAKind;
        return 7;
    }
    //Immediately return 7
    int hasStraight = getStraight(sortedValues, HAND_SIZE);
//    printf("just got straight\n");
    int hasFlush = getFlush(suits, sortedValues, HAND_SIZE);
//    printf("just got flush\n");
    //Now, we can return 8 if both straight and flush were there,
    if(hasStraight != -1 && hasFlush != -1) {
        *tieBreaker = hasStraight;
        return 8;
    }
    int hasThreeOfAKind = getThreeOfAKind(sortedValues, HAND_SIZE);
//    printf("just got 3 of a kind\n");
    if(hasThreeOfAKind == -1 && hasFlush != -1) {
        *tieBreaker = hasFlush;
        return 5;
    }
    if(hasThreeOfAKind == -1 && hasStraight != -1) {
        *tieBreaker = hasStraight;
        return 4;
    }
    //If no 3 of a kind, and we have flush, return 5
    //if no 3 of a kind and we have straight, return 4
    int numPairs = getNumPairs(sortedValues, tieBreaker, HAND_SIZE);
//    printf("just got num pairs\n");
    if(hasThreeOfAKind != -1 && numPairs == 1) {
        *tieBreaker = hasThreeOfAKind;
        return 3;
    }
    if(hasThreeOfAKind != -1 && numPairs == 2) {
        *tieBreaker = hasThreeOfAKind;
        return 6;
    }
    if(numPairs == 2) {
        return 2;
    }
    if(numPairs == 1) {
        return 1;
    }
    else {
        *tieBreaker = sortedValues[HAND_SIZE-1];
        return 0;
    }
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
    int tieBreak1 = 0;
    int tieBreak2 = 0;
//    printf("Getting hand 1 rank\n");
    int hand1Rank = getHandRank(hand1, &tieBreak1);
//    printf("Getting hand 2 rank\n");
    int hand2Rank = getHandRank(hand2, &tieBreak2);
    if(hand1Rank == hand2Rank) {
        if(tieBreak1 > tieBreak2) { return -1; }
        else if(tieBreak1 < tieBreak2) { return 1; }
        else { return 0; }
    }
    else if(hand1Rank > hand2Rank) {
        return -1;
    }
    else {
        return 1;
    }
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
