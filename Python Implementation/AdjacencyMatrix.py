import networkx as nx

class AdjacencyMatrix:
    def __init__(self):
        self.graph = nx.Graph()
    
    def get_num_vertices(self):
        return self.graph.number_of_nodes()

    def has_edge(self, i, j):
        return self.graph.has_edge(i, j)

    def load_from_file(self, file_string):
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
        except FileNotFoundError:
            print(f"File not found: {file_string}")
        finally:
            file.close()
            
    def print_adjacency_matrix(self):
        print("\n\t==== ADJACENCY MATRIX ====\n")
        for i in range(self.get_num_vertices()):
            for j in range(self.get_num_vertices()):
                if self.graph.has_edge(i, j):
                    print("1 ", end="")# to make it so that it ends with a space rather than a new line
                else:
                    print("0 ", end="")
            print()

    def print_friend_list(self, ID1):
        friends = list(self.graph.neighbors(ID1))
        print(f"\n\t==== {ID1}'s FRIEND LIST ====\n")
        for friend in friends:
            print(friend)
        print(f"\n\n{ID1}'s Friend Count: {len(friends)}")

    def find_connections_bfs(self, ID1, ID2):
         # Validate ID inputs
        if ID1 < 0 or ID1 >= self.get_num_vertices or ID2 < 0 or ID2 >= self.get_num_vertices or ID1 == ID2:
            print(f"Invalid ID/s. The range of an ID should be from 0 to {self.get_num_vertices - 1} inclusive.\nThe two IDs should also not be the same.\n\n")
            return None

        connection_found = False
        queue = []  # List used as a queue
        visited_vertices = [False] * self.get_num_vertices  # Keeps track of visited vertices
        parent = [-1] * self.get_num_vertices  # Keeps track of the parent of each vertex

        # Mark the first vertex as visited and enqueue it
        visited_vertices[ID1] = True
        queue.append(ID1)

        # Process the vertices in the queue until the queue is empty or connection is found
        while queue:
            current_vertex = queue.pop(0)  # Dequeue the vertex at the front of the queue
            if current_vertex == ID2:
                connection_found = True
                break  # Exit the loop if the current_vertex is equal to ID2

            # Explore unvisited neighboring vertices of the current vertex
            for neighbor in self.graph.neighbors(current_vertex):
                if not visited_vertices[neighbor]:
                    visited_vertices[neighbor] = True
                    parent[neighbor] = current_vertex
                    queue.append(neighbor)

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

