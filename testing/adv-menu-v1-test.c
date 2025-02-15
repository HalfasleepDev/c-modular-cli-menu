#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//set to text to purple
#define SELECT(string) "\x1b[35m" string "\x1b[0m"

//set text to red for error
#define NUHUH(string) "\x1b[31m" string "\x1b[0m"


char getch();
//(number of elements, navArray, end phrase)
int mainMenu(int, const char (*)[*][*], const char[]);
//(number of page elements, page number array, size of page number array, number of elements, navArray)
int subMenu(int, int*,int, int, const char (*)[*][*]);
int subMenuI();
int subMenuO();

//struct to store info??

int main(){
    int option;

    //[PAGES][MAX ELements][MAX STRING LENGTH]
    char navArray[4][5][50] = {
        //(header, tab 1, tab 2,..., "exit/back phrase")
        {"Main Menu", "Tab 1", "Tab 2", "Tab 3", "Exit"}, //page 0 (main menu)
        {"Tab 1", "Input", "Result History", "Back"}, //page 1 (Tab 1) IO
        {"Tab 2", "Sub Menu 1", "Sub Menu 2", "Sub Menu 3", "exit"}, //page 2 (Tab 2)
        {"Tab 3"} //page 3 (Tab 3)
    };

    char endString[] = "HAVE A GOOD DAY!";

    while(option != 4){
        option = mainMenu(5, navArray, endString);
        //printf("\n SELECTED OPTION: %d\n", option);
        switch(option){
            case 1:
                //sub menu here
                int subMenuStruct[] = {0, 1};
                option = subMenu(4, subMenuStruct, 2, 5, navArray);
                printf("\n SELECTED OPTION: %d\n", option);
                break;
            default:
                printf("\n SELECTED OPTION: %d\n", option);
        }
        //clear buffer when additional input is used
        //while ((getchar()) != '\n');
    }
    return 0;
}



/*TODO:
    - sub menu input
    - sub menu output
    - sub menu history (Input/Output history)
*/

// mainMenu
int mainMenu(int numOfElements, const char navArray[][numOfElements][50], const char endPhrase[]){
    int option = 0, optionSel = 0, optionEnter = 0, arrowPoint = 0, MaxNumOfElements;

    //arrow select array
    int arrowSel[numOfElements];

    //set max number for detection
    if (numOfElements > 9){
        MaxNumOfElements = 9;
    }else{
        MaxNumOfElements = numOfElements;
    }

    //initialize arrow select array elements
    for(int i = 1; i <= numOfElements; i++){
        arrowSel[i-1] == i;
    }

    //main menu loop
    while(option != numOfElements){
        //print header
        printf("\n======================================================================\n");
        printf("---%*s%*s---\n", 32+strlen(navArray[0][0])/2, navArray[0][0], 32-strlen(navArray[0][0])/2, "");
        printf("======================================================================\n");

        //print each element
        for(int i = 1; i < numOfElements; i++){
            if(i + 1 == numOfElements){
                printf("\n");
            }
            //(optionSel == i + 1)? printf("--->%d. [%s]\n", i+1, menuElements[i]) : printf("%d. %s\n", i+1, menuElements[i]); //no color
            //(optionSel == i + 1)? printf(SELECT("--->%d. [%s]\n"), i+1, menuElements[i]) : printf("%d. %s\n", i+1, menuElements[i]); //full line color
            (optionSel == i + 1)? printf("--->[%d] [" SELECT("%s") "]\n", i, navArray[0][i]) : printf("[%d] %s\n", i, navArray[0][i]); //only menu element color
        }
        printf("----------------------------------------------------------------------\n");
        printf("(NAVIGATE: '1 - %d' OR 'UP' 'DOWN')('ENTER' TO SELECT)\n", numOfElements - 1);

        optionEnter = optionSel;
        optionSel = getch();
        optionSel++;

        //update arrow point
         if(optionSel > 0 && optionSel <= MaxNumOfElements){
            arrowPoint = optionSel;
        }

        //if the `UP` key is pressed
        if(optionSel == 19){
            arrowPoint ++;

            //if the arrowpoint has reached the max number
            if(arrowPoint > numOfElements){
                arrowPoint -= numOfElements - 1;
                //arrowPoint++;
                optionSel = arrowPoint;
            }
            else{
                optionSel = arrowPoint;
            }
        }

        //if the `DOWN` key is pressed
        if(optionSel == 18){
            arrowPoint --;

            //if the arrowpoint has reached the max number
            if(arrowPoint <= 1){
                arrowPoint = numOfElements;
                optionSel = arrowPoint;
            }
            else{
                optionSel = arrowPoint;
            }
        }

        //if the `ENTER` key is pressed
        if(optionSel == -37){
            //the previous key is set to option
            option = optionEnter;
            //if the selection is valid
            if(option > 1 && option <= numOfElements){
                if(option == numOfElements){
                    system("clear");
                    //print the end phrase
                    printf("======================================================================\n");
                    printf("---%*s%*s---\n", 32+strlen(endPhrase)/2, endPhrase, 32-strlen(endPhrase)/2, "");
                    printf("======================================================================\n");
                    return option -1;
                }
                else{
                    //return option
                    system("clear");
                    return option -1;
                }
            }
            else{
                system("clear");
                printf(NUHUH("Invalid choice. Please try again.\n"));
                //printf("%d\n", optionEnter);//17up,18down
                continue;
            }
        }
        system("clear");
    }
}

