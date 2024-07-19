import java.util.*;

public abstract class Graph {
    protected int numVertices;
    protected int numEdges;

    public Graph() {
        this.numVertices = 0;
        this.numEdges = 0;
    }

    public int getNumVertices() {
        return this.numVertices;
    }

    public int getNumEdges() {
        return this.numEdges;
    }

    public abstract boolean hasEdge(int i, int j);
    public abstract void loadFromFile(String fileString);
    public abstract void printGraph();
    public abstract void printFriendList(int ID1);
    public abstract List<Integer> findConnections_BFS(int ID1, int ID2);
    public abstract List<Integer> findConnections_DFS(int ID1, int ID2);
    public abstract void printPath(List<Integer> path);
}
