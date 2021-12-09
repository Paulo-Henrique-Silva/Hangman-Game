//this was created by: Paulo
//it's totally free to use
//Github: Paulo-Henrique-Silva

//in this version, the user can make one guess and the hanged man's draws are finished, but not working

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *pWords; //this will contain the words

char words[][35] = {"HANGMAN GAME"}; //this is temporary

void refreshHanged();
void refreshWord(char letter);
char isValid_letter(char letter); 
int isThere_theLetter(char letter);
//fuctions prototypes

int main()
{
    char letter = ' ';
    //refreshHanged();
    refreshWord(letter); 

    printf("\n\nType a Letter: ");
    scanf(" %c", &letter); 

    letter = isValid_letter(letter); 

    if(isThere_theLetter(letter))
        printf("Right guess!\n\n");
    else
        printf("Wrong Guess :/\n\n");

    refreshWord(letter); 

    getch(); //stops before closes it
    return 0;
}

void refreshHanged()
{
    for(int i = 0; i < 7; i++)
    {
        switch(i)
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
        getch();
    }
}
//this will refresh for each user right guess

void refreshWord(char letter)
{
    int i;

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
