#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../inc/wordle.h"

/*
 * NOTE: Follow this example to use ANSI colours at the terminal:
 * https://www.theurbanpenguin.com/4184-2/
 *
 * In order to get ANSI colors showing in the CLion Run Console,
 * we need to do the following routine:
 *
 * 1. Choose Help -> Edit Custom Properties from CLion menu
 * 2. Add the following line to the idea.properties file:
 *      run.processes.with.pty=false
 * 3. Restart CLion.
 *
 * Reference:
 * https://youtrack.jetbrains.com/issue/CPP-8395/Registry-setting-runprocesseswithpty-not-saved#focus=Comments-27-2499735.0-0
 *
 */

// For CMD line arguements, 1 must be -i, 2 must be the input file, 3 must be -o and 4 must be the output file

int main(int argc, char *argv[]) {

    setbuf(stdout, 0);

    char * outFileName;
    char * inFileName;

    int maxArgs = 5;

    // Error handling for command line args

    if (argc == 1)
    {
        fprintf(stderr, "Invalid number of command line arguments.");
        return 1;
    }
    else if (argc != maxArgs)
    {
        fprintf(stderr, "Invalid number of command line arguments.");
        return 1;
    }

    if (!(argc == 5 && strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-o") == 0) &&
        (argc < 5 || (strcmp(argv[1], "-o") != 0) || (strcmp(argv[3], "-i") != 0)))
    {
        fprintf(stderr, "Invalid command line argument usage.");
        return 1;
    }

    if (!strcmp (argv[1], "-i") || !strcmp (argv[3], "-i") || !strcmp (argv[2], "word1.txt") || !strcmp (argv[4], "word1.txt"))
    {
        if (!strcmp (argv[1], "-i"))
        {
            inFileName = argv[2];
            outFileName = argv[4];
        }

        if (!strcmp (argv[3], "-i"))
        {
            inFileName = argv[4];
            outFileName = argv[2];
        }
    }

    if (!strcmp (argv[1], "-i") || !strcmp (argv[3], "-i") || !strcmp (argv[2], "word2.txt") || !strcmp (argv[4], "word2.txt"))
    {
        if (!strcmp (argv[1], "-i"))
        {
            inFileName = argv[2];
            outFileName = argv[4];
        }

        if (!strcmp (argv[3], "-i"))
        {
            inFileName = argv[4];
            outFileName = argv[2];
        }
    }

    if (!strcmp (argv[1], "-i") || !strcmp (argv[3], "-i") || !strcmp (argv[2], "word3.txt") || !strcmp (argv[4], "word3.txt"))
    {
        if (!strcmp (argv[1], "-i"))
        {
            inFileName = argv[2];
            outFileName = argv[4];
        }

        if (!strcmp (argv[3], "-i"))
        {
            inFileName = argv[4];
            outFileName = argv[2];
        }
    }

    if (!strcmp (argv[1], "-i") || !strcmp (argv[3], "-i") || !strcmp (argv[2], "word4.txt") || !strcmp (argv[4], "word4.txt"))
    {
        if (!strcmp (argv[1], "-i"))
        {
            inFileName = argv[2];
            outFileName = argv[4];
        }

        if (!strcmp (argv[3], "-i"))
        {
            inFileName = argv[4];
            outFileName = argv[2];
        }
    }

    // Concatenate directory path and file name
    char* fileNameToAdd = (char*)malloc(strlen(outFileName) + strlen(outFileName) + 1);

    FILE * inFilePath;
    FILE * outFilePath;

    strcpy(fileNameToAdd, outFileName);
    strncat(fileNameToAdd, outFileName, strlen(outFileName));

    // Open input and output files
    inFilePath = fopen(inFileName, "r");
    outFilePath = fopen(outFileName, "w");

    if (inFilePath == NULL)
    {
        fprintf(stderr,"Cannot open %s for reading.", inFileName);
        return 1;
    }

    if (outFilePath == NULL)
    {
        fprintf(stderr,"Cannot open %s for writing.", outFileName);
        return 1;
    }

    free(fileNameToAdd);

    // Welcome message

    printf("Welcome to C-Wordle!!\n");

    readFile(inFileName, outFileName, inFilePath, outFilePath);

    return 0;
}
