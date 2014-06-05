/*
 * Card header. Defines the functions that will be present in the card 'class'.
 * Card suits are 0-3, Clubs, Diamonds, Hearts, Spades
 * Values are 0-12, 0-8 are 2-10. 9-11 is Jack, Queen, King and 12 is Ace. 
 */

//Define all of our constant values for later readability
#define CLUBS 0
#define DIAMONDS 1
#define HEARTS 2
#define SPADES 3

#define VAL_2 0
#define VAL_3 1
#define VAL_4 2
#define VAL_5 3
#define VAL_6 4
#define VAL_7 5
#define VAL_8 6
#define VAL_9 7
#define VAL_10 8
#define VAL_JACK 9
#define VAL_QUEEN 10
#define VAL_KING 11
#define VAL_ACE 12

#define NUM_SUITS 4
#define NUM_VALUES 13

#define NULL_CARD 99

//Returns the suit of the card, 0-3
int getSuit(char card);

//Returns the value of the card, 0-12
int getValue(char card);

//Generates a random card. Assumes that srand() has already been called.
char generateRandomCard();

//Creates a card with the given suit and value
char createCard(int suit, int value);

//Prints out a card in an attractive way.
void printCard(char card);
