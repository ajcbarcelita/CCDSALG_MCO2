#include <string.h>
#include "adjacencyList.c"
#include "adjacencyMatrix.c"
#include "data_structures.h"

int main()
{
    int i, ID1, ID2, status = 0, pathLength = 0; 
    int numVertices = 0, numEdges = 0;
    int menuChoice = 0, graphChoice = 0, searchChoice = 0;
    char fileString[500];
    bool fileFound = false;
    bool** adjMatrix;
    FILE *fp;

    /*
        This part of the code asks for the file path or file name of the .txt file containing the social graph data.
        It only considers the scenarios whether if the file is not found, OR if the file is found and IS of valid format.
        Using a .txt file of invalid format will not be considered in this part of the code, and will therefore lead to undefined behavior.
    */
    while (fileFound == false) {
        printf("\n\t=== LOAD GRAPH DATA===\n");
        printf("Please indicate the ABSOLUTE file path or file name of the .txt file containing the social graph data.\n");
        printf("If entering the file name, please ensure that the file is in the same directory as the program.\n");
        printf("Enter the file path or file name: ");
        fgets(fileString, 500, stdin);
        fileString[strcspn(fileString, "\n")] = '\0';
        fp = fopen(fileString, "r");
        if (fp == NULL) {
            printf("File not found. Please try again.\n");
        } else {
            printf("File found. Now loading...\n");
            fileFound = true;
        }
    }

    /*
        This part of the code asks for the format of the social graph data.
        User can choose between Adjacency List and Adjacency Matrix format for the graph.
    */
    while (graphChoice != 1 && graphChoice != 2) {
        printf("\n\t=== GRAPH SELECTION ===\n");
        printf("Please choose the format of the social graph.\n");
        printf("[1] Adjacency List.\n");
        printf("[2] Adjacency Matrix.\n");
        printf("Enter your choice: ");
        scanf("%d", &graphChoice);
        
        switch(graphChoice) {
            case 1:
                printf("Adjacency List selected.\n");
                //create the adj list
                break;
            case 2:
                printf("Adjacency Matrix selected.\n");
                //create the adj matrix
                adjMatrix = loadAdjMatrix(fileString, &numVertices, &numEdges);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    /*
        This part of the code is the main menu of the program.
        User can choose between different functionalities to perform on the social graph data.
    */
    while (menuChoice != 3) {
        printf("\n\t=== MAIN MENU ===\n");
        printf("[1] Display friend list of a certain ID.\n");
        printf("[2] Find connections between two IDs.\n");
        printf("[3] Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &menuChoice);

        switch(menuChoice) {
            case 1:
                printf("Enter the ID of the person whose friend list you want to display: ");
                scanf("%d", &ID1);
                if (graphChoice == 1) {
                    printf("WIP"); //printFriendList(adjList, numVertices, ID1);
                } else if (graphChoice == 2) {
                    printFriendList(adjMatrix, numVertices, ID1);
                }
                break;

            case 2:
                printf("Enter ID 1: ");
                scanf("%d", &ID1);
                printf("Enter ID 2: ");
                scanf("%d", &ID2);
                printf("Choose a search method to be executed: \n");
                printf("[1] Breadth First Search.\n");
                printf("[2] Depth First Search.\n");
                printf("Enter your choice: ");
                scanf("%d", &searchChoice);
                if (graphChoice == 1) {

                } else if (graphChoice == 2) {
                    if (searchChoice == 1) {
                        printf("Performing Breadth First Search on the graph (adjacency matrix)...\n");
                        int* path = findConnections_BFS(adjMatrix, numVertices, ID1, ID2, &pathLength);
                        if (path == NULL) {
                            printf("No connection found between ID %d and ID %d.\n", ID1, ID2);
                        } else {
                            printf("Connection found between ID %d and ID %d.\n", ID1, ID2);
                            for (i = 0; i < pathLength - 1; i++) {
                                printf("%d is friends with %d\n", path[i], path[i + 1]);
                            }
                            printf("\n");
                        } 
                    } else if (searchChoice == 2) {

                    }
                }
                break;

            case 3:
                printf("Exiting program...\n");
                break;
            
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
     }

    return 0;
}