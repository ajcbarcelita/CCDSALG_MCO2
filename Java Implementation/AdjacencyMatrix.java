import java.util.*;
import java.io.*;

public class AdjacencyMatrix {
    private boolean adjacencyMatrix[][];
    private int numVertices;
    private int numEdges;
    private int edgeCount;

    public AdjacencyMatrix() {
        this.numVertices = 0;
        this.numEdges = 0;
        this.edgeCount = 0;
        this.adjacencyMatrix = null;
    }

    public int getNumVertices() {
        return numVertices;
    }

    public int getNumEdges() {
        return numEdges;
    }

    public boolean hasEdge(int i, int j) {
        return adjacencyMatrix[i][j];
    }

    public void loadFromFile(String fileString) { //fileString is either file path or file name
        try {
            Scanner sc = new Scanner(new File(fileString));
            
            if (sc.hasNextLine()) {
                String[] parts = sc.nextLine().split(" ");
                this.numVertices = Integer.parseInt(parts[0]);
                this.numEdges = Integer.parseInt(parts[1]);
                this.adjacencyMatrix = new boolean[numVertices][numVertices];
            }

            while (sc.hasNextLine() == true) {
                String[] edge = sc.nextLine().split(" ");
                int i = Integer.parseInt(edge[0]);
                int j = Integer.parseInt(edge[1]);
                if (!adjacencyMatrix[i][j]) {
                    edgeCount += 2;
                }
                adjacencyMatrix[i][j] = true;
                adjacencyMatrix[j][i] = true;
            }
            System.out.printf("Edge count (according to file): %d\nEdge count (according to func): %d\n", numEdges, edgeCount);
            sc.close();
        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + fileString);
        }
    }

    public void printAdjacencyMatrix() {
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
            if (adjacencyMatrix[ID1][i] == true) {
                System.out.printf("%d ", i);
                friendCount++;
            }
        }
        System.out.printf("\n\n%d's Friend Count: %d\n", ID1, friendCount);
    }

    public void printConnections(int ID1, int ID2) {

    }
}
