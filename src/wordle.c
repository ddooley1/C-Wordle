#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "../inc/wordle.h"

//
// Created by damon on 2023-04-08.
//

// Text color and reset functions
void yellow()
{
    printf("\033[0;33m");
}

void green()
{
    printf("\033[0;32m");
}

void resetText()
{
    printf("\033[0m");
}

char readFile(char * inFileName, char * outFileName, FILE * inFilePath, FILE * outFilePath)
{
    struct Table wordleTable;

    // Scans textfile for word length and number of guesses
    int wordSize = 0;
    int numOfGuesses = 0;

    fscanf(inFilePath, "%i %i", &wordSize, &numOfGuesses);

    // Scans textfile for the word to guess
    char wordToGuess[wordSize];
    fscanf(inFilePath, "%s", wordToGuess);

    // Copies our values to our wordletable struct
    strcpy(wordleTable.wordToGuess, wordToGuess);
    wordleTable.wordSize = wordSize;
    wordleTable.numOfGuesses = numOfGuesses;

    runWordleGame(inFilePath, outFilePath, &wordleTable, outFileName);

    return 0;
}

void writeFile(FILE* outFilePath, char tableArray[], char **prevGuesses, char endMessage[], struct Table* wordleTable)
{
    // Writes end msg
    fprintf(outFilePath, "%s\n", endMessage);

    // Writes all user guesses
    for (int l = 0; l < wordleTable->numOfGuesses ; l++)
    {
        // loop to write out word in prevGuesses array
        for (int k = 0; k < wordleTable->wordSize; k++)
        {
            fprintf(outFilePath, "%c ", prevGuesses[l][k]);
        }
        fprintf(outFilePath,"\n");
    }

    // Close remaining file stream & free table array
    fclose(outFilePath);
    free(prevGuesses);
    free(tableArray);
    exit(0);
}

