//
// Created by damon on 2023-04-08.
//

#ifndef ASSIGN5_WORDLE_H
#define ASSIGN5_WORDLE_H

#define MAXCOUNT 256

struct Table
{
    int numOfGuesses;
    int wordSize;
    char wordToGuess[MAXCOUNT];
};

void yellow();
void green();
void resetText();

char readFile(char * inFileName, char * outFileName, FILE * inFilePath, FILE * outFilePath);
void writeFile(FILE * outFilePath, char tableArray[], char **prevGuesses, char endMessage[], struct Table * wordleTable);

void runWordleGame(FILE * inFilePath, FILE * outFilePath, struct Table * wordleTable, char * outFileName);

#endif //ASSIGN5_WORDLE_H
