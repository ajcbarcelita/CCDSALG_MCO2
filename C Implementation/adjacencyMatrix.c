#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "data_structures.h"

bool** loadAdjMatrix(char *fileString, int *numVertices, int *numEdges)
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

bool hasEdge_AdjMatrix(bool** adjMatrix, int numVertices, int ID1, int ID2)
{
    if ((ID1 < 0 || ID1 >= numVertices) || (ID2 < 0 || ID2 >= numVertices)) {
        return false;
    }
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
        if(hasEdge_AdjMatrix(adjMatrix, numVertices, ID1, i)) {
            printf("%d\n", i);
            friendCount++;
        }
    }
}


/*
    This function aims to determine whether if a connection exists between two IDs in the social graph that is implemented
    using an adjacency matrix.
    If no connection is found OR if , returns NULL
*/
int* findConnections_BFS_AdjMatrix(bool** adjMatrix, int numVertices, int ID1, int ID2, int* pathLength)
{
    if (ID1 < 0 || ID1 >= numVertices || ID2 < 0 || ID2 >= numVertices || ID1 == ID2) {
        return NULL;
    }

    int i, j, currentIndex;
    bool connectionFound = false;
    int* parentVertices =  malloc(numVertices * sizeof(int));
    //include check
    bool* visitedVertices = calloc(numVertices, sizeof(bool));
    //include check
    PriorityQueue *priorityQueue = createPriorityQueue();

    //include a check here for when manual alloc for these arrays results in NULL and will return early

    memset(parentVertices, -1, numVertices * sizeof(int));
    visitedVertices[ID1] = true;
    enqueue(priorityQueue, ID1);

    while (!isEmptyQueue(priorityQueue)) {
        currentIndex = dequeue(priorityQueue);
        if (currentIndex == ID2) {
            connectionFound = true;
            break;
        }
        for (i = 0; i < numVertices; i++) {
            if (hasEdge_AdjMatrix(adjMatrix, numVertices, i, currentIndex) && !visitedVertices[i]) {
                visitedVertices[i] = true;
                parentVertices[i] = currentIndex;
                enqueue(priorityQueue, i);
            }
        }
    }
    
    if (!connectionFound) {
        free(parentVertices);
        free(visitedVertices);
        free(priorityQueue);
        return NULL;
    }

    //reconstruction logic
    *pathLength = 0;
    for (i = ID2; i != -1; i = parentVertices[i]) {
        (*pathLength)++;
    }

    int* path = malloc(*pathLength * sizeof(int));
    if (path == NULL) {
        printf("Memory allocation for path has failed. Terminating program...\n");
        free(parentVertices);
        free(visitedVertices);
        freePriorityQueue(priorityQueue);
        exit(-1);
    }

    i = ID2;
    for (j = *pathLength - 1; j >= 0; j--) {
        path[j] = i;
        i = parentVertices[i];
    }

    free(parentVertices);
    free(visitedVertices);
    freePriorityQueue(priorityQueue);
    return path;
}

int* findConnections_DFS_AdjMatrix(bool** adjMatrix, int numVertices, int ID1, int ID2, int* pathLength)
{
    if (ID1 < 0 || ID1 >= numVertices || ID2 < 0 || ID2 >= numVertices || ID1 == ID2) {
        return NULL;
    }
    int i, j, currentVertex;
    bool connectionFound = false;
    int* parentVertices = malloc(numVertices * sizeof(int));
    //include check for null
    memset(parentVertices, -1, numVertices * sizeof(int));
    bool* visitedVertices = calloc(numVertices, sizeof(bool));
    //include check for if null

    Stack *stack = createStack();
    //include check for if null

    push(stack, ID1);
    visitedVertices[ID1] = true;

    while(!isEmptyStack(stack)) {
        currentVertex = pop(stack);
        if (currentVertex == ID2) {
            connectionFound = true;
            break;
        }
        for(i = 0; i < numVertices; i++) {
            if (hasEdge_AdjMatrix(adjMatrix, numVertices, i, currentVertex) && !visitedVertices[i]) {
                visitedVertices[i] = true;
                parentVertices[i] = currentVertex;
                push(stack, i);
            }
        }
    }

    if (!connectionFound) {
        free(parentVertices);
        free(visitedVertices);
        freeStack(stack);
        return NULL;
    }

    //reconstruction logic
    *pathLength = 0;
    for (i = ID2; i != -1; i = parentVertices[i]) {
        (*pathLength)++;
    }

    int* path = malloc(*pathLength * sizeof(int));
    //include check for if null
    i = ID2;
    for(j = *pathLength - 1; j >= 0; j--) {
        path[j] = i;
        i = parentVertices[i];
    }

    free(parentVertices);
    free(visitedVertices);
    freeStack(stack);
    return path;
}
    