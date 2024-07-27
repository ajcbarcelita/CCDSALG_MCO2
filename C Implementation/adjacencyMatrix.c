#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "data_structures.h"

/*
    This function loads the social graph data from a .txt file and stores it in an adjacency matrix (as a 2D boolean array), and returns it.
    It is assumed that the file is of valid format, i.e., the first line contains the number of vertices and edges, and the subsequent lines contain the edges.
    The adjacency matrix is a square matrix where the number of rows and columns is equal to the number of vertices in the social graph.
    
    By Aaron Barcelita.
*/
bool** loadAdjMatrix(char *fileString, int *numVertices, int *numEdges)
{
    FILE *fp;
    int i, j, ID1, ID2, status;

    //open the file, check if it exists (assumes that file is of valid format)
    fp = fopen(fileString, "r");
    if (fp == NULL) {
        printf("File not found. Please try again.\n");
        return NULL;
    } else {
        printf("File found. Now loading...\n");
    }

    //next, read the first line of the file which contains the number of vertices and edges
    fscanf(fp, "%d %d", numVertices, numEdges);
    bool **adjMatrix = malloc(*numVertices * sizeof(bool*));
    if (adjMatrix == NULL) { //if memory allocation fails, free all previously allocated memory and terminate the program
        printf("Memory allocation for adjacency matrix has failed. Terminating program...\n");
        free(adjMatrix);
        fclose(fp);
        exit(-1);
    }

    //allocate memory for each row of the adjacency matrix
    for (i = 0; i < *numVertices; i++) {
        adjMatrix[i] = calloc(*numVertices, sizeof(bool));
        if (adjMatrix[i] == NULL) { //if memory allocation fails, free all previously allocated memory and terminate the program
            printf("Memory allocation for adjacency matrix has failed. Terminating program...\n");
            for (j = 0; j < i; j++) {
                free(adjMatrix[j]);
            }
            free(adjMatrix);
            fclose(fp);
            exit(-1);
        }
    }

    //read the subsequent lines of the file which contain the edges and set the corresponding elements in the adjacency matrix to true
    while (fscanf(fp, "%d %d", &ID1, &ID2) == 2) {
        adjMatrix[ID1][ID2] = true;
    }

    fclose(fp);
    return adjMatrix; //return the adjacency matrix
}

/*
    This function checks if an edge exists between two vertices in the social graph represented by an adjacency matrix.
    It returns true if an edge exists between the two vertices, and false otherwise.
    Also returns false when the IDs are invalid or when they are the same.
    
    By Aaron Barcelita.
*/
bool hasEdge_AdjMatrix(bool** adjMatrix, int numVertices, int ID1, int ID2)
{
    if ((ID1 < 0 || ID1 >= numVertices) || (ID2 < 0 || ID2 >= numVertices) || ID1 == ID2) {
        return false;
    }
    return adjMatrix[ID1][ID2] && adjMatrix[ID2][ID1];
}

/*
    Prints the adjacency matrix of the social graph. 1 if true, 0 if false.
    Used for testing purposes.
*/
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

/*
    This function prints the friend list of a given ID in the social graph represented by an adjacency matrix.
    It prints the IDs of the friends of the given ID.
    
    By Aaron Barcelita.
*/
void printFriendList_adjMatrix(bool **adjMatrix, int numVertices, int ID1) 
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
    printf("\n%d's Friend Count: %d\n", ID1, friendCount);
}


