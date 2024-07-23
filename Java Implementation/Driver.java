import java.util.*; 
import java.io.*; 

public class Driver {
    public static void main(String[] args) {
        int choice = 0, graphChoice = 0, searchChoice = 0;
        int ID1, ID2;
        boolean fileFound = false, isValid_ID1, isValid_ID2;
        String fileString = "";
        File file;
        Scanner sc = new Scanner(System.in);
        AdjacencyMatrix adjacencyMatrix = null;
        AdjacencyList adjacencyList = null;
        List<Integer> connection = new ArrayList<Integer>();

        /*
            This part of the code asks for the file path or file name of the .txt file containing the social graph data.
            It only considers the scenarios whether if the file is not found, OR if the file is found and IS of valid format.
            Using a .txt file of invalid format will not be considered in this part of the code, and will therefore lead to undefined behavior.
        */
        while (fileFound == false) {
            System.out.println("\n\t==== LOAD GRAPH DATA ====\n");
            System.out.println("Please indicate the ABSOLUTE file path or file name of the .txt file containing the social graph data.");
            System.out.print("If entering file name, ensure that the file is in the same directory as this program.\n");
            System.out.print("Enter file connection or file name: ");
            fileString = sc.nextLine();

            file = new File(fileString);
            if(file.exists() && !file.isDirectory()) { //if file exists and is not a directory
                System.out.println("File found.");
                fileFound = true;
            } else {
                System.out.println("File not found. Please try again.");
            }
        }

        /*
            This part of the code asks the user to choose the format of the social graph.
            The user can choose between an adjacency list or an adjacency matrix.
            The program will only proceed if the user chooses a valid option, i.e., 1 or 2.
        */
        while (graphChoice != 1 && graphChoice != 2) {
            System.out.println("\n\t==== CHOOSING A GRAPH FORMAT ====\n");
            System.out.println("Please choose the format of the social graph.");
            System.out.println("[1] Adjacency List.");
            System.out.println("[2] Matrix.\n");
            System.out.print("Enter choice: ");
            
            try {
                graphChoice = Integer.parseInt(System.console().readLine());
            } catch (NumberFormatException e) {
                System.out.println("Invalid input type. Please try again.");
                continue;
            }

            switch(graphChoice) {
                case 1:
                    adjacencyList = new AdjacencyList();
                    adjacencyList.loadFromFile(fileString);
                    // adjacencyList.printGraph();
                    break;
                case 2:
                    adjacencyMatrix = new AdjacencyMatrix();
                    adjacencyMatrix.loadFromFile(fileString);
                    // adjacencyMatrix.printGraph();
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }

        /*
            This part of the code is the main menu of the program.
            User can choose between different functionalities to perform on the social graph data.
        */
        while (choice != 3) {
            System.out.println("\n\t==== MAIN MENU ====\n");
            System.out.printf("The graph is of format: %s.\n", graphChoice == 1 ? "Adjacency List" : "Adjacency Matrix");
            System.out.println("[1] Display friend list.");
            System.out.println("[2] Display connections.");
            System.out.println("[3] Exit.\n");
            System.out.print("Enter choice: ");
            
            try {
                choice = Integer.parseInt(System.console().readLine());
            } catch (NumberFormatException e) {
                System.out.println("Invalid input type. Please try again.");
                continue;
            }

            switch (choice) {
                case 1:
                    System.out.println("Enter a ID number from 0 to " + (graphChoice == 1 ? adjacencyList.getNumVertices() - 1 : adjacencyMatrix.getNumVertices() - 1) + ": ");
                    try { //checks if ID1 is within the range of the number of vertices
                        ID1 = Integer.parseInt(System.console().readLine());
                        if ((ID1 < 0 ||  ID1 >= (graphChoice == 1 ? adjacencyList.getNumVertices() : adjacencyMatrix.getNumVertices()))) { //if ID1 is not within the range
                            System.out.println("Invalid ID. Please enter a valid ID within the range.");
                            break;
                        }
                    } catch (NumberFormatException e) { //happens when the input is not an integer
                        System.out.println("Invalid input type. Please try again.");
                        break;
                    }
                    if (graphChoice == 1) {
                        adjacencyList.printFriendList(ID1);
                    } else if (graphChoice == 2) {
                        adjacencyMatrix.printFriendList(ID1);
                    }
                    break;
                case 2:
                    System.out.println();
                    System.out.println("Enter two ID numbers that range from 0 to " + (graphChoice == 1 ? adjacencyList.getNumVertices() - 1 : adjacencyMatrix.getNumVertices() - 1) + ".");
                    System.out.println("These 2 IDs must also be different from each other.");
                    try { //checks if ID1 and ID2 are within the range of the number of vertices
                        System.out.print("Enter ID number 1: ");
                        ID1 = Integer.parseInt(System.console().readLine());
                        System.out.print("Enter ID number 2: ");
                        ID2 = Integer.parseInt(System.console().readLine());
                        
                        //checks if ID1 and ID2 are within the range of the number of vertices
                        isValid_ID1 = ID1 >= 0 && ID1 < (graphChoice == 1 ? adjacencyList.getNumVertices() : adjacencyMatrix.getNumVertices());
                        isValid_ID2 = ID2 >= 0 && ID2 < (graphChoice == 1 ? adjacencyList.getNumVertices() : adjacencyMatrix.getNumVertices());

                        if (!isValid_ID1 || !isValid_ID2 || ID1 == ID2) { //if ID1 and/or ID2 are not within the range or if they are the same
                            System.out.println("Invalid ID/s. Please enter valid ID/s within the range.");
                            break;
                        }
                    } catch (NumberFormatException e) { //happens when the input is not an integer
                        System.out.println("Invalid input type. Please try again.");
                        break;
                    }

                    System.out.println();
                    System.out.println("Choose between BFS or DFS for the search method.");
                    System.out.println("[1] Breadth First Search.");
                    System.out.println("[2] Depth First Search.");
                    System.out.print("Enter choice: ");
                    try {
                        searchChoice = Integer.parseInt(System.console().readLine());
                    } catch (NumberFormatException e) {
                        System.out.println("Invalid input type. Please try again."); //happens when the input is not an integer
                        break;
                    }

                    switch(searchChoice) {
                        case 1:
                            System.out.printf("\nPerforming BFS on the graph from %d to %d...\n", ID1, ID2);
                            connection = graphChoice == 1 ? adjacencyList.findConnections_BFS(ID1, ID2) : adjacencyMatrix.findConnections_BFS(ID1, ID2); //finds the connection between ID1 and ID2
                            if (connection != null && !connection.isEmpty()) {
                                System.out.printf("A CONNECTION BETWEEN %d AND %d EXISTS!\n", ID1, ID2);
                                if (graphChoice == 1) {
                                    adjacencyList.printPath(connection);
                                } else {
                                    adjacencyMatrix.printPath(connection);
                                }
                                System.out.println();
                            } else {
                                System.out.printf("No connection between %d and %d.\n", ID1, ID2);
                            }
                            break;
                        case 2:
                            System.out.printf("Performing DFS on the graph from %d to %d...\n", ID1, ID2);
                            connection = graphChoice == 1 ? adjacencyList.findConnections_DFS(ID1, ID2) : adjacencyMatrix.findConnections_DFS(ID1, ID2);
                            if (connection != null && !connection.isEmpty()) {
                                System.out.printf("A CONNECTION BETWEEN %d AND %d EXISTS!\n", ID1, ID2);
                                if (graphChoice == 1) {
                                    adjacencyList.printPath(connection);
                                } else {
                                    adjacencyMatrix.printPath(connection);
                                }
                                System.out.println();
                            } else {
                                System.out.printf("No connection between %d and %d.\n", ID1, ID2);
                            }
                            break;
                        default:
                            System.out.println("Invalid choice. Please try again.");
                    }

                    break;
                
                case 3:
                    System.out.println("Exiting program...");
                    System.exit(0);
                    break;
            }
        }
        sc.close();
    }
}