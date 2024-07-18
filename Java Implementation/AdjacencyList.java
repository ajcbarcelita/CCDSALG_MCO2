import java.util.*; //Scanner, Queue and List Interfaces, LinkedList, and Stack Class
import java.io.*; //File Class

public class AdjacencyList {
    private ArrayList<ArrayList<Integer>> adjacencyList;
    private int numVertices;
    private int numEdges;
    

    public AdjacencyList(){
        this.numVertices = 0;
        this.numEdges = 0;
        this.adjacencyList = null;
    }
    
    public int getNumVertices(){
        return this.numVertices;
    }

    public boolean hasEdge(int i, int j) {
        try {
            return adjacencyList.get(i).contains(j) && adjacencyList.get(j).contains(i);
        } catch (IndexOutOfBoundsException e) {
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
                this.adjacencyList = new ArrayList<>();
                for (i = 0; i < this.numVertices; i++) {
                    this.adjacencyList.add(new ArrayList<Integer>());
                }
            }

            while (sc.hasNextLine() == true) {
                edge = sc.nextLine().split(" ");
                i = Integer.parseInt(edge[0]);
                j = Integer.parseInt(edge[1]);
                adjacencyList.get(i).add(j);
                adjacencyList.get(j).add(i);
            }
            System.out.printf("File loaded successfully. List Graph has %d vertices and %d edges.\n\n", this.numVertices, this.numEdges);
            sc.close();
        } catch (FileNotFoundException e) {
            System.out.println("File not found: " + fileString);
        }
    }

    public void printAdjacencyList() { 
        int i, j;
        ArrayList<Integer> list;

        System.out.println("\n\t==== ADJACENCY LIST ====\n");
        for (i = 0; i < adjacencyList.size(); i++) {
            System.out.print(i + ": ");
            list = adjacencyList.get(i);
            for (j = 0; j < list.size(); j++) {
                System.out.printf("%d ", list.get(j));
            }
            System.out.println();
        }
    }

    //using a hashset is more efficient vs arraylist since it has O(1) time complexity for contains() method, a result of the hash function
    public void printFriendList(int ID1) { //ID1's friends are the nodes adjacent to it
        ArrayList<Integer> friendList = adjacencyList.get(ID1);
        HashSet<Integer> printedFriends = new HashSet<Integer>();

        System.out.printf("\n\t==== %d's FRIEND LIST ====\n\n", ID1);
        for (Integer friendID : friendList) {
            if (!printedFriends.contains(friendID)) {
                System.out.printf("%d\n", friendID);
                printedFriends.add(friendID);
            }
        }
        System.out.printf("\n\n%d's Friend Count: %d\n", ID1, printedFriends.size());
    }

    //queue is implemented using LinkedList
    public List<Integer> findConnections_BFS(int ID1, int ID2) {
        // first, validate ID inputs
        if (ID1 < 0 || ID1 >= this.numVertices || ID2 < 0 || ID2 >= this.numVertices || ID1 == ID2) {
            System.out.printf("Invalid ID/s. The range of an ID should be from 0 to " + (this.numVertices - 1) + " inclusive.\nThe two IDs should also not be the same.\n\n");
            return null;
        }

        int i, currentVertex;
        boolean connectionFound = false;
        PriorityQueue<Integer> queue = new PriorityQueue<>(); // stores the vertices to be visited next
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
            for (int neighbor : adjacencyList.get(currentVertex)) {
                if (!visitedVertices[neighbor]) {
                    visitedVertices[neighbor] = true;
                    parent[neighbor] = currentVertex;
                    queue.add(neighbor);
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

    public List<Integer> findConnections_DFS(int ID1, int ID2) {
        // first, validate ID inputs
        if (ID1 < 0 || ID1 >= this.numVertices || ID2 < 0 || ID2 >= this.numVertices || ID1 == ID2) {
            System.out.printf("Invalid ID/s. The range of an ID should be from 0 to " + (this.numVertices - 1) + " inclusive.\nThe two IDs should also not be the same.\n\n");
            return null;
        }

        int i, currentVertex;
        boolean connectionFound = false;
        Stack<Integer> stack = new Stack<>(); // stores the vertices to be visited next
        boolean visitedVertices[] = new boolean[this.numVertices]; // keeps track of visited vertices
        int[] parent = new int[this.numVertices]; // keeps track of the parent of each vertex
        Arrays.fill(parent, -1); // initialize all elements of parent to -1 since at the start, we do not know yet the parent of each vertex

        //mark the first vertex as visited and push it into the stack
        visitedVertices[ID1] = true;
        stack.push(ID1);

        // process the vertices in the stack until stack is empty or connection is found
        while (!stack.isEmpty()) {
            currentVertex = stack.pop(); // pop the vertex at the top of the stack
            if (currentVertex == ID2) {
                connectionFound = true;
                break; // exit the loop if the currentVertex is equal to ID2
            }

            // Explore unvisited neighboring vertices of the current vertex
            for (int neighbor : adjacencyList.get(currentVertex)) {
                if (!visitedVertices[neighbor]) {
                    visitedVertices[neighbor] = true;
                    parent[neighbor] = currentVertex;
                    stack.push(neighbor);
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

