#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "adjacencyMatrix.c"
#include "adjacencyList.c"
#include "data_structures.c"

int main()
{
    int i, ID1, ID2, status = 0, pathLength = 0; 
    int numVertices = 0, numEdges = 0;
    int menuChoice = 0, graphChoice = 0, searchChoice = 0;
    char fileString[500]; //the file path or file name of the .txt file containing the social graph data
    bool fileFound = false; 
    singlyNode** adjList = NULL;
    bool** adjMatrix = NULL;
    FILE *fp;

    /*
        This part of the code asks for the file path or file name of the .txt file containing the social graph data.
        It checks first if file exists, then also checks if the file is of valid format, i.e, first line contains two integers.

        By Aaron Barcelita.
    */ 
    while (fileFound == false) {
        printf("\n\t=== LOAD GRAPH DATA===\n");
        printf("Please indicate the ABSOLUTE file path or file name of the .txt file containing the social graph data.\n");
        printf("If entering the file name, please ensure that the file is in the same directory as the program.\n");
        printf("Enter the file path or file name: ");
        fgets(fileString, 500, stdin);
        fileString[strcspn(fileString, "\n")] = '\0'; //removes the newline character at the end of the string
        fp = fopen(fileString, "r"); 
        if (fp == NULL) { //if file does not exist
            printf("File not found. Please try again.\n");
        } else {
           if (fscanf(fp, "%d %d", &numVertices, &numEdges) == 2) { //if the first line contains two integers
                fileFound = true;
                printf("File found and is also valid.\n");
                fclose(fp);
            } else {
                printf("Invalid file format. Please try again.\n");
                fclose(fp);
            }
        }

    /*
        This part of the code asks the user to choose the format of the social graph.
        The user can choose between an adjacency list or an adjacency matrix.
        
        The program will only proceed if the user chooses a valid option, i.e., 1 or 2.
        If the user chooses an invalid option, the program will prompt the user to choose again.
        However, if the user inputs an input type that is not a number, the program will terminate.
        
        By Aaron Barcelita.
    */
    while (graphChoice != 1 && graphChoice != 2) {
        printf("\n\t=== GRAPH SELECTION ===\n");
        printf("Please choose the format of the social graph.\n");
        printf("[1] Adjacency List.\n");
        printf("[2] Adjacency Matrix.\n");
        printf("Enter your choice: ");
        scanf("%d", &graphChoice);
        while (getchar() != '\n');
        
        switch(graphChoice) {
            case 1:
                printf("Adjacency List selected.\n");
                //create the adj list
                adjList = loadAdjacencyList(fileString, &numVertices, &numEdges);
                printf("Adjacency List created.\n");
                break;
            case 2:
                printf("Adjacency Matrix selected.\n");
                //create the adj matrix
                adjMatrix = loadAdjMatrix(fileString, &numVertices, &numEdges);
                printf("Adjacency Matrix created.\n");
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
        while (getchar() != '\n');

        switch(menuChoice) {
            case 1:
                printf("Enter the ID of the person whose friend list you want to display: ");
                scanf("%d", &ID1);
                if (graphChoice == 1) {
                    printFriendList_AdjList(adjList, numVertices, ID1);
                } else if (graphChoice == 2) {
                    printFriendList_adjMatrix(adjMatrix, numVertices, ID1);
                }
                break;

            case 2:
                printf("Enter ID 1: ");
                scanf("%d", &ID1);
                printf("Enter ID 2: ");
                scanf("%d", &ID2);
                printf("\nChoose a search method to be executed: \n");
                printf("[1] Breadth First Search.\n");
                printf("[2] Depth First Search.\n");
                printf("Enter your choice: ");
                scanf("%d", &searchChoice);
                if (graphChoice == 1) {
                    if (searchChoice == 1) {
                        printf("\nPerforming Breadth First Search on the graph (adjacency list)...\n");
                        int* path = findConnections_BFS_AdjList(adjList, numVertices, ID1, ID2, &pathLength);
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
                        printf("\nPerforming Depth First Search on the graph (adjacency list)...\n");
                        int* path = findConnections_DFS_AdjList(adjList, numVertices, ID1, ID2, &pathLength);
                        if (path == NULL) {
                            printf("No connection found between ID %d and ID %d.\n", ID1, ID2);
                        } else {
                            printf("Connection found between ID %d and ID %d.\n", ID1, ID2);
                            for (i = 0; i < pathLength - 1; i++) {
                                printf("%d is friends with %d\n", path[i], path[i + 1]);
                            }
                            printf("\n");
                        }
                    }
                } else if (graphChoice == 2) {
                    if (searchChoice == 1) {
                        printf("\nPerforming Breadth First Search on the graph (adjacency matrix)...\n");
                        int* path = findConnections_BFS_AdjMatrix(adjMatrix, numVertices, ID1, ID2, &pathLength);
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
                        printf("\nPerforming Depth First Search on the graph (adjacency matrix)...\n");
                        int* path = findConnections_DFS_AdjMatrix(adjMatrix, numVertices, ID1, ID2, &pathLength);
                        if (path == NULL) {
                            printf("No connection found between ID %d and ID %d.\n", ID1, ID2);
                        } else {
                            printf("Connection found between ID %d and ID %d.\n", ID1, ID2);
                            for (i = 0; i < pathLength - 1; i++) {
                                printf("%d is friends with %d\n", path[i], path[i + 1]);
                            }
                            printf("\n");
                        }
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
    }
}