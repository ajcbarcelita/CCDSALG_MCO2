import networkx as nx
from AdjacencyList import AdjacencyList
from AdjacencyMatrix import AdjacencyMatrix

def main():
    file_found = False
    graph_choice = 0
    search_choice = 0
    file_string = ""
    adjacency_list = None
    adjacency_matrix = None
    connection = []
    choice = 0

    while not file_found:
        print("\n\t==== LOAD GRAPH DATA ====\n")
        print("Please indicate the ABSOLUTE file connection or file name of the .txt file containing the social graph data.")
        print("If entering file name, ensure that the file is in the same directory as this program.\n")
        
        file_string = input("Enter file connection or file name: ")

        try:
            with open(file_string, 'r') as file:
                print("File found.")
                file_found = True
        except FileNotFoundError:
            print("File not found. Please try again.")

    while graph_choice not in [1, 2]:
        print("\n\t==== CHOOSING A GRAPH FORMAT ====\n")
        print("Please choose the format of the social graph.")
        print("[1] Adjacency List.")
        print("[2] Matrix.\n")
        graph_choice = int(input("Enter choice: "))#is this fine? or do we still have to implement a try catch

        if graph_choice == 1:
            adjacency_list = AdjacencyList()
            adjacency_list.load_from_file(file_string)
            adjacency_list.print_adjacency_list()
        elif graph_choice == 2:
            adjacency_matrix = AdjacencyMatrix()
            adjacency_matrix.load_from_file(file_string)
            adjacency_matrix.print_adjacency_matrix()
        else:
            print("Invalid choice. Please try again.")

    
    while choice != 3:
        print("\n\t==== MAIN MENU ====\n")
        print("[1] Display friend list.")
        print("[2] Display connections.")
        print("[3] Exit.\n")
        try:
            choice = int(input("Enter choice: "))
        except ValueError:
            print("Input is not of type int. Please try again.")
            continue

        if choice == 1:
            '''
            This function accepts an ID number as a parameter.
            If valid, display total number of friends and list of friends.
            If not, display an error message, BUT not exit the program.
            '''
            
            ID1 = int(input("Enter ID number: "))
            if graph_choice == 1:
                if ID1 >= 0 and ID1 < adjacency_list.get_num_vertices():
                    adjacency_list.print_friend_list(ID1)
                else:
                    print("Invalid ID. Please enter a valid ID within the range.")
            elif graph_choice == 2:
                if ID1 >= 0 and ID1 < adjacency_matrix.get_num_vertices():
                    adjacency_matrix.print_friend_list(ID1)
                else:
                    print("Invalid ID. Please enter a valid ID within the range.")

        elif choice == 2:
            '''
            This function accepts 2 different ID numbers as parameters.
            If both ID numbers exist, display the connection/connection between the two, i.e, ID1 is friends with c1, until c(n-1) is friends with ID2.
            
            Note: 
            - A connection is a sequence from ID1, c1, c2, ..., ID2 such that ID1 is friends with c1, 
            c1 is friends with c2, ..., and c(n-1) is friends with ID2.

            If any/both ID numbers does not exist, display an error message, BUT not exit the program.
            '''
            ID1 = int(input("Enter ID number 1: "))
            ID2 = int(input("Enter ID number 2: "))
            print("\nChoose the search method: ")
            print("[1] Breadth First Search.")
            print("[2] Depth First Search.")
            search_choice = int(input("\nEnter choice: "))

            if graph_choice == 1:
                if search_choice == 1:
                    print("\nPerforming BFS on the graph from %d to %d...\n", ID1, ID2)
                    connection = adjacency_list.find_connections_bfs(ID1, ID2)
                    if connection: #if connection has any value
                        print(f"A connection from IDs {ID1} to {ID2} EXISTS!")
                        for i in range(len(connection) - 1):#loop for each connection
                            print(f"{connection[i]} is friends with {connection[i + 1]}.")
                    else:
                        print(f"No connection from IDs {ID1} to {ID2}.")
                        
                        
                elif search_choice == 2:
                    print("\nPerforming DFS on the graph from %d to %d...\n", ID1, ID2)
                    connection = adjacency_list.find_connections_dfs(ID1, ID2)
                    if connection: #if connection has any value
                        print(f"A connection from IDs {ID1} to {ID2} EXISTS!")
                        for i in range(len(connection) - 1):#loop for each connection
                            print(f"{connection[i]} is friends with {connection[i + 1]}.")
                    else:
                        print(f"No connection from IDs {ID1} to {ID2}.")
                        
                        
            elif graph_choice == 2:
                if search_choice == 1:
                    connection = adjacency_matrix.find_connections_bfs(ID1, ID2)
                    if connection:
                        print(f"A connection from IDs {ID1} to {ID2} EXISTS!")
                        for i in range(len(connection) - 1):
                            print(f"{connection[i]} is friends with {connection[i + 1]}.")
                    else:
                        print(f"No connection from IDs {ID1} to {ID2}.")
                        
                elif search_choice == 2:
                    print("\nPerforming DFS on the graph from %d to %d...\n", ID1, ID2)
                    connection = adjacency_list.find_connections_dfs(ID1, ID2)
                    if connection: #if connection has any value
                        print(f"A connection from IDs {ID1} to {ID2} EXISTS!")
                        for i in range(len(connection) - 1):#loop for each connection
                            print(f"{connection[i]} is friends with {connection[i + 1]}.")
                    else:
                        print(f"No connection from IDs {ID1} to {ID2}.")
                    
                    

        elif choice == 3:
            print("Exiting the program...")
            break
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
