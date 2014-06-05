/*
 * Header for a poker hand.
 * Author: Julian Jocque
 * Date: 6/3/14
 *
 */

#define HAND_SIZE 5

//Gets a random hand of size out of the given deck with the given hand size
//Removes the cards from the deck
char* getRandHand(char* deck, int size);

//Returns which hand wins out of two given hands.
//-1 if the first hand wins, 0 if tie, 1 if second hand wins
int testHands(char* hand1, char* hand2);

//Prints out a hand in an attractive way
void printHand(char* hand, int size);

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
int getHandRank(char* hand);
