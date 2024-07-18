import java.util.*; //Scanner, List Interface
import java.io.*; //File Class

public class Driver {
    public static void main(String[] args) {
        int i, choice = 0, graphChoice = 0, searchChoice = 0,ID1, ID2;
        boolean fileFound = false;
        String fileString = "";
        File file;
        Scanner sc = new Scanner(System.in);
        AdjacencyMatrix adjacencyMatrix = null;
        AdjacencyList adjacencyList = null;
        List<Integer> connection = new ArrayList<Integer>();

        // This is the main menu of the program.
        // Add a part here that allows the user to import a .txt file containing data for a social graph.
        // If the .txt file is not found, display an error message, BUT not exit the program.
        // If the .txt file is found, display a success message, and prompt the user to choose between an
        // ADJACENCY LIST or MATRIX for the social graph.
        // Choosing either will display the social graph in the chosen format, and will prompt the user to the main menu.

        while (fileFound == false) {
            System.out.println("\n\t==== LOAD GRAPH DATA ====\n");
            System.out.println("Please indicate the ABSOLUTE file path or file name of the .txt file containing the social graph data.");
            System.out.print("If entering file name, ensure that the file is in the same directory as this program.\n");
            System.out.print("Enter file connection or file name: ");
            fileString = sc.nextLine();

            file = new File(fileString);
            if(file.exists() && !file.isDirectory()) {
                System.out.println("File found.");
                fileFound = true;
            } else {
                System.out.println("File not found. Please try again.");
            }
        }

        // Add a part here that allows the user to choose between an ADJACENCY LIST or MATRIX for the social graph.
        while (graphChoice != 1 && graphChoice != 2) {
            System.out.println("\n\t==== CHOOSING A GRAPH FORMAT ====\n");
            System.out.println("Please choose the format of the social graph.");
            System.out.println("[1] Adjacency List.");
            System.out.println("[2] Matrix.\n");
            System.out.print("Enter choice: ");
            
            try {
                graphChoice = Integer.parseInt(System.console().readLine());
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please try again.");
                continue;
            }

            switch(graphChoice) {
                case 1:
                    adjacencyList = new AdjacencyList();
                    adjacencyList.loadFromFile(fileString);
                    // adjacencyList.printAdjacencyList();
                    break;
                case 2:
                    adjacencyMatrix = new AdjacencyMatrix();
                    adjacencyMatrix.loadFromFile(fileString);
                    // adjacencyMatrix.printAdjacencyMatrix();
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }

        //main menu
        while (choice != 3) {
            System.out.println("\n\t==== MAIN MENU ====\n");
            System.out.println("[1] Display friend list.");
            System.out.println("[2] Display connections.");
            System.out.println("[3] Exit.\n");
            System.out.print("Enter choice: ");
            
            try {
                choice = Integer.parseInt(System.console().readLine());
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please try again.");
                continue;
            }

            switch(choice) {
                case 1:
                    /*  
                        This function accepts an ID number as a parameter.
                        If valid, display total number of friends and list of friends.
                        If not, display an error message, BUT not exit the program.
                    */  
                    System.out.print("Enter ID number: ");
                    ID1 = Integer.parseInt(System.console().readLine());
                    if (ID1 < 0 || (graphChoice == 1 && ID1 >= adjacencyList.getNumVertices()) || (graphChoice == 2 && ID1 >= adjacencyMatrix.getNumVertices())) {
                        System.out.println("Invalid ID. Please enter a valid ID within the range.");
                        break;
                    }
                    if (graphChoice == 1) {
                        adjacencyList.printFriendList(ID1);
                    } else if (graphChoice == 2) {
                        adjacencyMatrix.printFriendList(ID1);
                    }
                    
                    break;
                case 2:
                    /*
                        This function accepts 2 different ID numbers as parameters.
                        If both ID numbers exist, display the connection/connection between the two, i.e, ID1 is friends with c1, until c(n-1) is friends with ID2.
                        
                        Note: 
                        - A connection is a sequence from ID1, c1, c2, ..., ID2 such that ID1 is friends with c1, 
                        c1 is friends with c2, ..., and c(n-1) is friends with ID2.

                        If any/both ID numbers does not exist, display an error message, BUT not exit the program.
                    */
                    System.out.print("Enter ID number 1: ");
                    ID1 = Integer.parseInt(System.console().readLine());
                    System.out.print("Enter ID number 2: ");
                    ID2 = Integer.parseInt(System.console().readLine());
                    System.out.println("\nChoose the search method: ");
                    System.out.println("[1] Breadth First Search.");
                    System.out.println("[2] Depth First Search.");
                    System.out.print("\nEnter choice: ");
                    searchChoice = Integer.parseInt(System.console().readLine());
                    if (graphChoice == 1) {
                        if (searchChoice == 1) {
                            System.out.printf("\nPerforming BFS on the graph from %d to %d...\n", ID1, ID2); //change
                            connection = adjacencyList.findConnections_BFS(ID1, ID2);
                            if (connection != null && !connection.isEmpty()) {
                                System.out.printf("A connection from IDs %d to %d EXISTS!\n", ID1, ID2);
                                for (i = 0; i < connection.size() - 1; i++) {
                                    System.out.printf("%d is friends with %d.\n", connection.get(i), connection.get(i + 1));
                                }
                                System.out.println();
                            } else {
                                System.out.printf("No connection from IDs %d to %d.\n", ID1, ID2);
                            }
                        } else if (searchChoice == 2) {
                            System.out.printf("\nPerforming DFS on the graph from %d to %d...\n", ID1, ID2);
                            connection = adjacencyList.findConnections_DFS(ID1, ID2);
                            if (connection != null && !connection.isEmpty()) {
                                System.out.printf("A connection from IDs %d to %d EXISTS!\n", ID1, ID2);
                                for (i = 0; i < connection.size() - 1; i++) {
                                    System.out.printf("%d is friends with %d.\n", connection.get(i), connection.get(i + 1));
                                }
                                System.out.println();
                            } else {
                                System.out.printf("No connection from IDs %d to %d.\n", ID1, ID2);
                            }
                        }
                    } else if (graphChoice == 2) {
                        if (searchChoice == 1) {
                            System.out.printf("\nPerforming BFS on the graph from %d to %d...\n", ID1, ID2);
                            connection = adjacencyMatrix.findConnections_BFS(ID1, ID2);
                            if (connection != null && !connection.isEmpty()) {
                                System.out.printf("A connection from IDs %d to %d EXISTS!\n", ID1, ID2);
                                for (i = 0; i < connection.size() - 1; i++) {
                                    System.out.printf("%d is friends with %d.\n", connection.get(i), connection.get(i + 1));
                                }
                                System.out.println();
                            } else {
                                System.out.printf("No connection from IDs %d to %d.\n", ID1, ID2);
                            }
                        } else if (searchChoice == 2) {
                            System.out.printf("\nPerforming DFS on the graph from %d to %d...\n", ID1, ID2);
                            connection = adjacencyMatrix.findConnections_DFS(ID1, ID2);
                            if (connection != null && !connection.isEmpty()) {
                                System.out.printf("A connection from IDs %d to %d EXISTS!\n", ID1, ID2);
                                for (i = 0; i < connection.size() - 1; i++) {
                                    System.out.printf("%d is friends with %d.\n", connection.get(i), connection.get(i + 1));
                                }
                                System.out.println();
                            } else {
                                System.out.printf("No connection from IDs %d to %d.\n", ID1, ID2);
                            }
                        }
                    }
                    break;
                case 3:
                    System.out.println("Exiting program...");
                    System.exit(0); 
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }

        sc.close();
    }
}