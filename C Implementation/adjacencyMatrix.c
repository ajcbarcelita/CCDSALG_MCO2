#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "data_structures.c"

bool** loadAdjMatrix(char *fileString, int* numVertices, int* numEdges)
{
    FILE *fp;
    int i, j, ID1, ID2, status;

    fp = fopen(fileString, "r");
    if (fp == NULL) {
        printf("File not found. Please try again.\n");
        return NULL;
    } else {
        printf("File found. Now loading...\n");
    }

    fscanf(fp, "%d %d", numVertices, numEdges);
    bool **adjMatrix = malloc(*numVertices * sizeof(bool*));
    if (adjMatrix == NULL) {
        printf("Memory allocation for adjacency matrix has failed. Terminating program...\n");
        free(adjMatrix);
        fclose(fp);
        exit(-1);
    }

    for (i = 0; i < *numVertices; i++) {
        adjMatrix[i] = calloc(*numVertices, sizeof(bool));
        if (adjMatrix[i] == NULL) {
            printf("Memory allocation for adjacency matrix has failed. Terminating program...\n");
            for (j = 0; j < i; j++) {
                free(adjMatrix[j]);
            }
            free(adjMatrix);
            fclose(fp);
            exit(-1);
        }
    }

    while (fscanf(fp, "%d %d", &ID1, &ID2) != EOF) {
        adjMatrix[ID1][ID2] = true; //sets the edge between ID1 and ID2 to true, indicating that there is an edge between them
        // adjMatrix[ID2][ID1] = true; 
    }

    fclose(fp);
    return adjMatrix;
}

bool hasEdge(bool** adjMatrix, int ID1, int ID2)
{
    return adjMatrix[ID1][ID2] && adjMatrix[ID2][ID1];
}

void printAdjMatrix(bool** adjMatrix, int numVertices)
{
    int i, j;

    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void printFriendList(bool **adjMatrix, int numVertices, int ID1) 
{
    int i, friendCount = 0;
    if (ID1 < 0 || ID1 >= numVertices) {
        printf("Invalid ID. ID should be a value between 0 to %d. Please try again.\n", numVertices - 1);
        return;
    }
    printf("\n\t=== %d's FRIEND LIST ===\n", ID1);
    for (i = 0; i < numVertices; i++) {
        if(hasEdge(adjMatrix, ID1, i)) {
            printf("%d\n", i);
            friendCount++;
        }
    }
}

int* findConnections_BFS(bool** adjMatrix, int numVertices, int ID1, int ID2)
{
    int i, currentIndex;
    bool* visitedVertices = calloc(numVertices, sizeof(bool));
    
    if (ID1 < 0 || ID1 >= numVertices || ID2 < 0 || ID2 >= numVertices || ID1 == ID2) {
        return NULL;
    }
    
}

// int* findConnections_DFS(bool** adjMatrix, int numVertices, int ID1, int ID2)
// {
//     if (ID1 < 0 || ID1 >= numVertices || ID2 < 0 || ID2 >= numVertices || ID1 == ID2) {
//         return NULL;
//     }
// }
    