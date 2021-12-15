//this was created by: Paulo
//it's totally free to use
//Github: Paulo-Henrique-Silva

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

FILE
*pWords, 
*pAccounts_names,
*pAccounts_passWords,
*pAccounts_points;

const char 
wordsF_path[] = "words.txt", 
namesF_path[] = "names.txt",
pointsF_path[] = "points.txt",
passwordsF_path[] = "passwords.txt";

char word[50] = {'\0'}; 

struct player
{
    char name[25], password[25];
};

struct player account;

enum menu 
{
    play = 1, howToplay, addAccount, deleteAccounts, seeAccounts, 
    addWord, deleteWord, seeWords, exitGame
};

void playGame();
void howTo_play();
void addA_account(); 
void deleteA_account();
void showAccounts(); 
void addA_word();
void deleteA_word();
void seeWord_list();
//game options

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
int numOf_words();
int isA_validWord(char typedWord[]);
int numOf_accounts(); 
int isA_validName(char name[]); 

int main()
{
    int operation = 0;

    while(operation != exitGame)
    {
        system("cls");
        printf("\t\t\t\tHANGMAN GAME\n");
        printf("\n\t\t\t\t[1] - Play Game");
        printf("\n\t\t\t\t[2] - How To Play");
        printf("\n\t\t\t\t[3] - Add an Account");
        printf("\n\t\t\t\t[4] - Delete an Account");
        printf("\n\t\t\t\t[5] - Show Accounts");
        printf("\n\t\t\t\t[6] - Add a Word");
        printf("\n\t\t\t\t[7] - Delete a Word");
        printf("\n\t\t\t\t[8] - Show Word List");
        printf("\n\t\t\t\t[9] - Exit");
        printf("\n\nType your operation: ");
        scanf("%d", &operation); 

        switch(operation)
        {
            case play:
                playGame();
                break;
            case howToplay:
                howTo_play();
                break;
            case addAccount:
                addA_account();
                break;
            case deleteAccounts:
                deleteA_account();
                break;
            case seeAccounts:
                showAccounts();
                break;
            case addWord:
                addA_word();
                break;
            case deleteWord:
                deleteA_word();
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
    
    if(logIn_anAccount())
    {
        system("cls");
        chooseA_randomWord();

        refreshHanged(wrongGuesses);    
        refreshWord(rightLetters); 
        showWrong_letters(wrongLetters);
        //shows the word and the draw just for the first time

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
        //calculates the player score

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

void howTo_play()
{
    system("cls");

    printf("\t\t\t\t\tHOW TO PLAY");
    printf("\n\t\t------------------------------------------------------------\n");

    printf("\n - Hangman Game is a popular game that the main objetive is avoid that a hanged guy dies.");
    printf("\n - To save him you need to guess a word, letter by letter.\n");

            printf("\n\t\t\t\t|--------|");
            printf("\n\t\t\t\t|        O");
            printf("\n\t\t\t\t|       /|\\        <- HANGED");
            printf("\n\t\t\t\t|       / \\");
            printf("\n\t\t\t\t|           ");
            printf("\n\t\t\t\t|__________");
            printf("\n\n\t\t\t\t_ _ _ _ - _ _ _ _     <- WORD\n");

    printf("\n   -> If you guess correctly, that letter in word will be revelead.");
    printf("\n   -> Else, a part of the hanged's body will be drawed.");
    printf("\n   -> To win, you need to guess the all the letters without let the hanged's draw finish");

    printf("\n\n - In this program, you need an ACCOUNT to play. After created, you'll have a score");
    printf("\n - The score is calculated by 6 SUBTRACTED by the number of wrong gueeses that you had in a Match");
    printf("\n   -> Example: If you wrongly guessed 4 times, you have now 2 points");
    printf("\n   -> If you didn't wrongly guessed anytime, you get 6 points");

    printf("\n\n - In addition, the program have a few words by default, but you can add your own words later.");
    printf("\n\nCreate accounts, words and Play :)");
}

void addA_account()
{
    system("cls");
    printf("\t\t\t\t\tADDING ACCOUNT");
    printf("\n\t\t------------------------------------------------------------\n");

    scanf("%c"); //avoid extra \n

    checkAccounts_data(); 
    //how it's adding an account, there is not need to block if the files were deleted or empty

    if(numOf_accounts() < 10)
    {
        printf("\nType a UserName to the new Account: "); 
        fgets(account.name, 25, stdin);

        printf("\nType a PassWord: "); 
        fgets(account.password, 25, stdin);


        if(isA_validName(account.name))
        {
            pAccounts_names = fopen(namesF_path, "a");
            pAccounts_passWords = fopen(passwordsF_path, "a");
            pAccounts_points = fopen(pointsF_path, "a");

            fputs(account.name, pAccounts_names);
            fputs(account.password, pAccounts_passWords);
            fprintf(pAccounts_points, "%d\n", 0);

            fclose(pAccounts_names);
            fclose(pAccounts_passWords);
            fclose(pAccounts_points);
            
            printf("\nNew Account Sucessfully Added!");
        }
        else
            printf("\nInvalid Input. There is an account with this name already!");
    }
    else
        printf("\nSorry :/, limit of Accounts reached! (10)");
}

void deleteA_account()
{
    FILE *pTemp_namesFile, *pTemp_passWords_File, *pTemp_pointsFile;

    const char 
    tempNames_path[] = "tmpNames.tmp", 
    tempPasswords_path[] = "tmpPasswords.tmp", 
    tempPoints_path[] = "tmpPoints.tmp";

    char nameIn_line[25], passWord_inLine[25];
    int pointsIn_line, i = 0, accountNum_toDelete = 0;

    system("cls");

    printf("\t\t\t\t\tDELETE A ACCOUNT");
    printf("\n\t\t------------------------------------------------------------");

    if(checkAccounts_data()) //checks if the files are ok and there is at least one account
    {
        pAccounts_names = fopen(namesF_path, "r"); 

        while(fgets(nameIn_line, 25, pAccounts_names) != NULL)
        {
            i++; 
            nameIn_line[strlen(nameIn_line) - 1] = '\0'; //remove \n in last char

            printf("\n\t\t\t\t\t%d - %s", i, nameIn_line);
        }

        printf("\n\nType the Account number to delete: ");
        scanf("%d", &accountNum_toDelete); 

        if(accountNum_toDelete < 1 || accountNum_toDelete > i)
        {
            printf("\nInvalid input!");
            fclose(pAccounts_names); 
        }
        else
        {
            rewind(pAccounts_names);

            pAccounts_passWords = fopen(passwordsF_path, "r");
            pAccounts_points = fopen(pointsF_path, "r");
            pTemp_namesFile = fopen(tempNames_path, "w");
            pTemp_passWords_File = fopen(tempPasswords_path, "w");
            pTemp_pointsFile = fopen(tempPoints_path, "w");

            i = 0;
            while
            (
                fgets(nameIn_line, 25, pAccounts_names) != NULL &&
                fgets(passWord_inLine, 25, pAccounts_passWords) != NULL &&
                fscanf(pAccounts_points, "%d", &pointsIn_line) != EOF
            )
            {
                i++;

                if(i != accountNum_toDelete)
                {
                    fprintf(pTemp_namesFile, "%s", nameIn_line);
                    fprintf(pTemp_passWords_File, "%s", passWord_inLine);
                    fprintf(pTemp_pointsFile, "%d\n", pointsIn_line);
                }
            }
            //copy the old content from files and paste in new files
            //except from the account that user wants to delete

            fclose(pAccounts_names); 
            fclose(pAccounts_passWords); 
            fclose(pAccounts_points); 
            fclose(pTemp_namesFile); 
            fclose(pTemp_passWords_File); 
            fclose(pTemp_pointsFile); 

            remove(namesF_path);
            remove(passwordsF_path);
            remove(pointsF_path);
            //remove the old files

            rename(tempNames_path, namesF_path);
            rename(tempPasswords_path, passwordsF_path);
            rename(tempPoints_path, pointsF_path);
            //rename the new files without the deleted account

            printf("\nAccount Successfully Removed from the Program!"); 
        }
    }
    else 
        printf("\nSorry, it was not possible to find An Account. :/");
}

void showAccounts()
{
    char nameIn_file[25], bestPlayer[25];
    int pointsIn_file, i = 0, bestScore; 

    system("cls"); 

    printf("\t\t\t\t\tACCOUNTS");
    printf("\n\t\t------------------------------------------------------------");

    if(checkAccounts_data()) //checks if the files are ok and there is at least one account
    {
        pAccounts_names = fopen(namesF_path, "r");
        pAccounts_points = fopen(pointsF_path, "r"); 

        while
        (
            fgets(nameIn_file, 25, pAccounts_names) != NULL && 
            fscanf(pAccounts_points, "%d", &pointsIn_file) != EOF
        )
        {
            i++;
            nameIn_file[strlen(nameIn_file) - 1] = '\0'; //remove \n of last char

            printf("\n\t\t\t NUMBER: %d - NAME: %s - POINTS: %d ", i, nameIn_file, pointsIn_file);
            printf("\n\t\t------------------------------------------------------------");

            if(i == 1)
            {
                strcpy(bestPlayer, nameIn_file);
                bestScore = pointsIn_file;
            }

            if(pointsIn_file > bestScore)
            {
                strcpy(bestPlayer, nameIn_file);
                bestScore = pointsIn_file; 
            }

            if(pointsIn_file == bestScore && strcmp(nameIn_file, bestPlayer) != 0)
                bestScore = 0;
            //calculates the best player and checks if there's a tie
        }

        fclose(pAccounts_names);
        fclose(pAccounts_points);

        if(bestScore == 0)
            printf("\n\nBest Player: -");
        else
            printf("\n\nBest Player: '%s' - Score: %d", bestPlayer, bestScore);
    }
    else
    {
        printf("\n\nSorry, it was not possible to see the Accounts. :/"); 
        printf("\nMaybe the files were deleted or there is no Account yet");
    }
}

void addA_word()
{
    char newWord[50] = {'\0'};
    int i = 0;

    checkWords_data();

    system("cls");
    printf("\t\t\t\t\tADDING A WORD");
    printf("\n\t\t------------------------------------------------------------\n");

    scanf("%c"); //avoid \n

    if(numOf_words() < 50)
    {
        printf("\nType a new Word: ");
        fgets(newWord, 50, stdin);

        if(isA_validWord(newWord))
        {
            pWords = fopen(wordsF_path, "a");
            fputs(newWord, pWords);
            fclose(pWords); 

            printf("\nThe new Word was Successfully added!");
        }
    }
    else
        printf("\nSorry :/, limit of words reached! (50)");
}

void deleteA_word()
{
    FILE *pTemp_file;
    const char tempF_path[] = "temp.tmp";

    char wordIn_file[50]; 
    int i = 0, wordTo_deleteNum;

    checkWords_data();

    system("cls");
    printf("\t\t\t\t\tDELETE A WORD");
    printf("\n\t\t------------------------------------------------------------\n");

    pWords = fopen(wordsF_path, "r");
    while(fgets(wordIn_file, 50, pWords) != NULL) 
    {
        i++;
        printf("\t\t\t\t%d - %s", i, wordIn_file);
    }

    printf("\nType the Number to delete: ");
    scanf("%d", &wordTo_deleteNum);

    if(wordTo_deleteNum < 1 || wordTo_deleteNum > i)
    {   
        printf("\nInvalid Input!");
        fclose(pWords); 
    }
    else
    {
        rewind(pWords); //go back to begging of file

        i = 0;
        pTemp_file = fopen(tempF_path, "w");

        while(fgets(wordIn_file, 50, pWords) != NULL) 
        {
            i++;

            if(i != wordTo_deleteNum)
                fprintf(pTemp_file, "%s", wordIn_file);
        }
        //copy the content of first file and paste in a temp file.
        //except for the word that the user wants to delete. 

        fclose(pWords); 
        fclose(pTemp_file);

        remove(wordsF_path);
        rename(tempF_path, wordsF_path);
        //remove the old list and rename the new one without that word

        printf("\nWord Successfully Removed from word list!");
    }
}

void seeWord_list()
{
    char wordIn_file[50]; 
    int i = 0;

    checkWords_data();

    system("cls");

    printf("\t\t\t\t\tWORD LIST");
    printf("\n\t\t------------------------------------------------------------\n");

    pWords = fopen(wordsF_path, "r");
    while(fgets(wordIn_file, 50, pWords) != NULL) 
    {
        i++;
        printf("\t\t\t\t%d - %s", i, wordIn_file);
    }
    fclose(pWords); //reads each line and prints on screen
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
    pWords = fopen(wordsF_path, "r"); 

    if(pWords == NULL)
    {
        fclose(pWords); 

        pWords = fopen(wordsF_path, "w");

        fputs("GITHUB\n", pWords);
        fputs("STACK OVERFLOW\n", pWords);
        fputs("GIT\n", pWords);
        fputs("C LANGUAGE\n", pWords);
        fputs("PYTHON\n", pWords);
        fputs("VS CODE\n", pWords);
        fputs("HANGMAN GAME\n", pWords);
        fputs("CODING\n", pWords);
        fputs("PULL REQUEST\n", pWords);
        fputs("PRINTF\n", pWords);
    } 

    fclose(pWords); 
}
//if the file doesn't exist, it will create a new one with a few words.
//then the user can play the game

int checkAccounts_data()
{ 
    char nameIn_firstLine[25], passWord_Infirstline[25];
    int pointsIn_firstLine; 

    pAccounts_names = fopen(namesF_path, "r");
    pAccounts_passWords = fopen(passwordsF_path, "r");
    pAccounts_points = fopen(pointsF_path, "r"); 

    if
    (
        pAccounts_names == NULL || 
        pAccounts_passWords == NULL ||
        pAccounts_points == NULL ||
        fgets(nameIn_firstLine, 25, pAccounts_names) == NULL ||
        fgets(passWord_Infirstline, 25, pAccounts_passWords) == NULL ||
        fscanf(pAccounts_points, "%d", &pointsIn_firstLine) == EOF
    )
    {
        fclose(pAccounts_names);
        fclose(pAccounts_passWords);
        fclose(pAccounts_points);

        pAccounts_names = fopen(namesF_path, "w");
        pAccounts_passWords = fopen(passwordsF_path, "w");
        pAccounts_points = fopen(pointsF_path, "w"); 
        //the files are connect, they don't make sense if one is missing.
        //or one is empty
        //then, they need to be recreated

        fclose(pAccounts_names);
        fclose(pAccounts_passWords);
        fclose(pAccounts_points);

        return 0;
    }
    else 
    {
        fclose(pAccounts_names);
        fclose(pAccounts_passWords);
        fclose(pAccounts_points);

        return 1;
    }
}
//if it returns 1, it means there is data. Else it means that the files were deleted or are empties

int logIn_anAccount()
{
    int pointsIn_file = 0;
    char nameIn_file[25], passWord_inFile[25];

    system("cls");

    printf("\t\t\t\t\tLOGIN");
    printf("\n\t\t------------------------------------------------------------\n");

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

void addPoints_toPlayer(int points) 
{
    FILE *pTemp_file;
    const char tempF_path[] = "temp.tmp";

    int lineNum = 0, pointsIn_file = 0, i = 0;
    char nameIn_file[25]; 

    if(checkAccounts_data())
    {
        pAccounts_names = fopen(namesF_path, "r");
        while(fgets(nameIn_file, 25, pAccounts_names) != NULL)
        {
            lineNum++;

            if(strcmp(nameIn_file, account.name) == 0)
                break;
        }
        fclose(pAccounts_names); 
        //finds the line num of user in file 

        pAccounts_points = fopen(pointsF_path, "r");
        pTemp_file = fopen(tempF_path, "w");

        while(fscanf(pAccounts_points, "%d", &pointsIn_file) != EOF)
        {
            i++; 

            if(i == lineNum)
                fprintf(pTemp_file, "%d\n", pointsIn_file + points);
            else if(pointsIn_file != EOF)
                fprintf(pTemp_file, "%d\n", pointsIn_file);
        } 
        //creates a second file, copy and paste the content.
        //when reaches the user line, it'll add their points in play
        
        fclose(pAccounts_points);
        fclose(pTemp_file);   

        remove(pointsF_path);
        rename(tempF_path, pointsF_path);
        //deletes the old file and renames the new one with the new points
    }
    else
        printf("\nERROR: It was not possible to add points to User."); 
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

int numOf_words()
{
    char buffer[50]; 
    int amountOf_words = 0;

    pWords = fopen(wordsF_path, "r");
    while(fgets(buffer, 50, pWords) != NULL)
        amountOf_words++;
    fclose(pWords);

    return amountOf_words++;
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
            return 0;
        }
    }

    pWords = fopen(wordsF_path, "r");
    while(fgets(buffer, 50, pWords) != NULL)
    {
        if(strcmp(buffer, typedWord) == 0)
        {
            printf("\nInvalid Input. This word exist already!"); 
            fclose(pWords);
            return 0;
        }
    }
    fclose(pWords);

    return 1; //if any case matches, it means that word is valid and returns TRUE
} 

int numOf_accounts()
{
    char buffer[25];
    int numOf_accounts = 0;

    pAccounts_names = fopen(namesF_path, "r");
    while(fgets(buffer, 25, pAccounts_names) != NULL)
        numOf_accounts++;
    fclose(pAccounts_names);
    //calculates the amount of lines(players)

    return numOf_accounts; 
}

int isA_validName(char name[])
{
    char buffer[25];

    pAccounts_names = fopen(namesF_path, "r");
    while(fgets(buffer, 25, pAccounts_names) != NULL)
    {
        if(strcmp(buffer, name) == 0)
        {
            fclose(pAccounts_names);
            return 0;
        }
    }
    fclose(pAccounts_names);

    return 1;
}
//names can't repeat. Then, it searchs in each line to checks if it is a valid name. 