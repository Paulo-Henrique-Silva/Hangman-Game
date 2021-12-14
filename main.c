//this was created by: Paulo
//it's totally free to use
//Github: Paulo-Henrique-Silva

//adding a points System

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

FILE 
*pWords,
*pTemp_file, 
*pAccounts_names,
*pAccounts_passWords,
*pAccounts_points;

const char 
wordsF_path[] = "words.txt",
tempF_path[] = "temp.tmp", 
namesF_path[] = "names.txt",
pointsF_path[] = "points.txt",
passwordsF_path[] = "passwords.txt";

char word[50] = {'\0'}; 

struct player
{
    int points;
    char name[25], password[25];
};
struct player account;

enum menu {play = 1, howToplay, addAccount, seeAccounts, addWord, seeWords, exitGame};

void playGame();
void addA_word();
void seeWord_list();
void addA_account(); 

void chooseA_randomWord();
void checkWords_data();
int checkAccounts_data();
int logIn_anAccount(); 

void refreshHanged(int wrongGuesses);
void refreshWord(char rightLetters[]);
void showWrong_letters(char wrongLetters[]); 
void addPoints_toPlayer(int points); 

char isValid_letter(char letter, char rightLetters[], char wrongLetters[]); 

int isThere_theLetter(char letter);
int isVictory(char rightLetters[]);
int isA_validWord(char typedWord[]);
//functions prototypes

