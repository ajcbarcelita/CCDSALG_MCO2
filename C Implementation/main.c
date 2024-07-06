#include <stdio.h>
#include <stdlib.h>

int main() //
{
    int choice = 0;
    /*
        Planning to do both implementations. Maybe ask for an option to either use adjacency list or adjacency matrix when loading the file.
    */

    //main menu
    while (choice != 3) {
        printf("\t==== MAIN MENU ====\n\n");
        printf("[1] Display friend list.\n");
        printf("[2] Display connections.\n");
        printf("[3] Exit.\n\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                /*  
                    This function accepts an ID number as a parameter.
                    If valid, display total number of friends and list of friends.
                    If not, display an error message, BUT not exit the program.
                */  
                break;
            case 2:
                /*
                    This function accepts 2 different ID numbers as parameters.
                    If both ID numbers exist, display the connection/path between the two, i.e, ID1 is friends with c1, until c(n-1) is friends with ID2.
                    
                    Note: 
                    - A connection is a sequence from ID1, c1, c2, ..., ID2 such that ID1 is friends with c1, 
                    c1 is friends with c2, ..., and c(n-1) is friends with ID2.

                    If any/both ID numbers does not exist, display an error message, BUT not exit the program.
                */
                break;
            case 3:
                printf("Exiting the program...");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}