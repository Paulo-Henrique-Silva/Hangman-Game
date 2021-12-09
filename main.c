//this was created by: Paulo
//it's totally free to use
//Github: Paulo-Henrique-Silva

//a simple hangman in ASCII

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

FILE *pWords;

void createHanged();
//fuctions prototypes

int main()
{
    createHanged();
    getch(); //stops before closes it
    return 0;
}

void createHanged()
{
    printf("\n\t\t\t\t\t|--------|");
    printf("\n\t\t\t\t\t|        O");
    printf("\n\t\t\t\t\t|       /|\\");
    printf("\n\t\t\t\t\t|       / \\");
    printf("\n\t\t\t\t\t|           ");
    printf("\n\t\t\t\t\t|__________");
}