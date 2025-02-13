#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//TODO: Add arrow controls for ver 2.0
//set to text to purple
#define SELECT(string) "\x1b[35m" string "\x1b[0m"

//set text to red for error
#define NUHUH(string) "\x1b[31m" string "\x1b[0m"

char getch();
int menu(const char[], const char (*)[], const char[], int);

int main(){
    int option = 0, optionSel = 0, optionEnter = 0, arrowPoint = 0, MaxNumOfElements;
    
    //test
    int numOfElements = 3;
    int arrowSel[numOfElements];
    
    if (numOfElements > 9){
        MaxNumOfElements = 9;
    }else{
        MaxNumOfElements = numOfElements;
    }

    while(option != numOfElements){
        for(int i = 0; i <= numOfElements; i++){
            arrowSel[i-1] == i;
        }

        for(int i = 0; i < numOfElements; i++){
            (optionSel == i + 1)? printf("[%d]\n", i+1) : printf("%d\n", i+1);
        }

        optionEnter = optionSel;
        optionSel = getch();

        if(optionSel > 0 && optionSel <= MaxNumOfElements){
            arrowPoint = optionSel;
        }

        //up
        if(optionSel == 18){
            arrowPoint ++;
            if(arrowSel[arrowPoint] == 0){
                arrowPoint -= arrowPoint;
                arrowPoint++;
                printf("\nUP: %d\n", arrowPoint);
                optionSel = arrowPoint;
            }
            else{
                optionSel = arrowPoint;
            }
        }

        //down
        if(optionSel == 17){
            arrowPoint --;
            if(arrowPoint <= 0){
                arrowPoint = numOfElements;
                printf("\nDOWN: %d\n", arrowPoint);
                optionSel = arrowPoint;
            }
            else{
                optionSel = arrowPoint;
            }
        }
        system("clear");
        
    }
}

char getch(){
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