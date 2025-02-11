/*==================================================================================================+
|   - Created by HalfAsleepDev                                                                      |
|   - Version 1.0                                                                                   |
|   - Last update: Feb, 10, 2025                                                                    |
+===================================================================================================+
*/

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"

//set selected text to purple
#define SELECT(string) "\x1b[35m" string "\x1b[0m"

//set text to red for error
#define NUHUH(string) "\x1b[31m" string "\x1b[0m"

char getch();
int menu(const char[], const char (*)[], const char[], int);

int menu(const char header[], const char menuElements[][50], const char endPhrase[], int numOfElements){
    int option = 0, optionSel = 0, optionEnter = 0;

    while(option != numOfElements){
        //print header
        printf("\n==============================================\n");
        printf("---%*s%*s---\n", 20+strlen(header)/2, header, 20-strlen(header)/2, "");
        printf("==============================================\n");

        //print each element
        for(int i = 0; i < numOfElements; i++){
            //(optionSel == i + 1)? printf("--->%d. [%s]\n", i+1, menuElements[i]) : printf("%d. %s\n", i+1, menuElements[i]); //no color
            //(optionSel == i + 1)? printf(SELECT("--->%d. [%s]\n"), i+1, menuElements[i]) : printf("%d. %s\n", i+1, menuElements[i]); //full line color
            (optionSel == i + 1)? printf("--->%d. [" SELECT("%s") "]\n", i+1, menuElements[i]) : printf("%d. %s\n", i+1, menuElements[i]); //only menu element color
        }
        printf("(NAVIGATE: '1 - %d')('ENTER' TO SELECT)", numOfElements);

        optionEnter = optionSel;
        optionSel = getch();

        //if the `ENTER` key is pressed
        if(optionSel == -38){
            //the previous key is set to option
            option = optionEnter;
            //if the selection is valid
            if(option > 0 && option <= numOfElements){
                if(option == numOfElements){
                    system("clear");
                    //print the end phrase
                    printf("==============================================\n");
                    printf("---%*s%*s---\n", 20+strlen(endPhrase)/2, endPhrase, 20-strlen(endPhrase)/2, "");
                    printf("==============================================\n");
                    return option;
                }
                else{
                    //return option
                    system("clear");
                    return option;
                }
                
            }
            else{
                //input error
                system("clear");
                printf(NUHUH("Invalid choice. Please try again.\n"));
                continue;
            }
        }
        system("clear");
    }
}


char getch() {
    struct termios oldt, newt;
    char ch;
    int chNum;
    
    // Get current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable buffering and echo
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Read a single character
    ch = getchar();

    // Restore old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    chNum = ch - '0';

    return chNum;
}