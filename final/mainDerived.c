/*
 * Main method for parallel monte carlo estimation of poker hand strength.
 * Uses derived datatypes to send the deck and the hand at the same time as well as
 * using derived data types to send the results of a hand.
 * Author: Julian
 *
 */

#include "mpi.h"
#include "card.h"
#include "hand.h"
#include "deck.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_TESTS 5000000
#define NUM_SEC_TO_RUN 30

//Tests out the functions
void testFunctions()
{
    printf("About to created deck.\n");
    char* deck = createOrderedDeck();
    printf("Deck is of size: %d\n", getDeckSize(deck));
    printf("About to print deck.\n");
    printDeck(deck);
    printf("Now dealing one card.\n");
    char dealt = dealRandomCard(deck);
    printf("Deck is of size: %d\n", getDeckSize(deck));
    printf("Dealt:\n");
    printCard(dealt);
    printDeck(deck);
    char* newDeck = getDeckCopy(deck, getDeckSize(deck));
    printf("Copied deck\n");
    printDeck(newDeck);
    char* hand1 = getRandHand(deck, HAND_SIZE);
    char* hand2 = getRandHand(deck, HAND_SIZE);
    printHand(hand1, HAND_SIZE);
    printf("vs\n");
    printHand(hand2, HAND_SIZE);

    char highCard[HAND_SIZE] = {12,32,17,1,5};
    char onePair[HAND_SIZE] = {1,2,3,4,14};
    char twoPair[HAND_SIZE] = {1,2,3,14,15};
    char threeOfAKind[HAND_SIZE] = {1,2,3,14,27};
    char fourOfAKind[HAND_SIZE] = {1,2,14,27,40};
    char fullHouse[HAND_SIZE] = {1,14,2,15,28};
    char flush[HAND_SIZE] = {1,3,4,5,6};
    char straight[HAND_SIZE] = {1,15,3,4,5};
    char straightFlush[HAND_SIZE] = {1,2,3,4,5};
    char betterThreeOfAKind[HAND_SIZE] = {2,3,4,15,28};

    printHand(highCard, HAND_SIZE);
    printHand(onePair, HAND_SIZE);
    printf("Result is %d!\n", testHands(highCard, onePair));
    printHand(twoPair, HAND_SIZE);
    printHand(threeOfAKind, HAND_SIZE);
    printf("Result is %d!\n", testHands(twoPair, threeOfAKind));
    printHand(fourOfAKind, HAND_SIZE);
    printHand(fullHouse, HAND_SIZE);
    printf("Result is %d!\n", testHands(fourOfAKind, fullHouse));
    printHand(flush, HAND_SIZE);
    printHand(straight, HAND_SIZE);
    printf("Result is %d!\n", testHands(flush, straight));
    printHand(straightFlush, HAND_SIZE);
    printf("Result is %d!\n", testHands(straightFlush, straightFlush));
    printf("Result of two 3 of a kinds: %d\n", testHands(threeOfAKind,
                betterThreeOfAKind));


    //printf("Result is %d!\n", testHands(hand1, hand2));
}

/*
 * Builds the data type for the deck/hand datatype
 * Builds it onto the variable deckHandDatatype
 */
void buildDeckHandDatatype(char* deck, char* hand, MPI_Datatype* deckHandDatatype)
{
    int blockLengthArray[2] = {DECK_SIZE + 1, HAND_SIZE};
    MPI_Datatype typeArray[2] = {MPI_CHAR, MPI_CHAR};
    MPI_Aint deckAddr, handAddr;
    MPI_Aint displacementArray[2] = {0};

    MPI_Get_address(deck, &deckAddr);
    MPI_Get_address(hand, &handAddr);

    displacementArray[1] = handAddr - deckAddr;

    MPI_Type_create_struct(2, blockLengthArray, displacementArray, typeArray, deckHandDatatype);
    MPI_Type_commit(deckHandDatatype);
}

/*
 * Builds the data type for the results datatype
 * Builds it onto the variable resultsDatatype
 */
