//this was created by: Paulo
//it's totally free to use
//Github: Paulo-Henrique-Silva

//randomly select a word from file

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

FILE *pWords; //this contain the words
char word[50] = {'\0'}; 

enum menu {play = 1, exitGame};

void playGame();
void chooseA_randomWord();
void refreshHanged(int wrongGuesses);
void refreshWord(char rightLetters[]);
void showWrong_letters(char wrongLetters[]); 

char isValid_letter(char letter, char rightLetters[], char wrongLetters[]); 

int isThere_theLetter(char letter);
int isVictory(char rightLetters[]);
//functions prototypes

int main()
{
    int operation = 0;

    while(operation != exitGame)
    {
        system("cls");
        printf("\t\t\t\tHANGMAN GAME\n");
        printf("\n\t\t\t\t[1] - Play Game");
        printf("\n\t\t\t\t[2] - Exit");
        printf("\n\nType your operation: ");
        scanf("%d", &operation); 

        switch(operation)
        {
            case play:
                playGame();
                break;
            case exitGame:
                printf("\nExiting...");
                break;
            default:
                printf("\nInvalid Input!");
                break;
        }

        getch(); //stops before closes it
    }

    return 0;
}

void playGame() 
{
    char letter = '\0';
    char rightLetters[26] = {'\0'}; 
    char wrongLetters[26] = {'\0'};

    int wrongGuesses = 0; 
    int rightGuesses = 0;

    system("cls");
    chooseA_randomWord();
    
    refreshHanged(wrongGuesses);    
    refreshWord(rightLetters); 
    showWrong_letters(wrongLetters);
    //shows the word and the draw for the first time

    while(wrongGuesses < 6 && isVictory(rightLetters) == 0)
    {
        printf("\n\nType a Letter: ");
        scanf(" %c", &letter); 
        letter = isValid_letter(letter, rightLetters, wrongLetters); 

        if(isThere_theLetter(letter))
        {
            printf("Right guess! :)");
            rightLetters[rightGuesses] = letter;
            rightGuesses++;
        }
        else
        {
            printf("Wrong Guess :/");
            wrongLetters[wrongGuesses] = letter;
            wrongGuesses++;
        }

        getch(); //stops before clean
        system("cls"); //cleans the screen

        refreshHanged(wrongGuesses);    
        refreshWord(rightLetters); 
        showWrong_letters(wrongLetters);
        //refresh for each attempt
    } 

    printf("\n\nEND GAME!");

    if(isVictory(rightLetters))
        printf("\nVICTORY! :)");
    else
        printf("\nYOU LOST :(");
    
    printf("\nAnswer = %s", word);
}

void chooseA_randomWord()
{
    char Fpath[10] = "words.txt";
    int randomLine, i; 

    if(fopen(Fpath, "r") == NULL) 
    {
        pWords = fopen(Fpath, "w");

        fputs("CLICK\n", pWords);
        fputs("HARRY POTTER AND THE PHILOSOPHERS STONE\n", pWords);
        fputs("THE LAST OF US\n", pWords);
        fputs("INDIANA JONES AND THE LAST CRUSADE\n", pWords);
        fputs("BRAZIL\n", pWords);
        fputs("THE GODFATHER\n", pWords);
        fputs("ASSASSINS CREED\n", pWords);
        fputs("GRAND THEFT AUTO SAN ANDREAS\n", pWords);
        fputs("UNITED STATES OF AMERICA\n", pWords);
        fputs("MEXICO\n", pWords);

        fclose(pWords); //put some words in a file
    }

    srand(time(0));
    randomLine = rand() % 11; //select a random line (0 - 10)

    pWords = fopen(Fpath, "r");
    for(i = 0; i <= randomLine; i++)
            fgets(word, 50, pWords); //gets the word from the random line
    fclose(pWords);

    word[strlen(word) - 1] = '\0'; //remove the \n char
}

