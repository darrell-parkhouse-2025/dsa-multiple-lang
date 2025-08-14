package algorithms;

import java.util.*;

/**
 * Breadth-First Search (BFS) Algorithm Implementation in Java
 * 
 * Time Complexity: O(V + E) where V = vertices, E = edges
 * Space Complexity: O(V) for the queue and visited set
 * 
 * BFS explores nodes level by level, visiting all neighbors of a node
 * before moving to the next level. It's optimal for finding shortest
 * paths in unweighted graphs.
 */
public class BFS {
    
    /**
     * Graph representation using adjacency list
     */
    public static class Graph {
        private Map<Integer, List<Integer>> adjList;
        private boolean isDirected;
        
        /**
         * Constructor
         * @param directed Whether the graph is directed
         */
        public Graph(boolean directed) {
            this.adjList = new HashMap<>();
            this.isDirected = directed;
        }
        
        /**
         * Add an edge to the graph
         * @param from Source vertex
         * @param to Destination vertex
         */
        public void addEdge(int from, int to) {
            adjList.computeIfAbsent(from, k -> new ArrayList<>()).add(to);
            if (!isDirected) {
                adjList.computeIfAbsent(to, k -> new ArrayList<>()).add(from);
            }
        }
        
        /**
         * Add a vertex to the graph (if not already present)
         * @param vertex Vertex to add
         */
        public void addVertex(int vertex) {
            adjList.computeIfAbsent(vertex, k -> new ArrayList<>());
        }
        
        /**
         * Get neighbors of a vertex
         * @param vertex Vertex to get neighbors for
         * @return List of neighboring vertices
         */
        public List<Integer> getNeighbors(int vertex) {
            return adjList.getOrDefault(vertex, new ArrayList<>());
        }
        
        /**
         * Get all vertices in the graph
         * @return Set of all vertices
         */
        public Set<Integer> getAllVertices() {
            return adjList.keySet();
        }
        
        /**
         * Check if vertex exists in graph
         * @param vertex Vertex to check
         * @return true if vertex exists
         */
        public boolean hasVertex(int vertex) {
            return adjList.containsKey(vertex);
        }
        
        /**
         * Get number of vertices
         * @return Number of vertices
         */
        public int getVertexCount() {
            return adjList.size();
        }
        
        /**
         * Print the graph
         */
        public void printGraph() {
            System.out.println("Graph adjacency list:");
            for (Map.Entry<Integer, List<Integer>> entry : adjList.entrySet()) {
                System.out.print(entry.getKey() + ": ");
                for (int neighbor : entry.getValue()) {
                    System.out.print(neighbor + " ");
                }
                System.out.println();
            }
        }
    }
    
    /**
     * Basic BFS traversal from a starting vertex
     * @param graph Graph to traverse
     * @param start Starting vertex
     * @return List of vertices in BFS order
     */
    public static List<Integer> traverse(Graph graph, int start) {
        List<Integer> result = new ArrayList<>();
        Set<Integer> visited = new HashSet<>();
        Queue<Integer> queue = new LinkedList<>();
        
        if (!graph.hasVertex(start)) {
            return result;
        }
        
        queue.offer(start);
        visited.add(start);
        
        while (!queue.isEmpty()) {
            int current = queue.poll();
            result.add(current);
            
            // Visit all unvisited neighbors
            for (int neighbor : graph.getNeighbors(current)) {
                if (!visited.contains(neighbor)) {
                    visited.add(neighbor);
                    queue.offer(neighbor);
                }
            }
        }
        
        return result;
    }
    