/*
    This function is an implementation of the BFS algorithm to determine whether if a connection exists between two IDs 
    in the social graph that is implemented as an adjacency matrix.
    Returns an array of integers that represents the path between the two IDs if a connection is found, and NULL otherwise.

    By Aaron Barcelita.
*/
int* findConnections_BFS_AdjMatrix(bool** adjMatrix, int numVertices, int ID1, int ID2, int* pathLength)
{
    if (ID1 < 0 || ID1 >= numVertices || ID2 < 0 || ID2 >= numVertices || ID1 == ID2) {
        return NULL;
    }

    int i, j, currentIndex;
    bool connectionFound = false;

    //create a parent array of size numVertices to store the parent of each vertex
    int* parentVertices =  malloc(numVertices * sizeof(int));
    if (parentVertices == NULL) {
        printf("Memory allocation for parentVertices has failed. Terminating program...\n");
        exit(-1);
    }
    memset(parentVertices, -1, numVertices * sizeof(int)); //set all elements to -1

    //create a visited array of size numVertices to keep track of visited vertices
    bool* visitedVertices = calloc(numVertices, sizeof(bool));
    if (visitedVertices == NULL) {
        printf("Memory allocation for visitedVertices has failed. Terminating program...\n");
        free(parentVertices);
        free(visitedVertices);
        exit(-1);
    }

    //create a priority queue to store the vertices to be visited, is used to prioritize lower value nodes
    PriorityQueue *priorityQueue = createPriorityQueue(); //check data_structures.c for the implementation of the priority queue and its operations
    if (priorityQueue == NULL) {
        printf("Memory allocation for priorityQueue has failed. Terminating program...\n");
        free(parentVertices);
        free(visitedVertices);
        freePriorityQueue(priorityQueue);
        exit(-1);
    }

    //initialize the search by visiting the starting vertex and enqueueing it
    visitedVertices[ID1] = true;
    enqueue(priorityQueue, ID1);

    while (!isEmptyQueue(priorityQueue)) {
        currentIndex = dequeue(priorityQueue); //dequeue the front of the priority queue
        if (currentIndex == ID2) {
            connectionFound = true;
            break;
        }
        //visit all the adjacent vertices of the current vertex
        for (i = 0; i < numVertices; i++) {
            if (hasEdge_AdjMatrix(adjMatrix, numVertices, i, currentIndex) && !visitedVertices[i]) {
                visitedVertices[i] = true; //mark the vertex as visited
                parentVertices[i] = currentIndex; //set the parent of the vertex
                enqueue(priorityQueue, i); //enqueue the vertex
            }
        }
    }
    
    if (!connectionFound) {
        free(parentVertices);
        free(visitedVertices);
        free(priorityQueue);
        return NULL; //if no connection is found, return NULL
    }

    /*
        Reconstruct the path from the destination vertex to the source vertex using the parent array.
        The path is stored in an array of integers, and the length of the path is stored in the pathLength variable.
        There is a need to trace back from ID2 to ID1 to determine the path because we only keep track of the parent of each vertex.
    */
    *pathLength = 0;
    for (i = ID2; i != -1; i = parentVertices[i]) {
        (*pathLength)++; //count the number of vertices in the path
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
    for (j = *pathLength - 1; j >= 0; j--) { //store the path in reverse order
        path[j] = i; //store the current vertex in the path array
        i = parentVertices[i]; //move to the parent vertex
    }

    free(parentVertices);
    free(visitedVertices);
    freePriorityQueue(priorityQueue);
    return path; //return the path
}

/*
    This function is a nonrecursive implementation of the DFS algorithm to determine whether if a connection exists between two IDs 
    in the social graph that is implemented as an adjacency matrix.
    Returns an array of integers that represents the path between the two IDs if a connection is found, and NULL otherwise.

    By Aaron Barcelita.
*/
int* findConnections_DFS_AdjMatrix(bool** adjMatrix, int numVertices, int ID1, int ID2, int* pathLength)
{
    if (ID1 < 0 || ID1 >= numVertices || ID2 < 0 || ID2 >= numVertices || ID1 == ID2) { //if the IDs are invalid or the same, return NULL
        return NULL;
    }

    int i, j, currentVertex;
    bool connectionFound = false;

    int* parentVertices = malloc(numVertices * sizeof(int));
    if (parentVertices == NULL) {
        printf("Memory allocation for parentVertices has failed. Terminating program...\n");
        exit(-1);
    }
    memset(parentVertices, -1, numVertices * sizeof(int)); //set all elements to -1

    bool* visitedVertices = calloc(numVertices, sizeof(bool));
    if (visitedVertices == NULL) {
        printf("Memory allocation for visitedVertices has failed. Terminating program...\n");
        free(parentVertices);
        exit(-1);
    }

    Stack *stack = createStack(); //check data_structures.c for the implementation of the stack and its operations
    if (stack == NULL) {
        printf("Memory allocation for stack has failed. Terminating program...\n");
        free(parentVertices);
        free(visitedVertices);
        exit(-1);
    }

    //initialize the search by visiting the starting vertex and pushing it onto the stack
    push(stack, ID1);
    visitedVertices[ID1] = true;

    while(!isEmptyStack(stack)) {
        currentVertex = pop(stack); //pop the top of the stack
        if (currentVertex == ID2) {
            connectionFound = true;
            break;
        }
        //visit all the adjacent vertices of the current vertex
        for(i = 0; i < numVertices; i++) {
            if (hasEdge_AdjMatrix(adjMatrix, numVertices, i, currentVertex) && !visitedVertices[i]) {
                visitedVertices[i] = true; //mark the vertex as visited
                parentVertices[i] = currentVertex; //set the parent of the vertex
                push(stack, i); //push the vertex onto the stack
            }
        }
    }

    if (!connectionFound) { //if no connection is found, free the memory and return NULL
        free(parentVertices);
        free(visitedVertices);
        freeStack(stack);
        return NULL;
    }

    /*
        Reconstruct the path from the destination vertex to the source vertex using the parent array.
        The path is stored in an array of integers, and the length of the path is stored in the pathLength variable.
        There is a need to trace back from ID2 to ID1 to determine the path because we only keep track of the parent of each vertex.
    */
    *pathLength = 0;
    for (i = ID2; i != -1; i = parentVertices[i]) {
        (*pathLength)++; //count the number of vertices in the path
    }

    int* path = malloc(*pathLength * sizeof(int));
    if (path == NULL) {
        printf("Memory allocation for path has failed. Terminating program...\n");
        free(parentVertices);
        free(visitedVertices);
        freeStack(stack);
        exit(-1);
    }

    i = ID2;
    for(j = *pathLength - 1; j >= 0; j--) { //store the path in reverse order
        path[j] = i; //store the current vertex in the path array
        i = parentVertices[i]; //move to the parent vertex
    }

    free(parentVertices);
    free(visitedVertices);
    freeStack(stack);
    return path; //return the path
}

/*
    This functions allows us to free the memory dynamically allocated for the adjacency matrix and its contents to prevent memory leaks.

    By Aaron Barcelita.
*/
void freeAdjMatrix(bool** adjMatrix, int numVertices)
{
    int i;
    for (i = 0; i < numVertices; i++) { //this method of freeing is due to how I allocated the memory for the adjacency matrix in loadAdjMatrix
        free(adjMatrix[i]);
    }
    free(adjMatrix);
    printf("Memory dynamically allocated for the adjacency matrix and its contents has been freed.\n");
}  