void runWordleGame(FILE * inFilePath, FILE * outFilePath, struct Table * wordleTable, char * outFileName)
{
    // Defines our user input and table we use to run the game.
    // Table is dynamically sized by our wordSize value from our textfile
    int wordSize = wordleTable->wordSize;
    int tableLength = wordleTable->numOfGuesses;

    char userGuess[MAXCOUNT];

    char endMessage;

    int timesToPrint = 0;
    int arrayCounter = 0;

    char *tableArray = malloc(sizeof(int) * wordleTable->wordSize);

    char ** prevGuesses = malloc(tableLength * sizeof(char *));; // allocates memory for columns
    for (int i = 0; i < tableLength; i++)
    {
        prevGuesses[i] = malloc(wordSize * sizeof(char)); // allocates memory for rows
    }

    bool firstLoop = true; // Boolean flag that determines if the loop has already been run once. Used to print additional guesses after a user has made their guess

    printf("Current game state:\n");
    printf(" ");

    // Nested for loop to run the game
    for (int i = 0; i < tableLength + 2; i++)
    {
        if (firstLoop == false)
        {
            arrayCounter = 0;
            timesToPrint++;
            for (int l = 0; l < timesToPrint; l++)
            {
                printf("\n");
                // loop to print out word in prevGuesses array
                for (int k = 0; k < wordSize; k++)
                {
                    // Color checking, checks if letter is in the same position as the word trying to be guessed
                    // Prints the char as green if true, indicating a correct guess
                    if (prevGuesses[arrayCounter][k] == wordleTable->wordToGuess[k])
                    {
                        green();
                        printf("%c", prevGuesses[arrayCounter][k]);
                        printf(" ");
                        resetText();
                        continue;
                    }
                    else
                    {
                        // Checks and see if any letters in the user guess exist in the array at any other positions
                        // Prints the char as yellow if true, indicating the letter is in that word but at a different position
                        bool found = false;
                        for (int j = 0; j < wordSize; j++)
                        {
                            if (prevGuesses[arrayCounter][k] == wordleTable->wordToGuess[j] && i != j)
                            {
                                found = true;
                                break;
                            }
                        }
                        if (found == true)
                        {
                            yellow();
                            printf("%c", prevGuesses[arrayCounter][k]);
                            printf(" ");
                            resetText();
                        }
                        else
                        {
                            printf("%c", prevGuesses[arrayCounter][k]);
                            printf(" ");
                        }
                    }
                }
                arrayCounter++;
            }
        }
        // Prints remainder of underscores for table
        for (int j = 0; j < tableLength; j++) {
            printf("\n");
            for (int k = 0; k < wordSize; k++) {
                // Prints the table array according to the current size of 'j'
                tableArray[j] = '_';
                printf("%c ", tableArray[j]);
            }
        }

        // Win condition
        if (strcmp(userGuess, wordleTable->wordToGuess) == 0)
        {
            printf("\n");
            printf("YOU WIN!!!\n");
            printf("The game result was written to the %s file.",outFileName);

            char endMessage[] = "The solution was found.";

            // Closes the input file path
            fclose(inFilePath);

            writeFile(outFilePath, tableArray, prevGuesses, endMessage, wordleTable);
        }

        // User input & invalid input handling
        int h = 0;
        while (h < 1)
        {
            printf("\nPlease enter a %i letter word:", wordleTable->wordSize);
            scanf("%s", userGuess);
            if (!isalpha(userGuess[i]) || strlen(userGuess) > wordSize || strlen(userGuess) < wordSize)
            {
                printf("Sorry, but you can only enter %i-letter words.\n", wordSize);
                h = 0;
                continue; // Runs loop until valid input is achieved
            }
            h = 1; // sets l to 1 to exit loop
        }

        // Converts user input to uppercase
        for (int j = 0; j < wordSize; j++) {
            userGuess[j] = toupper(userGuess[j]);

            // Stores the guess in an array to call from during the next iteration of the loop
            prevGuesses[arrayCounter][j] = userGuess[j];
        }

        // Decrements the table length by one & resets the 'i' value to 0
        tableLength = tableLength - 1;
        i = 0;

        // Sets a flag that enables printing the prevGuesses array on the next iteration of the loop
        firstLoop = false;

        // Prints out the entire table once the game has concluded. More or less using the same loop as before to check
        // if our guesses were correct during the game
        if (i == tableLength)
        {
            // resets the array counter to 0 for use within the loop
            arrayCounter = 0;

            // increments the amount of times a row will be printed on the table
            timesToPrint++;
            for (int l = 0; l < timesToPrint ; l++)
            {
                printf("\n");

                // loop to print out word in prevGuesses array
                for (int k = 0; k < wordSize; k++)
                {
                    // Color checking
                    if (prevGuesses[arrayCounter][k] == wordleTable->wordToGuess[k])
                    {
                        green();
                        printf("%c", prevGuesses[arrayCounter][k]);
                        printf(" ");
                        resetText();
                        continue;
                    }
                    else
                    {
                        // Checks and see if any letters in the user guess exist in the array at any other positions
                        // Prints the char as yellow if true, indicating the letter is in that word but at a different position
                        bool found = false;
                        for (int j = 0; j < wordSize; j++)
                        {
                            if (prevGuesses[arrayCounter][k] == wordleTable->wordToGuess[j] && l != j)
                            {
                                found = true;
                                break;
                            }
                        }
                        if (found == true)
                        {
                            yellow();
                            printf("%c", prevGuesses[arrayCounter][k]);
                            printf(" ");
                            resetText();
                        }
                        else
                        {
                            printf("%c", prevGuesses[arrayCounter][k]);
                            printf(" ");
                        }
                    }
                }
                arrayCounter++;
            }
            printf("\n");

            // Win Condition
            if (strcmp(userGuess, wordleTable->wordToGuess) == 0)
            {
                printf("\n");
                printf("YOU WIN!!!\n");
                printf("The game result was written to the %s file.",outFileName);

                char endMessage[] = "The solution was found.";

                // Closes the input file path
                fclose(inFilePath);

                writeFile(outFilePath, tableArray, prevGuesses, endMessage, wordleTable);
            }

            // Losing Condition
            else
            {
                printf("\n");
                printf("YOU LOSE!!!\n");
                printf("The game result was written to the %s file.",outFileName);

                char endMessage[] = "The solution was not found.";

                // Closes the input file path
                fclose(inFilePath);

                writeFile(outFilePath, tableArray, prevGuesses, endMessage, wordleTable);
            }
        }
    }
}