    /**
     * BFS to find shortest path between two vertices (unweighted graph)
     * @param graph Graph to search in
     * @param start Starting vertex
     * @param target Target vertex
     * @return List representing the shortest path, empty if no path exists
     */
    public static List<Integer> shortestPath(Graph graph, int start, int target) {
        if (!graph.hasVertex(start) || !graph.hasVertex(target)) {
            return new ArrayList<>();
        }
        
        if (start == target) {
            return Arrays.asList(start);
        }
        
        Set<Integer> visited = new HashSet<>();
        Queue<Integer> queue = new LinkedList<>();
        Map<Integer, Integer> parent = new HashMap<>();
        
        queue.offer(start);
        visited.add(start);
        parent.put(start, -1);
        
        while (!queue.isEmpty()) {
            int current = queue.poll();
            
            if (current == target) {
                // Reconstruct path
                List<Integer> path = new ArrayList<>();
                int node = target;
                while (node != -1) {
                    path.add(node);
                    node = parent.get(node);
                }
                Collections.reverse(path);
                return path;
            }
            
            for (int neighbor : graph.getNeighbors(current)) {
                if (!visited.contains(neighbor)) {
                    visited.add(neighbor);
                    parent.put(neighbor, current);
                    queue.offer(neighbor);
                }
            }
        }
        
        return new ArrayList<>(); // No path found
    }
    
    /**
     * BFS to find shortest distance between two vertices
     * @param graph Graph to search in
     * @param start Starting vertex
     * @param target Target vertex
     * @return Shortest distance, -1 if no path exists
     */
    public static int shortestDistance(Graph graph, int start, int target) {
        if (!graph.hasVertex(start) || !graph.hasVertex(target)) {
            return -1;
        }
        
        if (start == target) {
            return 0;
        }
        
        Set<Integer> visited = new HashSet<>();
        Queue<int[]> queue = new LinkedList<>(); // [vertex, distance]
        
        queue.offer(new int[]{start, 0});
        visited.add(start);
        
        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            int vertex = current[0];
            int distance = current[1];
            
            for (int neighbor : graph.getNeighbors(vertex)) {
                if (neighbor == target) {
                    return distance + 1;
                }
                
                if (!visited.contains(neighbor)) {
                    visited.add(neighbor);
                    queue.offer(new int[]{neighbor, distance + 1});
                }
            }
        }
        
