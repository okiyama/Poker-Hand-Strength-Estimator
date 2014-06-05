/*
 * Represents a card in poker.
 * Used for monte carlo poker hand strength estimation.
 * Author: Julian Jocque
 * Date: 6/3/14
 *
 */

#include "card.h"
#include <stdio.h>

//Returns the suit of the card, 0-3
int getSuit(char card)
{
    return card / NUM_VALUES;
}

//Returns the value of the card, 0-12
int getValue(char card)
{
    return card % NUM_VALUES;
}

//Generates a random card. Assumes that srand() has already been called.
char generateRandomCard();

//Creates a card with the given suit and value
char createCard(int suit, int value);

//Prints the value out in a nice way
void prettyPrintValue(int value)
{
    if(value >= VAL_2 && value <= VAL_10) {
        printf("%d", value + 2);
    }
    else if(value == VAL_JACK) {
        printf("Jack");
    }
    else if(value == VAL_QUEEN) {
        printf("Queen");
    }
    else if(value == VAL_KING) {
        printf("King");
    }
    else if(value == VAL_ACE) {
        printf("Ace");
    }
    else {
        printf("Invalid card value");
    }
}

//Prints the suit out in a nice way
void prettyPrintSuit(int suit)
{
    if(suit == CLUBS) {
        printf("Clubs");
    }
    else if(suit == DIAMONDS) {
        printf("Diamonds");
    }
    else if(suit == HEARTS) {
        printf("Hearts");
    }
    else if(suit == SPADES) {
        printf("Spades");
    }
    else {
        printf("Invalid suit.");
    }
}

//Prints out a card in an attractive way.
void printCard(char card)
{
    int suit = getSuit(card);
    int value = getValue(card);
    prettyPrintValue(value);
    printf(" of ");
    prettyPrintSuit(suit);
    printf("\n");
}
