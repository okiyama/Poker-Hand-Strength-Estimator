/*
 * Represents a deck of cards. Allows dealing from the deck as well as creating
 * decks.
 * Author: Julian Jocque
 * Date 6/3/14
 *
 */

#include "deck.h"
#include "card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Gets the size of a given deck.
//Works by counting until it finds a NULL_CARD.
int getDeckSize(char* deck)
{
    int size = 0;
    while(deck[size] != NULL_CARD) {
        size++;
    }
    return size;
}

//Creates a deck in new deck order
char* createOrderedDeck()
{
    char* deck = malloc(DECK_SIZE * sizeof(char));
    for(int i = 0; i < DECK_SIZE; i++) {
        deck[i] = i;
    }
    deck[DECK_SIZE] = NULL_CARD;
    return deck;
}

//Creates a deck in a random order
char* createRandDeck();

//Removes card at the given index into the deck
//Returns resulting deck
char* removeCard(char* deck, int position);

//Helper function, given a deck, the size of the deck and a position, 
//shifts all cards to the right of the given position over 1. 
//Sets the last card to be NULL_CARD.
void shiftLeft(char* deck, int position, int size)
{
    for(int i = position; i < size; i++) {
        deck[i] = deck[i+1];
    }
    deck[size] = NULL_CARD;
}

//Deals a random card from the deck
char dealRandomCard(char* deck)
{
    int size = getDeckSize(deck);
    //need to test if that works as expected
    int pos = rand() % size;
    char card = deck[pos];
    shiftLeft(deck, pos, size);
    return card;
}

//Deals top card of the deck
char dealCard(char* deck);

//Returns a copy of the given deck with the given deck size
char* getDeckCopy(char* deck, int size)
{
    char* newDeck = malloc((size + 1) * sizeof(char));
    if(newDeck == NULL)
    {
        printf("Memory allocation error, exiting!\n");
        exit(1);
    }
    memcpy(newDeck, deck, (size + 1) * sizeof(char));
    return newDeck;
}

//Prints out the deck
void printDeck(char* deck)
{
    int size = getDeckSize(deck);
    printf("Printing deck\n");
    for(int i = 0; i < size; i++) {
        printCard(deck[i]);
    }
}
