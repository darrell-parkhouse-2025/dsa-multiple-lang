#ifndef BFS_H
#define BFS_H

#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <algorithm>

/**
 * Breadth-First Search (BFS) Algorithm Implementation
 * 
 * Time Complexity: O(V + E) where V = vertices, E = edges
 * Space Complexity: O(V) for the queue and visited set
 * 
 * BFS explores nodes level by level, visiting all neighbors of a node
 * before moving to the next level. It's optimal for finding shortest
 * paths in unweighted graphs.
 */

namespace BFS {
    
    /**
     * Graph representation using adjacency list
     */
    class Graph {
    private:
        std::unordered_map<int, std::vector<int>> adjList;
        bool isDirected;
        
    public:
        /**
         * Constructor
         * @param directed Whether the graph is directed
         */
        explicit Graph(bool directed = false) : isDirected(directed) {}
        
        /**
         * Add an edge to the graph
         * @param from Source vertex
         * @param to Destination vertex
         */
        void addEdge(int from, int to) {
            adjList[from].push_back(to);
            if (!isDirected) {
                adjList[to].push_back(from);
            }
        }
        
        /**
         * Add a vertex to the graph (if not already present)
         * @param vertex Vertex to add
         */
        void addVertex(int vertex) {
            if (adjList.find(vertex) == adjList.end()) {
                adjList[vertex] = std::vector<int>();
            }
        }
        
        /**
         * Get neighbors of a vertex
         * @param vertex Vertex to get neighbors for
         * @return Vector of neighboring vertices
         */
        const std::vector<int>& getNeighbors(int vertex) const {
            static std::vector<int> empty;
            auto it = adjList.find(vertex);
            return (it != adjList.end()) ? it->second : empty;
        }
        
        /**
         * Get all vertices in the graph
         * @return Vector of all vertices
         */
        std::vector<int> getAllVertices() const {
            std::vector<int> vertices;
            for (const auto& pair : adjList) {
                vertices.push_back(pair.first);
            }
            return vertices;
        }
        
        /**
         * Check if vertex exists in graph
         * @param vertex Vertex to check
         * @return true if vertex exists
         */
        bool hasVertex(int vertex) const {
            return adjList.find(vertex) != adjList.end();
        }
        
        /**
         * Get number of vertices
         * @return Number of vertices
         */
        size_t getVertexCount() const {
            return adjList.size();
        }
        
        /**
         * Print the graph
         */
        void printGraph() const {
            std::cout << "Graph adjacency list:" << std::endl;
            for (const auto& pair : adjList) {
                std::cout << pair.first << ": ";
                for (int neighbor : pair.second) {
                    std::cout << neighbor << " ";
                }
                std::cout << std::endl;
            }
        }
    };
    