        return -1; // No path found
    }
    
    /**
     * BFS to find all vertices at a specific distance from start
     * @param graph Graph to search in
     * @param start Starting vertex
     * @param distance Target distance
     * @return List of vertices at the specified distance
     */
    public static List<Integer> verticesAtDistance(Graph graph, int start, int distance) {
        List<Integer> result = new ArrayList<>();
        
        if (!graph.hasVertex(start) || distance < 0) {
            return result;
        }
        
        if (distance == 0) {
            return Arrays.asList(start);
        }
        
        Set<Integer> visited = new HashSet<>();
        Queue<int[]> queue = new LinkedList<>(); // [vertex, current_distance]
        
        queue.offer(new int[]{start, 0});
        visited.add(start);
        
        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            int vertex = current[0];
            int currentDistance = current[1];
            
            if (currentDistance == distance) {
                result.add(vertex);
                continue;
            }
            
            if (currentDistance < distance) {
                for (int neighbor : graph.getNeighbors(vertex)) {
                    if (!visited.contains(neighbor)) {
                        visited.add(neighbor);
                        queue.offer(new int[]{neighbor, currentDistance + 1});
                    }
                }
            }
        }
        
        return result;
    }
    
    /**
     * Check if graph is connected using BFS
     * @param graph Graph to check
     * @return true if graph is connected
     */
    public static boolean isConnected(Graph graph) {
        Set<Integer> vertices = graph.getAllVertices();
        if (vertices.isEmpty()) {
            return true;
        }
        
        int startVertex = vertices.iterator().next();
        List<Integer> traversalResult = traverse(graph, startVertex);
        return traversalResult.size() == vertices.size();
    }
    
    /**
     * Find connected components using BFS
     * @param graph Graph to analyze
     * @return List of connected components, each component is a list of vertices
     */
    public static List<List<Integer>> findConnectedComponents(Graph graph) {
        List<List<Integer>> components = new ArrayList<>();
        Set<Integer> globalVisited = new HashSet<>();
        
        for (int vertex : graph.getAllVertices()) {
            if (!globalVisited.contains(vertex)) {
                List<Integer> component = new ArrayList<>();
                Set<Integer> visited = new HashSet<>();
                Queue<Integer> queue = new LinkedList<>();
                
                queue.offer(vertex);
                visited.add(vertex);
                globalVisited.add(vertex);
                
                while (!queue.isEmpty()) {
                    int current = queue.poll();
                    component.add(current);
                    
                    for (int neighbor : graph.getNeighbors(current)) {
                        if (!visited.contains(neighbor)) {
                            visited.add(neighbor);
                            globalVisited.add(neighbor);
                            queue.offer(neighbor);
                        }
                    }
                }
                
                components.add(component);
            }
        }
        
        return components;
    }
    
    /**
     * BFS on a 2D grid (treating grid cells as vertices)
     * @param grid 2D grid where 0 = walkable, 1 = obstacle
     * @param startRow Starting row
     * @param startCol Starting column
     * @param targetRow Target row
     * @param targetCol Target column
     * @return List of int arrays representing the shortest path coordinates
     */
    public static List<int[]> gridBFS(int[][] grid, int startRow, int startCol, 
                                     int targetRow, int targetCol) {
        if (grid == null || grid.length == 0 || grid[0].length == 0) {
            return new ArrayList<>();
        }
        
        int rows = grid.length;
        int cols = grid[0].length;
        
        // Check bounds and obstacles
        if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols ||
            targetRow < 0 || targetRow >= rows || targetCol < 0 || targetCol >= cols ||
            grid[startRow][startCol] == 1 || grid[targetRow][targetCol] == 1) {
            return new ArrayList<>();
        }
        
        if (startRow == targetRow && startCol == targetCol) {
            return Arrays.asList(new int[]{startRow, startCol});
        }
        
        boolean[][] visited = new boolean[rows][cols];
        int[][][] parent = new int[rows][cols][2]; // Store parent coordinates
        Queue<int[]> queue = new LinkedList<>();
        
        // Directions: up, down, left, right
        int[][] directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        queue.offer(new int[]{startRow, startCol});
        visited[startRow][startCol] = true;
        parent[startRow][startCol] = new int[]{-1, -1};
        
        while (!queue.isEmpty()) {
            int[] current = queue.poll();
            int row = current[0];
            int col = current[1];
            
            if (row == targetRow && col == targetCol) {
                // Reconstruct path
                List<int[]> path = new ArrayList<>();
                int currentRow = targetRow, currentCol = targetCol;
                
                while (currentRow != -1 && currentCol != -1) {
                    path.add(new int[]{currentRow, currentCol});
                    int[] parentCoord = parent[currentRow][currentCol];
                    currentRow = parentCoord[0];
                    currentCol = parentCoord[1];
                }
                
                Collections.reverse(path);
                return path;
            }
            
            for (int[] dir : directions) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];
                
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                    !visited[newRow][newCol] && grid[newRow][newCol] == 0) {
                    visited[newRow][newCol] = true;
                    parent[newRow][newCol] = new int[]{row, col};
                    queue.offer(new int[]{newRow, newCol});
                }
            }
        }
        
        return new ArrayList<>(); // No path found
    }
    
    /**
     * Utility method to print BFS traversal result
     * @param result List of vertices from BFS traversal
     * @param title Title for the output
     */
    public static void printTraversal(List<Integer> result, String title) {
        System.out.print(title + ": ");
        for (int i = 0; i < result.size(); i++) {
            System.out.print(result.get(i));
            if (i < result.size() - 1) System.out.print(" -> ");
        }
        System.out.println();
    }
    
    /**
     * Utility method to print path
     * @param path List representing a path
     * @param title Title for the output
     */
    public static void printPath(List<Integer> path, String title) {
        System.out.print(title + ": ");
        if (path.isEmpty()) {
            System.out.print("No path found");
        } else {
            for (int i = 0; i < path.size(); i++) {
                System.out.print(path.get(i));
                if (i < path.size() - 1) System.out.print(" -> ");
            }
        }
        System.out.println();
    }
    
    /**
     * Utility method to print grid path
     * @param path List of coordinate arrays representing a path
     * @param title Title for the output
     */
    public static void printGridPath(List<int[]> path, String title) {
        System.out.print(title + ": ");
        if (path.isEmpty()) {
            System.out.print("No path found");
        } else {
            for (int i = 0; i < path.size(); i++) {
                int[] coord = path.get(i);
                System.out.print("(" + coord[0] + "," + coord[1] + ")");
                if (i < path.size() - 1) System.out.print(" -> ");
            }
        }
        System.out.println();
    }
}
