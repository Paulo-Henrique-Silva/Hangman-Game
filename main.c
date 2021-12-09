//this was created by: Paulo
//it's totally free to use
//Github: Paulo-Henrique-Silva

//Now the user can't type a letter that they have typed already
//there is a bug: the word is reseting yet.

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *pWords; //this will contain the words

char word[35] = {"HANGMAN GAME"}; 

void refreshHanged(int wrongGuesses);
void refreshWord(char letter);
char isValid_letter(char letter, char rightLetters[], char wrongLetters[]); 
int isThere_theLetter(char letter);
//fuctions prototypes

int main()
{
    char letter = ' ';
    char rightLetters[26]; 
    char wrongLetters[26];
    //contais the user guesses

    int wrongGuesses = 0; 
    int rightGuesses = 0;
    
    refreshHanged(wrongGuesses);    
    refreshWord(letter); 
    //shows the word and the draw for the first time

    while(wrongGuesses < 6)
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
        system("cls"); //clean the screen

        refreshHanged(wrongGuesses);    
        refreshWord(letter); 
        //refresh for each attempt
    } 

    printf("\n\nEND GAME!");

    getch(); //stops before closes it
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
    printf("\n\n\t\t\t");

    for(i = 0; i < strlen(word); i++)
    {
        if(word[i] == letter && letter != ' ')
            printf(" %c ", word[i]);
        else if(word[i] == ' ')
            printf(" - ");
        else
            printf(" _ ");
    }
}
//refresh the word for each attempt

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

    for(i = 0; i < strlen(rightLetters); i++) //they're the same size, so it won't be a problem
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

int isThere_theLetter(char letter)
{
    for(int i = 0; i < strlen(word); i++)
    {
        if(letter == word[i])
            return 1; //if it has the letter, returns TRUE
    }

    return 0;
}
