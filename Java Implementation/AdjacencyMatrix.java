import java.util.*;
import java.io.*;

public class AdjacencyMatrix {
    private boolean adjacencyMatrix[][];
    private int numVertices;
    private int numEdges; //num of edges according to file

    public AdjacencyMatrix() {
        this.numVertices = 0;
        this.numEdges = 0;
        this.adjacencyMatrix = null;
    }
    
    public int getNumVertices (){
        return this.numVertices;
    } 

    public boolean hasEdge(int i, int j) {
        // Check if i and j are within the bounds of the matrix
        if (i >= 0 && i < adjacencyMatrix.length && j >= 0 && j < adjacencyMatrix[i].length) {
            return adjacencyMatrix[i][j] && adjacencyMatrix[j][i];
        } else {
            // Return false or handle the error appropriately if i or j are out of bounds
            return false;
        }
    }

    public void loadFromFile(String fileString) { //fileString is either file connection or file name
        int i, j;
        Scanner sc;
        String[] parts, edge;
        
        try {
            sc = new Scanner(new File(fileString));
            
            if (sc.hasNextLine()) {
                parts = sc.nextLine().split(" ");
                this.numVertices = Integer.parseInt(parts[0]);
                this.numEdges = Integer.parseInt(parts[1]);
                this.adjacencyMatrix = new boolean[numVertices][numVertices];
            }

            while (sc.hasNextLine() == true) {
                edge = sc.nextLine().split(" ");
                i = Integer.parseInt(edge[0]);
                j = Integer.parseInt(edge[1]);
                adjacencyMatrix[i][j] = true;
                // adjacencyMatrix[j][i] = true;
            }
            System.out.printf("File loaded successfully. Matrix Graph has %d vertices and %d edges.\n\n", this.numVertices, this.numEdges);
            sc.close();
        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + fileString);
        }
    }

    public void printAdjacencyMatrix() { //for testing purposes with smaller graphs
        int i, j;

        System.out.println("\n\t==== ADJACENCY MATRIX ====\n");
        for (i = 0; i < numVertices; i++) {
            for (j = 0; j < numVertices; j++) {
                if (adjacencyMatrix[i][j] == true) {
                    System.out.print("1 ");
                } else {
                    System.out.print("0 ");
                }
            }
            System.out.println();
        }
        System.out.println();
    }

    public void printFriendList(int ID1) { //ID1's friends are the nodes adjacent to it
        int i, friendCount = 0;

        System.out.printf("\n\t==== %d's FRIEND LIST ====\n\n", ID1);
        for (i = 0; i < this.numVertices; i++) {
            if (hasEdge(ID1, i)) {
                System.out.printf("%d\n", i);
                friendCount++;
            }
        }
        System.out.printf("\n\n%d's Friend Count: %d\n", ID1, friendCount);
    }

    //queue is implemented using a priority queue
    public List<Integer> findConnections_BFS(int ID1, int ID2) {
        // first, validate ID inputs
        if (ID1 < 0 || ID1 >= this.numVertices || ID2 < 0 || ID2 >= this.numVertices || ID1 == ID2) {
            System.out.printf("Invalid ID/s. The range of an ID should be from 0 to " + (this.numVertices - 1) + " inclusive.\nThe two IDs should also not be the same.\n\n");
            return null;
        }

        int i, currentVertex;
        boolean connectionFound = false;
        PriorityQueue<Integer> queue = new PriorityQueue<>(); //this declaration w/o defining a custom comparator ensures NATURAL ORDERING (lower value node has higher priority)
        boolean visitedVertices[] = new boolean[this.numVertices]; // keeps track of visited vertices
        int[] parent = new int[this.numVertices]; // keeps track of the parent of each vertex
        Arrays.fill(parent, -1); // initialize all elements of parent to -1 since at the start, we do not know yet the parent of each vertex

        //mark the first vertex as visited and enqueue it
        visitedVertices[ID1] = true;
        queue.add(ID1);

        // process the vertices in the queue until queue is empty or connection is found
        while (!queue.isEmpty()) {
            currentVertex = queue.poll(); // dequeue the vertex at the front of the queue
            if (currentVertex == ID2) {
                connectionFound = true;
                break; // exit the loop if the currentVertex is equal to ID2
            }

            // Explore unvisited neighboring vertices of the current vertex
            for (i = 0; i < this.numVertices; i++) {
                if (this.hasEdge(i, currentVertex) && !visitedVertices[i]) {
                    visitedVertices[i] = true;
                    parent[i] = currentVertex;
                    queue.add(i);
                }
            }
        }

        // if no connection is found between ID1 and ID2, display an error message
        if (!connectionFound) {
            System.out.printf("No connection found between IDs %d and %d.\n", ID1, ID2);
            return Collections.emptyList();
        }

        // if a connection is found, reconstruct the path from ID1 to ID2 and display it
        List<Integer> connection = new ArrayList<Integer>();
        for (i = ID2; i != -1; i = parent[i]) {
            connection.add(i);
        }
        Collections.reverse(connection); //reverse the connection list to make it from ID1 to ID2 instead of ID2 to ID1
        return connection;
    }
}