void refreshHanged(int wrongGuesses)
{
    printf("\t\t\t\t\tHANGMAN GAME");
    printf("\n\t\t------------------------------------------------------------");

    switch(wrongGuesses)
    {
        case 0:
            printf("\n\t\t\t\t\t|--------|");
            printf("\n\t\t\t\t\t|         ");
            printf("\n\t\t\t\t\t|           ");
            printf("\n\t\t\t\t\t|           ");
            printf("\n\t\t\t\t\t|           ");
            printf("\n\t\t\t\t\t|__________");
            break;
        case 1:
            printf("\n\t\t\t\t\t|--------|");
            printf("\n\t\t\t\t\t|        O");
            printf("\n\t\t\t\t\t|           ");
            printf("\n\t\t\t\t\t|           ");
            printf("\n\t\t\t\t\t|           ");
            printf("\n\t\t\t\t\t|__________");
            break;
        case 2:
            printf("\n\t\t\t\t\t|--------|");
            printf("\n\t\t\t\t\t|        O");
            printf("\n\t\t\t\t\t|        |  ");
            printf("\n\t\t\t\t\t|           ");
            printf("\n\t\t\t\t\t|           ");
            printf("\n\t\t\t\t\t|__________");
            break;
        case 3:
            printf("\n\t\t\t\t\t|--------|");
            printf("\n\t\t\t\t\t|        O");
            printf("\n\t\t\t\t\t|       /|  ");
            printf("\n\t\t\t\t\t|           ");
            printf("\n\t\t\t\t\t|           ");
            printf("\n\t\t\t\t\t|__________");
            break;
        case 4:
            printf("\n\t\t\t\t\t|--------|");
            printf("\n\t\t\t\t\t|        O");
            printf("\n\t\t\t\t\t|       /|\\");
            printf("\n\t\t\t\t\t|           ");
            printf("\n\t\t\t\t\t|           ");
            printf("\n\t\t\t\t\t|__________");
            break;
        case 5:
            printf("\n\t\t\t\t\t|--------|");
            printf("\n\t\t\t\t\t|        O");
            printf("\n\t\t\t\t\t|       /|\\");
            printf("\n\t\t\t\t\t|       /   ");
            printf("\n\t\t\t\t\t|           ");
            printf("\n\t\t\t\t\t|__________");
            break;
        case 6:
            printf("\n\t\t\t\t\t|--------|");
            printf("\n\t\t\t\t\t|      (;-;)");
            printf("\n\t\t\t\t\t|       /|\\");
            printf("\n\t\t\t\t\t|       / \\");
            printf("\n\t\t\t\t\t|           ");
            printf("\n\t\t\t\t\t|__________");
            break;
    }

    printf("\n\t\t------------------------------------------------------------");
}
//this will refresh for each user wrong guess

void refreshWord(char rightLetters[])
{
    int i, j;
    printf("\n\n");

    for(i = 0; i < strlen(word); i++)
    {
        for(j = 0; j < strlen(rightLetters); j++)
        {
            if(word[i] == rightLetters[j])
            {
                printf(" %c ", word[i]);
                break;
            }
            //checks each right letter to print
        }

        if(word[i] == ' ')
            printf(" - ");
        else if(word[i] != rightLetters[j])
            printf(" _ ");
        //if the letter is not in rightLetters array, it means that it was not discovered yet
        //then, it'll be placed as a empty space
    }
}
//refresh the word for each attempt

void showWrong_letters(char wrongLetters[])
{
    printf("\n\nWrong Letters: "); 

    for(int i = 0; i < strlen(wrongLetters); i++)
    {
        if(i == 0)
            printf("%c", wrongLetters[i]);
        else
            printf(" - %c", wrongLetters[i]);
    } //to show like: A - B - C...
}

char isValid_letter(char letter, char rightLetters[], char wrongLetters[])
{
    int i;
    letter = toupper(letter); //lower case to upper case
    
    while(letter < 'A' || letter > 'Z')
    {
        printf("\nInvalid Input. Type a new letter: ");
        scanf(" %c", &letter);
        letter = toupper(letter);
    } //continues to ask until is an alphabet char

    for(i = 0; i < 26; i++)
    {
        if(letter == rightLetters[i] || letter == wrongLetters[i]) //if the letter was already used
        {
            printf("\nThis letter was already taken. Type again: ");
            scanf(" %c", &letter);
            letter = toupper(letter);
            i = -1; //this will reset the loop
        }
    }

    return letter; 
}

int isVictory(char rightLetters[])
{
    //the logic is similar to refreshWord()
    int i, j;

    for(i = 0; i < strlen(word); i++)
    {
        for(j = 0; j < strlen(rightLetters); j++)
        {
            if(word[i] == rightLetters[j])
                break;
        }

        if(word[i] != rightLetters[j] && word[i] != ' ')
            return 0; 
            //if the letter is not in rightLetters array, it'll return FALSE
            //it means that the game it's not over 
    }

    return 1;
}

int isThere_theLetter(char letter)
{
    for(int i = 0; i < strlen(word); i++)
    {
        if(letter == word[i])
            return 1; //if it has the letter, returns TRUE
    }

    return 0;
}