//TODO: stress test inputs
int subMenu(int pageElements, int pageNum[], int subPageSize, int numOfElements, const char navArray[][numOfElements][50]){
    int option = 0, optionSel = 0, optionEnter = 0, arrowPoint = 0, MaxNumOfElements, currentPage;

    //subPageSize = sizeof(pageNum) / sizeof(pageNum[0]);

    //arrow select array
    int arrowSel[pageElements];

    //set max number for detection
    if (pageElements > 9){
        MaxNumOfElements = 9;
    }else{
        MaxNumOfElements = pageElements;
    }

    //initialize arrow select array elements
    for(int i = 1; i <= pageElements; i++){
        arrowSel[i-1] == i;
    }

    //main menu loop
    while(option != pageElements){
        //print header
        printf("\n----------------------------------------------------------------------\n");
        //for loop
        for(int i = 0; i < subPageSize; i++){
            if(i == subPageSize -1){
                printf(SELECT("%s")"\n", navArray[1][0]);
                currentPage = i;
                continue;
            }
            printf("%s/", navArray[pageNum[i]][0]);
        }
        
        printf("----------------------------------------------------------------------\n");

        //print each element
        for(int i = 1; i < pageElements; i++){
            if(i + 1 == pageElements){
                printf("\n");
            }
            //(optionSel == i + 1)? printf("--->%d. [%s]\n", i+1, menuElements[i]) : printf("%d. %s\n", i+1, menuElements[i]); //no color
            //(optionSel == i + 1)? printf(SELECT("--->%d. [%s]\n"), i+1, menuElements[i]) : printf("%d. %s\n", i+1, menuElements[i]); //full line color
            (optionSel == i + 1)? printf("--->[%d] [" SELECT("%s") "]\n", i, navArray[currentPage][i]) : printf("[%d] %s\n", i, navArray[currentPage][i]); //only menu element color
        }
        printf("----------------------------------------------------------------------\n");
        printf("(NAVIGATE: '1 - %d' OR 'UP' 'DOWN')('ENTER' TO SELECT)\n", pageElements - 1);

        optionEnter = optionSel;
        optionSel = getch();
        optionSel++;

        //update arrow point
         if(optionSel > 0 && optionSel <= MaxNumOfElements){
            arrowPoint = optionSel;
        }

        //if the `UP` key is pressed
        if(optionSel == 19){
            arrowPoint ++;

            //if the arrowpoint has reached the max number
            if(arrowPoint > pageElements){
                arrowPoint -= pageElements - 1;
                //arrowPoint++;
                optionSel = arrowPoint;
            }
            else{
                optionSel = arrowPoint;
            }
        }

        //if the `DOWN` key is pressed
        if(optionSel == 18){
            arrowPoint --;

            //if the arrowpoint has reached the max number
            if(arrowPoint <= 1){
                arrowPoint = pageElements;
                optionSel = arrowPoint;
            }
            else{
                optionSel = arrowPoint;
            }
        }

        //if the `ENTER` key is pressed
        if(optionSel == -37){
            //the previous key is set to option
            option = optionEnter;
            //if the selection is valid
            if(option > 1 && option <= pageElements){
                if(option == pageElements){
                    system("clear");
                    //print the end phrase
                    //printf("======================================================================\n");
                    //printf("---%*s%*s---\n", 32+strlen(endPhrase)/2, endPhrase, 32-strlen(endPhrase)/2, "");
                    //printf("======================================================================\n");
                    return option -1;
                }
                else{
                    //return option
                    system("clear");
                    return option -1;
                }
            }
            else{
                system("clear");
                printf(NUHUH("Invalid choice. Please try again.\n"));
                //printf("%d\n", optionEnter);//17up,18down
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
