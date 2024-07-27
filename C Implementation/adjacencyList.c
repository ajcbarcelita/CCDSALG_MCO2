#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include "data_structures.h"

/*
    This function loads the social graph data from a .txt file and stores it in an adjacency list implemented as an array of singly linked lists.
    It is assumed that the file is of valid format, i.e., the first line contains the number of vertices and edges, and the subsequent lines contain the edges.
    Specifically, this array of singly linked lists is implemented as an array of singlyNode pointers, where each singlyNode pointer points to the head of a singly linked list.
    
    By Aaron Barcelita.
*/
singlyNode** loadAdjacencyList(char *fileString, int *numVertices, int *numEdges) {
    FILE *fp;
    int i, j, ID1, ID2, status;

    //open the file
    fp = fopen(fileString, "r");
    if (fp == NULL) {
        printf("File not found. Please try again.\n");
        return NULL;
    } else {
        printf("File found. Now loading...\n");
    }

    //read the number of vertices and edges
    fscanf(fp, "%d %d", numVertices, numEdges);
    singlyNode **adjList = malloc(*numVertices * sizeof(singlyNode*));
    if (adjList == NULL) {
        printf("Memory allocation for adjacency list has failed. Terminating program...\n");
        free(adjList);
        fclose(fp);
        exit(-1);
    }

    //initialize the adjacency list
    for (i = 0; i < *numVertices; i++) {
        adjList[i] = NULL;
    }

    //read the edges
    while (fscanf(fp, "%d %d", &ID1, &ID2) == 2) {
        insertAtEnd(&adjList[ID1], ID2); //check data_structures.c for the implementation of insertAtEnd
    }

    fclose(fp);
    return adjList;
}

/*
    This function checks if there is an edge between two vertices in an adjacency list implemented as an array of singly linked lists.
    It returns true if there is an edge between the two vertices, and false otherwise.
    
    By Aaron Barcelita.
*/
bool hasEdge_AdjList(singlyNode** adjList, int numVertices, int ID1, int ID2) {
    if ((ID1 < 0 || ID1 >= numVertices) || (ID2 < 0 || ID2 >= numVertices) || ID1 == ID2) {

        return false;
    }

    bool found1 = false, found2 = false;

    singlyNode *temp = adjList[ID1];
    while (temp != NULL) {
        if (temp->data == ID2) {
            found1 = true;
        }
        temp = temp->nextNode;
    }

    temp = adjList[ID2];
    while (temp != NULL) {
        if (temp->data == ID1) {
            found2 = true;
        }
        temp = temp->nextNode;
    }
    return found1 && found2;
}

/*
    This function prints the adjacency list implemented as an array of singly linked lists.
    Used for testing purposes.
    
    By Aaron Barcelita.
*/
void printAdjList(singlyNode** adjList, int numVertices) {
    int i;
    singlyNode *temp;
    for (i = 0; i < numVertices; i++) {
        temp = adjList[i];
        printf("%d: ", i);
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->nextNode;
        }
        printf("\n");
    }
}

/*
    This function prints the friend list of a certain ID in an adjacency list implemented as an array of singly linked lists.
    It prints the friends of the specified ID.
    
    By Aaron Barcelita.
*/
void printFriendList_AdjList(singlyNode** adjList, int numVertices, int ID1) {
    if (ID1 < 0 || ID1 >= numVertices) {
        printf("Invalid ID. ID should be a value between 0 to %d. Please try again.\n", numVertices - 1);
        return;
    }
    int i = 0;
    singlyNode *temp = adjList[ID1];
    printf("\n\t=== %d's FRIEND LIST ===\n", ID1);
    while (temp != NULL) {
        printf("%d\n", temp->data);
        temp = temp->nextNode;
        i++;
    }
    printf("\n%d's Friend Count: %d\n", ID1, i); //check data_structures.c for the implementation of countNodes
}