    /**
     * Basic BFS traversal from a starting vertex
     * @param graph Graph to traverse
     * @param start Starting vertex
     * @return Vector of vertices in BFS order
     */
    std::vector<int> traverse(const Graph& graph, int start) {
        std::vector<int> result;
        std::unordered_set<int> visited;
        std::queue<int> queue;
        
        if (!graph.hasVertex(start)) {
            return result;
        }
        
        queue.push(start);
        visited.insert(start);
        
        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();
            result.push_back(current);
            
            // Visit all unvisited neighbors
            for (int neighbor : graph.getNeighbors(current)) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    queue.push(neighbor);
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
     * @return Vector representing the shortest path, empty if no path exists
     */
    std::vector<int> shortestPath(const Graph& graph, int start, int target) {
        if (!graph.hasVertex(start) || !graph.hasVertex(target)) {
            return {};
        }
        
        if (start == target) {
            return {start};
        }
        
        std::unordered_set<int> visited;
        std::queue<int> queue;
        std::unordered_map<int, int> parent;
        
        queue.push(start);
        visited.insert(start);
        parent[start] = -1;
        
        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();
            
            if (current == target) {
                // Reconstruct path
                std::vector<int> path;
                int node = target;
                while (node != -1) {
                    path.push_back(node);
                    node = parent[node];
                }
                std::reverse(path.begin(), path.end());
                return path;
            }
            
            for (int neighbor : graph.getNeighbors(current)) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    parent[neighbor] = current;
                    queue.push(neighbor);
                }
            }
        }
        
        return {};  // No path found
    }
    
    /**
     * BFS to find shortest distance between two vertices
     * @param graph Graph to search in
     * @param start Starting vertex
     * @param target Target vertex
     * @return Shortest distance, -1 if no path exists
     */
    int shortestDistance(const Graph& graph, int start, int target) {
        if (!graph.hasVertex(start) || !graph.hasVertex(target)) {
            return -1;
        }
        
        if (start == target) {
            return 0;
        }
        
        std::unordered_set<int> visited;
        std::queue<std::pair<int, int>> queue;  // {vertex, distance}
        
        queue.push({start, 0});
        visited.insert(start);
        
        while (!queue.empty()) {
            auto [current, distance] = queue.front();
            queue.pop();
            
            for (int neighbor : graph.getNeighbors(current)) {
                if (neighbor == target) {
                    return distance + 1;
                }
                
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    queue.push({neighbor, distance + 1});
                }
            }
        }
        
        return -1;  // No path found
    }
    
    /**
     * BFS to find all vertices at a specific distance from start
     * @param graph Graph to search in
     * @param start Starting vertex
     * @param distance Target distance
     * @return Vector of vertices at the specified distance
     */
    std::vector<int> verticesAtDistance(const Graph& graph, int start, int distance) {
        std::vector<int> result;
        
        if (!graph.hasVertex(start) || distance < 0) {
            return result;
        }
        
        if (distance == 0) {
            return {start};
        }
        
        std::unordered_set<int> visited;
        std::queue<std::pair<int, int>> queue;  // {vertex, current_distance}
        
        queue.push({start, 0});
        visited.insert(start);
        
        while (!queue.empty()) {
            auto [current, currentDistance] = queue.front();
            queue.pop();
            
            if (currentDistance == distance) {
                result.push_back(current);
                continue;
            }
            
            if (currentDistance < distance) {
                for (int neighbor : graph.getNeighbors(current)) {
                    if (visited.find(neighbor) == visited.end()) {
                        visited.insert(neighbor);
                        queue.push({neighbor, currentDistance + 1});
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
    bool isConnected(const Graph& graph) {
        auto vertices = graph.getAllVertices();
        if (vertices.empty()) {
            return true;
        }
        
        auto traversalResult = traverse(graph, vertices[0]);
        return traversalResult.size() == vertices.size();
    }
    
    /**
     * Find connected components using BFS
     * @param graph Graph to analyze
     * @return Vector of connected components, each component is a vector of vertices
     */
    std::vector<std::vector<int>> findConnectedComponents(const Graph& graph) {
        std::vector<std::vector<int>> components;
        std::unordered_set<int> globalVisited;
        
        for (int vertex : graph.getAllVertices()) {
            if (globalVisited.find(vertex) == globalVisited.end()) {
                std::vector<int> component;
                std::unordered_set<int> visited;
                std::queue<int> queue;
                
                queue.push(vertex);
                visited.insert(vertex);
                globalVisited.insert(vertex);
                
                while (!queue.empty()) {
                    int current = queue.front();
                    queue.pop();
                    component.push_back(current);
                    
                    for (int neighbor : graph.getNeighbors(current)) {
                        if (visited.find(neighbor) == visited.end()) {
                            visited.insert(neighbor);
                            globalVisited.insert(neighbor);
                            queue.push(neighbor);
                        }
                    }
                }
                
                components.push_back(component);
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
     * @return Vector of pairs representing the shortest path
     */
    std::vector<std::pair<int, int>> gridBFS(
        const std::vector<std::vector<int>>& grid,
        int startRow, int startCol,
        int targetRow, int targetCol
    ) {
        if (grid.empty() || grid[0].empty()) {
            return {};
        }
        
        int rows = grid.size();
        int cols = grid[0].size();
        
        // Check bounds and obstacles
        if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols ||
            targetRow < 0 || targetRow >= rows || targetCol < 0 || targetCol >= cols ||
            grid[startRow][startCol] == 1 || grid[targetRow][targetCol] == 1) {
            return {};
        }
        
        if (startRow == targetRow && startCol == targetCol) {
            return {{startRow, startCol}};
        }
        
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
        std::vector<std::vector<std::pair<int, int>>> parent(rows, std::vector<std::pair<int, int>>(cols, {-1, -1}));
        std::queue<std::pair<int, int>> queue;
        
        // Directions: up, down, left, right
        std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        queue.push({startRow, startCol});
        visited[startRow][startCol] = true;
        
        while (!queue.empty()) {
            auto [row, col] = queue.front();
            queue.pop();
            
            if (row == targetRow && col == targetCol) {
                // Reconstruct path
                std::vector<std::pair<int, int>> path;
                int currentRow = targetRow, currentCol = targetCol;
                
                while (currentRow != -1 && currentCol != -1) {
                    path.push_back({currentRow, currentCol});
                    auto [parentRow, parentCol] = parent[currentRow][currentCol];
                    currentRow = parentRow;
                    currentCol = parentCol;
                }
                
                std::reverse(path.begin(), path.end());
                return path;
            }
            
            for (auto [dr, dc] : directions) {
                int newRow = row + dr;
                int newCol = col + dc;
                
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                    !visited[newRow][newCol] && grid[newRow][newCol] == 0) {
                    visited[newRow][newCol] = true;
                    parent[newRow][newCol] = {row, col};
                    queue.push({newRow, newCol});
                }
            }
        }
        
        return {};  // No path found
    }
    
    /**
     * Utility function to print BFS traversal result
     * @param result Vector of vertices from BFS traversal
     * @param title Title for the output
     */
    void printTraversal(const std::vector<int>& result, const std::string& title = "BFS Traversal") {
        std::cout << title << ": ";
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << result[i];
            if (i < result.size() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
    }
    
    /**
     * Utility function to print path
     * @param path Vector representing a path
     * @param title Title for the output
     */
    void printPath(const std::vector<int>& path, const std::string& title = "Path") {
        std::cout << title << ": ";
        if (path.empty()) {
            std::cout << "No path found";
        } else {
            for (size_t i = 0; i < path.size(); ++i) {
                std::cout << path[i];
                if (i < path.size() - 1) std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }
}

#endif // BFS_H
