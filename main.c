//this was created by: Paulo
//it's totally free to use
//Github: Paulo-Henrique-Silva

//in this version the game works, but there's a bug that the game does not finish when the body is complete
//and the word always reset

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *pWords; //this will contain the words

char words[][35] = {"HANGMAN GAME"}; //this is temporary

void refreshHanged(int wrongGuesses);
void refreshWord(char letter);
char isValid_letter(char letter); 
int isThere_theLetter(char letter);
//fuctions prototypes

int main()
{
    char letter = ' ';
    int wrongGuesses = 0;

    while(wrongGuesses <= 6)
    {
        refreshHanged(wrongGuesses);
        refreshWord(letter); 

        printf("\n\nType a Letter: ");
        scanf(" %c", &letter); 
        letter = isValid_letter(letter); 

        if(isThere_theLetter(letter))
            printf("Right guess! :)");
        else
        {
            printf("Wrong Guess :/");
            wrongGuesses++;
        }

        getch();
    } 

   // getch(); //stops before closes it
    return 0;
}

void refreshHanged(int wrongGuesses)
{
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
            printf("\n\t\t\t\t\t|        O");
            printf("\n\t\t\t\t\t|       /|\\");
            printf("\n\t\t\t\t\t|       / \\");
            printf("\n\t\t\t\t\t|           ");
            printf("\n\t\t\t\t\t|__________");
            break;
    }
}
//this will refresh for each user wrong guess

void refreshWord(char letter)
{
    int i;
    printf("\n\n\t\t");

    for(i = 0; i < strlen(words[0]); i++)
    {
        if(words[0][i] == letter && letter != ' ')
            printf(" %c ", words[0][i]);
        else if(words[0][i] == ' ')
            printf(" - ");
        else
            printf(" _ ");
    }
}
//refresh the word for each attempt

char isValid_letter(char letter)
{
    letter = toupper(letter); //lower case to upper case
    
    while(letter < 'A' || letter > 'Z')
    {
        printf("\nInvalid Input. Type a LETTER: ");
        scanf(" %c", &letter);
        letter = toupper(letter);
    } //continues to ask until is an alphabet char

    return letter;
}

int isThere_theLetter(char letter)
{
    for(int i = 0; i < strlen(words[0]); i++)
    {
        if(letter == words[0][i])
            return 1; //if it has the letter, returns TRUE
    }

    return 0;
}