/*
    This function is an implementation of the BFS algorithm to determine whether if a connection exists between two IDs 
    in the social graph that is implemented as an adjacency list.
    Returns an array of integers that represents the path between the two IDs if a connection is found, and NULL otherwise.

    By Aaron Barcelita.
*/
int* findConnections_BFS_AdjList(singlyNode** adjList, int numVertices, int ID1, int ID2, int *pathLength) {
    if (ID1 < 0 || ID1 >= numVertices || ID2 < 0 || ID2 >= numVertices || ID1 == ID2) {
        return NULL;
    }

    int i, j, currentIndex;
    bool connectionFound = false;

    int* parentVertices =  malloc(numVertices * sizeof(int));
    if (parentVertices == NULL) {
        printf("Memory allocation for parentVertices has failed. Terminating program...\n");
        free(parentVertices);
        exit(-1);
    }
    memset(parentVertices, -1, numVertices * sizeof(int));

    bool* visitedVertices = calloc(numVertices, sizeof(bool));
    if (visitedVertices == NULL) {
        printf("Memory allocation for visitedVertices has failed. Terminating program...\n");
        free(parentVertices);
        free(visitedVertices);
        exit(-1);
    }

    //initialize the priority queue
    PriorityQueue *priorityQueue = createPriorityQueue(); //check data_structures.c for the implementation of PriorityQueue and its operations
    if (priorityQueue == NULL) {
        printf("Memory allocation for priorityQueue has failed. Terminating program...\n");
        free(parentVertices);
        free(visitedVertices);
        freePriorityQueue(priorityQueue);
        exit(-1);
    }

    visitedVertices[ID1] = true;
    enqueue(priorityQueue, ID1);

    while (!isEmptyQueue(priorityQueue)) {
        currentIndex = dequeue(priorityQueue); //dequeue the front element
        if (currentIndex == ID2) {
            connectionFound = true;
            break;
        }
        for (i = 0; i < numVertices; i++) { //enqueue the adjacent vertices
            if (hasEdge_AdjList(adjList, numVertices, i, currentIndex) && !visitedVertices[i]) { //check if there is an edge between the two vertices
                visitedVertices[i] = true; //mark the vertex as visited
                parentVertices[i] = currentIndex; //set the parent of the vertex
                enqueue(priorityQueue, i); //enqueue the vertex
            }
        }
    }
    
    if (!connectionFound) { //return NULL if no connection is found
        free(parentVertices);
        free(visitedVertices);
        free(priorityQueue);
        return NULL;
    }

    /*
        Reconstruct the path from the destination vertex to the source vertex using the parent array.
        The path is stored in an array of integers, and the length of the path is stored in the pathLength variable.
        There is a need to trace back from ID2 to ID1 to determine the path because we only keep track of the parent of each vertex.
    */
    *pathLength = 0;
    for (i = ID2; i != -1; i = parentVertices[i]) {
        (*pathLength)++; //increment the path length
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
    for (j = *pathLength - 1; j >= 0; j--) { //store the path in the array
        path[j] = i; //store the vertex in the array
        i = parentVertices[i]; //move to the parent vertex
    }

    free(parentVertices);
    free(visitedVertices);
    freePriorityQueue(priorityQueue);
    return path;
}

/*
    This function is a nonrecursive implementation of the DFS algorithm to determine whether if a connection exists between two IDs 
    in the social graph that is implemented as an adjacency list.
    Returns an array of integers that represents the path between the two IDs if a connection is found, and NULL otherwise.

    By Aaron Barcelita.

*/
int* findConnections_DFS_AdjList(singlyNode** adjList, int numVertices, int ID1, int ID2, int* pathLength) {
    if (ID1 < 0 || ID1 >= numVertices || ID2 < 0 || ID2 >= numVertices || ID1 == ID2) {
        return NULL;
    }
    
    bool connectionFound = false;
    int* parentVertices = malloc(numVertices * sizeof(int));

    if (parentVertices == NULL) {
        printf("Memory allocation for parentVertices has failed. Terminating program...\n");
        free(parentVertices);
        exit(-1);
    }
    memset(parentVertices, -1, numVertices * sizeof(int)); //initialize the parent array

    bool* visitedVertices = calloc(numVertices, sizeof(bool));
    if (visitedVertices == NULL) {
        printf("Memory allocation for visitedVertices has failed. Terminating program...\n");
        free(parentVertices);
        free(visitedVertices);
        exit(-1);
    }

    Stack* stack = createStack(); //check data_structures.c for the implementation of Stack and its operations
    if (stack == NULL) {
        printf("Memory allocation for stack has failed. Terminating program...\n");
        free(parentVertices);
        free(visitedVertices);
        freeStack(stack);
        exit(-1);
    }

    //push the source vertex to the stack and mark it as visited
    push(stack, ID1);
    visitedVertices[ID1] = true;

    while(!isEmptyStack(stack)) {
        int currentVertex = pop(stack); //pop the top element
        if (currentVertex == ID2) {
            connectionFound = true;
            break;
        }

        singlyNode* temp = adjList[currentVertex]; //traverse the adjacency list of the current vertex
        for (int i = 0; i < numVertices; i++) { //push the adjacent vertices to the stack
            if (hasEdge_AdjList(adjList, numVertices, i, currentVertex) && !visitedVertices[i]) {
                visitedVertices[i] = true; //mark the vertex as visited
                parentVertices[i] = currentVertex; //set the parent of the vertex
                push(stack, i); //push the vertex to the stack
            }
        }
    }

    //return NULL if no connection is found
    if (!connectionFound) {
        free(parentVertices);
        free(visitedVertices);
        freeStack(stack);
        return NULL;
    }

    *pathLength = 0;
    for (int i = ID2; i != -1; i = parentVertices[i]) {
        (*pathLength)++; //increment the path length
    }

    int* path = malloc(*pathLength * sizeof(int));
    if (path == NULL) {
        printf("Memory allocation for path has failed. Terminating program...\n");
        free(parentVertices);
        free(visitedVertices);
        freeStack(stack);
        exit(-1);
    }

    int i = ID2;
    for (int j = *pathLength - 1; j >= 0; j--) { //store the path in the array
        path[j] = i; //store the vertex in the array
        i = parentVertices[i]; //move to the parent vertex
    }

    free(parentVertices);
    free(visitedVertices);
    freeStack(stack);
    return path;
}

/*
    This functions allows us to free the memory dynamically allocated for the adjacency list and its contents.
    Doing so would help prevent memory leaks. Even though memory for this is freed after program termination, this is
    still considered as a good practice.

    By Aaron Barcelita.
*/
void freeAdjacencyList(singlyNode** adjList, int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        freeLinkedList(&adjList[i]); //check data_structures.c for the implementation of freeLinkedList
    }
    free(adjList);
    printf("Memory dynamically allocated for the adjacency list and its contents has been freed.\n");
}