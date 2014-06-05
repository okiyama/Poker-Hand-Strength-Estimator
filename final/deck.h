/*
 * Deck header file.
 * One oddity is that decks are defined as ending in a NULL_CARD.
 * This is to make it so that we can get the size and remove cards easily.
 *
 */

#define DECK_SIZE 52

//Gets the size of a given deck.
//Works by counting until it finds a NULL_CARD.
int getDeckSize(char* deck);

//Creates a deck in new deck order
char* createOrderedDeck();

//Creates a deck in a random order
char* createRandDeck();

//Removes card at the given index into the deck
//Returns resulting deck
char* removeCard(char* deck, int position);

//Deals a random card from the deck
char dealRandomCard(char* deck);

//Deals top card of the deck
char dealCard(char* deck);

//Returns a copy of the given deck and the deck size to copy
char* getDeckCopy(char* deck, int size);

//Prints out the deck in a pretty way
void printDeck(char* deck);