void buildResultsDatatype(int* numWins, int* numTies, int* numLosses, MPI_Datatype* resultsDatatype)
{
    int blockLengthArray[3] = {1, 1, 1};
    MPI_Datatype typeArray[3] = {MPI_INT, MPI_INT, MPI_INT};
    MPI_Aint winAddr, tiesAddr, lossAddr;
    MPI_Aint displacementArray[3] = {0};

    MPI_Get_address(numWins, &winAddr);
    MPI_Get_address(numTies, &tiesAddr);
    MPI_Get_address(numLosses, &lossAddr);

    displacementArray[1] = tiesAddr - winAddr;
    displacementArray[2] = lossAddr - winAddr;

    MPI_Type_create_struct(3, blockLengthArray, displacementArray, typeArray, resultsDatatype);
    MPI_Type_commit(resultsDatatype);
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
//    testFunctions();
    int myRank;           /* Process rank */
    int p;                /* Number of processes */

    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &myRank);
    MPI_Comm_size (MPI_COMM_WORLD, &p);

    double programStartTime = MPI_Wtime();
    char* masterHand = malloc(HAND_SIZE * sizeof(char));
    char* masterDeck = malloc(DECK_SIZE * sizeof(char)); 
    char* localHand = malloc(HAND_SIZE * sizeof(char));
    char* localDeck = malloc(DECK_SIZE * sizeof(char)); 
    MPI_Datatype deckHandDatatype;

    buildDeckHandDatatype(masterDeck, masterHand, &deckHandDatatype);

    //Have root node generate a deck and master hand for nodes to use
    if(myRank == 0) {
        masterDeck = createOrderedDeck();
        masterHand = getRandHand(masterDeck, HAND_SIZE);
    }

    //Broadcast out the hand and deck we are using with a derived datatype
    MPI_Bcast(masterDeck, 1, deckHandDatatype, 0, MPI_COMM_WORLD);


    int globalWins = 0;
    int globalTies = 0;
    int globalLosses = 0;
    int globalNumTests = 0;

    int localWins = 0;
    int localTies = 0;
    int localLosses = 0;
    int localNumTests = 0;
    int result = 0;
    MPI_Datatype resultsDatatype;
    buildResultsDatatype(&localWins, &localTies, &localLosses, &resultsDatatype);

    double testStartTime = MPI_Wtime();
    while((MPI_Wtime() - testStartTime) < NUM_SEC_TO_RUN) {
        //Although inefficient, this makes the simulation much more realistic
        localDeck = getDeckCopy(masterDeck, getDeckSize(masterDeck) + 1);
        localHand = getRandHand(localDeck, HAND_SIZE);

        result = testHands(masterHand, localHand);
        switch(result) {
            case -1:
                localWins++;
                break;
            case 0:
                localTies++;
                break;
            case 1:
                localLosses++;
                break;
        }
        localNumTests++;
    }
    double testEndTime = MPI_Wtime();

    //I tried to use a derived data type here, but reduce doesn't work for non-simplified data types.
    MPI_Reduce(&localWins, &globalWins, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&localLosses, &globalLosses, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&localTies, &globalTies, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&localNumTests, &globalNumTests, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(myRank == 0) {
        double programEndTime = MPI_Wtime();
        float winRate = (((float)globalWins)/((float)NUM_TESTS)) * 100.0;
        printf("All done! The master hand was:\n");
        printHand(masterHand, HAND_SIZE);
        printf("\nOut of %d tests on %d nodes, the hand won %d games, lost %d games and tied %d games.\n Which is a %f percent win rate!\n", globalNumTests, p, globalWins, globalLosses, globalTies, winRate);
        printf("The program took a total of %f seconds to run whereas the tests took %f seconds to run!\n", programEndTime - programStartTime, testEndTime - testStartTime);
    }

    MPI_Type_free(&resultsDatatype);
    MPI_Type_free(&deckHandDatatype);

    MPI_Finalize();
    return 0;
}