int main()
{
    int operation = 0;

    while(operation != exitGame)
    {
        system("cls");
        printf("\t\t\t\tHANGMAN GAME\n");
        printf("\n\t\t\t\t[1] - Play Game");
        printf("\n\t\t\t\t[2] - How To Play");
        printf("\n\t\t\t\t[3] - Add an account");
        printf("\n\t\t\t\t[4] - Show Accounts");
        printf("\n\t\t\t\t[5] - Add a Word");
        printf("\n\t\t\t\t[6] - Show Word List");
        printf("\n\t\t\t\t[7] - Exit");
        printf("\n\nType your operation: ");
        scanf("%d", &operation); 

        switch(operation)
        {
            case play:
                playGame();
                break;
            case howToplay:
                break;
            case addAccount:
                addA_account();
                break;
            case seeAccounts:
                break;
            case addWord:
                addA_word();
                break;
            case seeWords: 
                seeWord_list();
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
    char rightLetters[26] = {'\0'}, wrongLetters[26] = {'\0'};

    int wrongGuesses = 0, rightGuesses = 0, pointsIn_play = 6;
    
    if(logIn_anAccount() != 0)
    {
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

        pointsIn_play = pointsIn_play - wrongGuesses;

        printf("\n\nEND GAME!");

        if(isVictory(rightLetters))
        {
            printf("\nVICTORY! :)");
            printf("\nPoints gained: %d", pointsIn_play);
            addPoints_toPlayer(pointsIn_play); 
        }
        else
            printf("\nYOU LOST :(");
        
        printf("\nAnswer = %s", word);

    }
}

void addA_account()
{
    system("cls");
    printf("\t\t\t\t\tADDING ACCOUNT");
    printf("\n\t\t------------------------------------------------------------\n");

    scanf("%c"); //avoid \n

    printf("\nType a UserName to the new Account: "); 
    fgets(account.name, 25, stdin);

    printf("\nType a PassWord: "); 
    fgets(account.password, 25, stdin);

    account.points = 0; //it's a new account, then its points it will be equal 0

    checkAccounts_data();

    pAccounts_names = fopen(namesF_path, "a");
    pAccounts_passWords = fopen(passwordsF_path, "a");
    pAccounts_points = fopen(pointsF_path, "a");

    fputs(account.name, pAccounts_names);
    fputs(account.password, pAccounts_passWords);
    fprintf(pAccounts_points, "%d\n", account.points);

    fclose(pAccounts_names);
    fclose(pAccounts_passWords);
    fclose(pAccounts_points);
    
    printf("\nNew Account Sucessfully Added!");
}

void addA_word()
{
    char newWord[50] = {'\0'};
    int i = 0;

    checkWords_data();

    do
    {
        system("cls");
        printf("\t\t\t\t\tADDING A WORD");
        printf("\n\t\t------------------------------------------------------------\n");
        printf("\nType a new Word: ");

        if(i == 0)
        {
            scanf("%c"); 
            i++;
        } //this avoid fgets get '\n'

        fgets(newWord, 50, stdin);
    }
    while(isA_validWord(newWord) == 0);

    pWords = fopen(wordsF_path, "a");
    fputs(newWord, pWords);
    fclose(pWords); 

    printf("\nThe new Word was Successfully added!");
}

void seeWord_list()
{
    char wordIn_file[50]; //this will get the line
    int i = 1;

    checkWords_data();

    system("cls");

    printf("\t\t\t\t\tWORD LIST");
    printf("\n\t\t------------------------------------------------------------\n");

    pWords = fopen(wordsF_path, "r");
    while(fgets(wordIn_file, 50, pWords) != NULL) //NULL it's the end of file
    {
        printf("\t\t\t%d - %s", i, wordIn_file);
        i++;
    }
    fclose(pWords);
}

void chooseA_randomWord()
{
    int randomLine, i, amountOf_lines = 0; 
    char tempBuffer[50];

    checkWords_data();

    pWords = fopen(wordsF_path, "r");
    do 
        amountOf_lines++;
    while(fgets(tempBuffer, 50, pWords) != NULL);
    fclose(pWords);
    //checks how many lines(words) there are in the file

    srand(time(0));
    randomLine = rand() % amountOf_lines; //select a random line between 0 - amount of lines in file

    pWords = fopen(wordsF_path, "r");
    for(i = 0; i <= randomLine; i++)
            fgets(word, 50, pWords); //gets the word from the random line
    fclose(pWords);

    word[strlen(word) - 1] = '\0'; //remove the \n char
}

void checkWords_data()
{
    if(fopen(wordsF_path, "r") == NULL)
    {
        pWords = fopen(wordsF_path, "w");

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

        fclose(pWords); 
    } 
}
//if the file doesn't exist, it will create a new one with a few words.
//then the user can play the game

int checkAccounts_data()
{
    char nameIn_firstLine[25];

    if
    (
        fopen(namesF_path, "r") == NULL || 
        fopen(passwordsF_path, "r") == NULL ||
        fopen(pointsF_path, "r") == NULL
    )
    {
        pAccounts_names = fopen(namesF_path, "w");
        pAccounts_passWords = fopen(passwordsF_path, "w");
        pAccounts_points = fopen(pointsF_path, "w"); 
        //the files are connect, they don't make sense if one is missing.
        //then, they need to be recreated

        fclose(pAccounts_names);
        fclose(pAccounts_passWords);
        fclose(pAccounts_points);

        return 0;
    }

    pAccounts_names = fopen(namesF_path, "r");
    if(fgets(nameIn_firstLine, 25, pAccounts_names) == NULL)
    {
        fclose(pAccounts_names);
        return 0;
    }
    //if the first line is empty. It means that it does not have an account yet
    
    fclose(pAccounts_names);
    return 1;
}
//if it returns 1, it means there is data. Else it means that the files were deleted or are empties

int logIn_anAccount()
{
    int pointsIn_file = 0;
    char nameIn_file[25], passWord_inFile[25];

    system("cls");
    if(checkAccounts_data() == 0) //if it is missing data
    {
        printf("\nSorry, it seems it does not have an Account yet or the Files were deleted :/");
        printf("\nCreate a new Account to Play!");
        return 0;
    }

    printf("\nType your User name: "); 
    scanf("%c");
    fgets(account.name, 25, stdin);
    printf("\nType Your PassWord: ");
    fgets(account.password, 25, stdin);

    pAccounts_names = fopen(namesF_path, "r"); 
    pAccounts_passWords = fopen(passwordsF_path, "r"); 

    while
    (
        fgets(nameIn_file, 25, pAccounts_names) != NULL &&
        fgets(passWord_inFile, 25, pAccounts_passWords) != NULL
    )
    {
        if(strcmp(nameIn_file, account.name) == 0 && strcmp(passWord_inFile, account.password) == 0)
        {
            printf("\nSuccessfully loged in!");
            getch();

            fclose(pAccounts_names);
            fclose(pAccounts_passWords);
            return 1;
        }
    }
    //search in each line to find the typed account 

    printf("\nSorry, it was not possible to find this account.");
    printf("\nCheck the inputs!");

    fclose(pAccounts_names);
    fclose(pAccounts_passWords);
    return 0;
}
//the user needs to enter in an account to play
//if it returns 0, it means it was not possible to enter in an account

void refreshHanged(int wrongGuesses)
{
    printf("\t\t\t\tHANGMAN GAME - Player: %s", account.name);
    printf("\t\t------------------------------------------------------------");

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

void addPoints_toPlayer(int points) //this function does not work yet
{
    int lineNum = 0, pointsIn_file = 0, i = 0;
    char nameIn_file[25]; 
    
    pAccounts_names = fopen(namesF_path, "r");
    while(fgets(nameIn_file, 25, pAccounts_names) != NULL)
    {
        lineNum++;

        if(strcmp(nameIn_file, account.name) == 0)
            break;
    }
    fclose(pAccounts_names);

    pAccounts_points = fopen(pointsF_path, "r");
    pTemp_file = fopen(tempF_path, "w");

    while(fscanf(pAccounts_points, "%d", &pointsIn_file) != EOF)
    {
        i++; 

        if(i == lineNum)
        {
            printf("\npoints in file: %d", pointsIn_file);
            fprintf(pTemp_file, "%d\n", pointsIn_file + points);
        }
        else if(pointsIn_file != EOF)
        {
            printf("\npoints in file: %d", pointsIn_file);
            fprintf(pTemp_file, "%d\n", pointsIn_file);
        }   
    } 
    
    fclose(pAccounts_points);
    fclose(pTemp_file);

    printf("\nremove = %d", remove(pointsF_path));
    printf("\nrename = %d", rename(tempF_path, pointsF_path));
    //-> bug: both functions dont work   
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

int isA_validWord(char typedWord[])
{
    int i;
    char buffer[50];
    
    strupr(typedWord);

    for(i = 0; i < strlen(typedWord) - 1; i++) //-1 because it has \n in last char
    {
        if(typedWord[i] != ' ' && (typedWord[i] < 'A' || typedWord[i] > 'Z')) //just allows spaces and alphabets
        {
            printf("\nInvalid Input. Please, just type Alphabet letters!");
            getch();
            return 0;
        }
    }

    pWords = fopen(wordsF_path, "r");
    while(fgets(buffer, 50, pWords) != NULL)
    {
        if(strcmp(buffer, typedWord) == 0) //if it returns 0, it means that the words are equal
        {
            printf("\nInvalid Input. This word exist already!"); 
            getch();
            fclose(pWords);
            return 0;
        }
    }
    fclose(pWords);

    return 1; //if any case matches, it means that word is valid and returns TRUE
} 