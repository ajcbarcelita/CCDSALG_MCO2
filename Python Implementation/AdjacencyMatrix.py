import networkx as nx
import numpy as np
import heapq

class AdjacencyMatrix:
    """
    A class to represent a graph using an adjacency matrix.
    It uses NetworkX to handle graph operations and provides
    methods to load the graph from a file, print the adjacency
    matrix, display a friend list, and find connections between
    vertices using BFS or DFS.
    
    by Aaron Go
    """
    
    def __init__(self):
        """
        Initializes an empty graph using NetworkX, and prepares an adjacency matrix.
        """
        self.graph = nx.Graph()
        self.adj_matrix = None
    
    def get_num_vertices(self):
        """
        Returns the number of vertices (nodes) in the graph.

        Returns:
            int: Number of nodes in the graph.
        """
        return self.graph.number_of_nodes()
    
    def has_edge(self, i, j):
        """
        Checks if there is an edge between vertices i and j.

        Args:
            i (int): The first vertex.
            j (int): The second vertex.

        Returns:
            bool: True if there is an edge between i and j, False otherwise.
        """
        #has edge is already a function in networkx
        return self.adj_matrix[i,j]
    
    def load_from_file(self, file_string):
        """
        Loads the graph from a file. The file should contain
        the number of vertices and edges on the first line, followed
        by the edges in subsequent lines.

        Args:
            file_string (str): The path to the file containing graph data.
        """
        #open file in read mode
        file = open(file_string, 'r')
        try:
            #Read all lines
            lines = file.readlines()
            #split the first line to get the number of vertices and edges
            first_line = lines[0].strip().split()#strip to remove new line, then split it into words that are stored in the array
            num_vertices = int(first_line[0])
            num_edges = int(first_line[1])
            
            for line in lines[1:]: #make a sublist without the first line(skip the nodes and edges) then iterate through it
                i, j = map(int, line.strip().split())#changes them from words into integers, then puts them into i and j
                self.graph.add_edge(i, j)#and lastly adds an edge between the two
            
            print(f"File loaded successfully. List Graph has {num_vertices} vertices and {num_edges} edges.")
            self.adj_matrix = nx.adjacency_matrix(self.graph).todense() #turn graph into adj matrix, then use numpy to turn it into a dense graph(less complex)
        except FileNotFoundError:
            print(f"File not found: {file_string}")
        finally:
            file.close()
            
    def print_adjacency_matrix(self):
        """
        Checks if adjacency matrix is available, then
        Prints the adjacency matrix of the graph by using networkx's built-in adjacency matrix
        """
        
        if self.adj_matrix is None:
            print("Adjacency matrix is not available. Please load the graph first.")
            return

        print("\n\t==== ADJACENCY MATRIX ====\n")
        print(self.adj_matrix)

    def print_friend_list(self, ID1):
        """
        Checks if adj matrix is avail, then
        Prints the list of friends (neighbors) for a given vertex ID.

        Args:
            ID1 (int): The ID of the vertex for which to print the friend list.
        """
        friends = [j for j in range(self.get_num_vertices()) if self.adj_matrix[ID1, j] == 1]#iterates through the range of vertices(0 to numvertices-1), and if theres an edge, add it to friends 
        print(f"\n\t==== {ID1}'s FRIEND LIST ====\n")
        for friend in friends:
            print(friend)
        print(f"\n\n{ID1}'s Friend Count: {len(friends)}")

    def find_connections_bfs(self, ID1, ID2):
        """
        Finds a path between two vertices using Breadth-First Search (BFS). 
        This BFS implementation utilizes a priority queue to keep track of the vertices to be explored and ensures
        that each vertex is visited only once. 

        Args:
            ID1 (int): The starting vertex ID.
            ID2 (int): The ending vertex ID.

        Returns:
            list: A list of vertex IDs representing the path from ID1 to ID2.
            If no path is found, returns an empty list.
        """
         # Validate ID inputs 
        
        if ID1 < 0 or ID1 >= (self.get_num_vertices()) or ID2 < 0 or ID2 >= (self.get_num_vertices()) or ID1 == ID2:
            print(f"Invalid ID/s. The range of an ID should be from 0 to {(self.get_num_vertices()) - 1} inclusive.\nThe two IDs should also not be the same.\n\n")
            return None

        connection_found = False
        priority_queue = []  # List used as a queue
        
        visited_vertices = [False] * self.get_num_vertices()  # Keeps track of visited vertices
        parent = [-1] * self.get_num_vertices()  # Keeps track of the parent of each vertex
        
        #heappush = (list, (priority, node))
        heapq.heappush(priority_queue, (0, ID1))  # Use heapq to push the initial node with priority 0
        
        # Mark the first vertex as visited and enqueue it
        visited_vertices[ID1] = True

        # Process the vertices in the priority_queue until the priority_queue is empty or connection is found
        while priority_queue:
            _, current_vertex = heapq.heappop(priority_queue)  # Pop the node with the highest priority (lowest value), ignore the first value returned (priority) by assigning it to '_'
            if current_vertex == ID2:
                connection_found = True
                break
            
                    
            for neighbor in range(self.get_num_vertices()):
                if self.graph.has_edge(current_vertex, neighbor) and not visited_vertices[neighbor]:
                    visited_vertices[neighbor] = True
                    parent[neighbor] = current_vertex
                    heapq.heappush(priority_queue, (neighbor, neighbor))

        # If no connection is found between ID1 and ID2, display an error message
        if not connection_found:
            print(f"No connection found between IDs {ID1} and {ID2}.")
            return []

        # If a connection is found, reconstruct the path from ID1 to ID2 and display it
        connection = []
        i = ID2
        while i != -1:
            connection.append(i)
            i = parent[i]
        connection.reverse()  # Reverse the connection list to make it from ID1 to ID2 instead of ID2 to ID1
        return connection
        
    def find_connections_dfs(self, ID1, ID2):
        """
        Finds a path between two vertices using Depth-First Search (DFS). 
        This implementation uses a stack to keep track of the vertices to be explored 
        and ensures that each vertex is visited only once. 

        Args:
            ID1 (int): The starting vertex ID.
            ID2 (int): The ending vertex ID.

        Returns:
            list: A list of vertex IDs representing the path from ID1 to ID2.
            If no path is found, returns an empty list.
        """
        if ID1 < 0 or ID1 >= self.get_num_vertices() or ID2 < 0 or ID2 >= self.get_num_vertices() or ID1 == ID2:
            print(f"Invalid ID/s. The range of an ID should be from 0 to {self.get_num_vertices() - 1} inclusive.\nThe two IDs should also not be the same.\n\n")
            return None

        stack = [ID1]
        visited_vertices = [False] * self.get_num_vertices()
        parent = [-1] * self.get_num_vertices()

        visited_vertices[ID1] = True
        connection_found = False

        while stack:
            current_vertex = stack.pop()
            if current_vertex == ID2:
                connection_found = True
                break

            for neighbor in range(self.get_num_vertices()):#more elaborate way to not use graph
                if self.adj_matrix[current_vertex, neighbor] == 1 and not visited_vertices[neighbor]:
                    visited_vertices[neighbor] = True
                    parent[neighbor] = current_vertex
                    stack.append(neighbor)

        if not connection_found:
            print(f"No connection found between IDs {ID1} and {ID2}.")
            return []

        connection = []
        i = ID2
        while i != -1:

            connection.append(i)
            i = parent[i]
            
        connection.reverse()
        return connection

