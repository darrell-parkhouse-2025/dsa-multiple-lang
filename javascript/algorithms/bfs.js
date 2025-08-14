/**
 * Breadth-First Search (BFS) Algorithm Implementation in JavaScript
 * 
 * Time Complexity: O(V + E) where V = vertices, E = edges
 * Space Complexity: O(V) for the queue and visited set
 * 
 * BFS explores nodes level by level, visiting all neighbors of a node
 * before moving to the next level. It's optimal for finding shortest
 * paths in unweighted graphs.
 */

/**
 * Graph representation using adjacency list
 */
class Graph {
    /**
     * Constructor
     * @param {boolean} directed - Whether the graph is directed
     */
    constructor(directed = false) {
        this.adjList = new Map();
        this.isDirected = directed;
    }
    
    /**
     * Add an edge to the graph
     * @param {number} from - Source vertex
     * @param {number} to - Destination vertex
     */
    addEdge(from, to) {
        if (!this.adjList.has(from)) {
            this.adjList.set(from, []);
        }
        this.adjList.get(from).push(to);
        
        if (!this.isDirected) {
            if (!this.adjList.has(to)) {
                this.adjList.set(to, []);
            }
            this.adjList.get(to).push(from);
        }
    }
    
    /**
     * Add a vertex to the graph (if not already present)
     * @param {number} vertex - Vertex to add
     */
    addVertex(vertex) {
        if (!this.adjList.has(vertex)) {
            this.adjList.set(vertex, []);
        }
    }
    
    /**
     * Get neighbors of a vertex
     * @param {number} vertex - Vertex to get neighbors for
     * @returns {number[]} Array of neighboring vertices
     */
    getNeighbors(vertex) {
        return this.adjList.get(vertex) || [];
    }
    
    /**
     * Get all vertices in the graph
     * @returns {number[]} Array of all vertices
     */
    getAllVertices() {
        return Array.from(this.adjList.keys());
    }
    
    /**
     * Check if vertex exists in graph
     * @param {number} vertex - Vertex to check
     * @returns {boolean} true if vertex exists
     */
    hasVertex(vertex) {
        return this.adjList.has(vertex);
    }
    
    /**
     * Get number of vertices
     * @returns {number} Number of vertices
     */
    getVertexCount() {
        return this.adjList.size;
    }
    
    /**
     * Print the graph
     */
    printGraph() {
        console.log("Graph adjacency list:");
        for (const [vertex, neighbors] of this.adjList) {
            console.log(`${vertex}: ${neighbors.join(" ")}`);
        }
    }
}

/**
 * BFS Algorithm implementations
 */
class BFS {
    /**
     * Basic BFS traversal from a starting vertex
     * @param {Graph} graph - Graph to traverse
     * @param {number} start - Starting vertex
     * @returns {number[]} Array of vertices in BFS order
     */
    static traverse(graph, start) {
        const result = [];
        const visited = new Set();
        const queue = [];
        
        if (!graph.hasVertex(start)) {
            return result;
        }
        
        queue.push(start);
        visited.add(start);
        
        while (queue.length > 0) {
            const current = queue.shift();
            result.push(current);
            
            // Visit all unvisited neighbors
            for (const neighbor of graph.getNeighbors(current)) {
                if (!visited.has(neighbor)) {
                    visited.add(neighbor);
                    queue.push(neighbor);
                }
            }
        }
        
        return result;
    }
    
    /**
     * BFS to find shortest path between two vertices (unweighted graph)
     * @param {Graph} graph - Graph to search in
     * @param {number} start - Starting vertex
     * @param {number} target - Target vertex
     * @returns {number[]} Array representing the shortest path, empty if no path exists
     */
    static shortestPath(graph, start, target) {
        if (!graph.hasVertex(start) || !graph.hasVertex(target)) {
            return [];
        }
        
        if (start === target) {
            return [start];
        }
        
        const visited = new Set();
        const queue = [];
        const parent = new Map();
        
        queue.push(start);
        visited.add(start);
        parent.set(start, -1);
        
        while (queue.length > 0) {
            const current = queue.shift();
            
            if (current === target) {
                // Reconstruct path
                const path = [];
                let node = target;
                while (node !== -1) {
                    path.push(node);
                    node = parent.get(node);
                }
                return path.reverse();
            }
            
            for (const neighbor of graph.getNeighbors(current)) {
                if (!visited.has(neighbor)) {
                    visited.add(neighbor);
                    parent.set(neighbor, current);
                    queue.push(neighbor);
                }
            }
        }
        
        return []; // No path found
    }
    
    /**
     * BFS to find shortest distance between two vertices
     * @param {Graph} graph - Graph to search in
     * @param {number} start - Starting vertex
     * @param {number} target - Target vertex
     * @returns {number} Shortest distance, -1 if no path exists
     */
    static shortestDistance(graph, start, target) {
        if (!graph.hasVertex(start) || !graph.hasVertex(target)) {
            return -1;
        }
        
        if (start === target) {
            return 0;
        }
        
        const visited = new Set();
        const queue = []; // Will store {vertex, distance} objects
        
        queue.push({ vertex: start, distance: 0 });
        visited.add(start);
        
        while (queue.length > 0) {
            const { vertex, distance } = queue.shift();
            
            for (const neighbor of graph.getNeighbors(vertex)) {
                if (neighbor === target) {
                    return distance + 1;
                }
                
                if (!visited.has(neighbor)) {
                    visited.add(neighbor);
                    queue.push({ vertex: neighbor, distance: distance + 1 });
                }
            }
        }
        
        return -1; // No path found
    }
    
    /**
     * BFS to find all vertices at a specific distance from start
     * @param {Graph} graph - Graph to search in
     * @param {number} start - Starting vertex
     * @param {number} distance - Target distance
     * @returns {number[]} Array of vertices at the specified distance
     */
    static verticesAtDistance(graph, start, distance) {
        const result = [];
        
        if (!graph.hasVertex(start) || distance < 0) {
            return result;
        }
        
        if (distance === 0) {
            return [start];
        }
        
        const visited = new Set();
        const queue = []; // Will store {vertex, currentDistance} objects
        
        queue.push({ vertex: start, currentDistance: 0 });
        visited.add(start);
        
        while (queue.length > 0) {
            const { vertex, currentDistance } = queue.shift();
            
            if (currentDistance === distance) {
                result.push(vertex);
                continue;
            }
            
            if (currentDistance < distance) {
                for (const neighbor of graph.getNeighbors(vertex)) {
                    if (!visited.has(neighbor)) {
                        visited.add(neighbor);
                        queue.push({ vertex: neighbor, currentDistance: currentDistance + 1 });
                    }
                }
            }
        }
        
        return result;
    }
    
    /**
     * Check if graph is connected using BFS
     * @param {Graph} graph - Graph to check
     * @returns {boolean} true if graph is connected
     */
    static isConnected(graph) {
        const vertices = graph.getAllVertices();
        if (vertices.length === 0) {
            return true;
        }
        
        const traversalResult = BFS.traverse(graph, vertices[0]);
        return traversalResult.length === vertices.length;
    }
    
    /**
     * Find connected components using BFS
     * @param {Graph} graph - Graph to analyze
     * @returns {number[][]} Array of connected components, each component is an array of vertices
     */
    static findConnectedComponents(graph) {
        const components = [];
        const globalVisited = new Set();
        
        for (const vertex of graph.getAllVertices()) {
            if (!globalVisited.has(vertex)) {
                const component = [];
                const visited = new Set();
                const queue = [];
                
                queue.push(vertex);
                visited.add(vertex);
                globalVisited.add(vertex);
                
                while (queue.length > 0) {
                    const current = queue.shift();
                    component.push(current);
                    
                    for (const neighbor of graph.getNeighbors(current)) {
                        if (!visited.has(neighbor)) {
                            visited.add(neighbor);
                            globalVisited.add(neighbor);
                            queue.push(neighbor);
                        }
                    }
                }
                
                components.push(component);
            }
        }
        
        return components;
    }
    
    /**
     * BFS on a 2D grid (treating grid cells as vertices)
     * @param {number[][]} grid - 2D grid where 0 = walkable, 1 = obstacle
     * @param {number} startRow - Starting row
     * @param {number} startCol - Starting column
     * @param {number} targetRow - Target row
     * @param {number} targetCol - Target column
     * @returns {number[][]} Array of coordinate pairs representing the shortest path
     */
    static gridBFS(grid, startRow, startCol, targetRow, targetCol) {
        if (!grid || grid.length === 0 || grid[0].length === 0) {
            return [];
        }
        
        const rows = grid.length;
        const cols = grid[0].length;
        
        // Check bounds and obstacles
        if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols ||
            targetRow < 0 || targetRow >= rows || targetCol < 0 || targetCol >= cols ||
            grid[startRow][startCol] === 1 || grid[targetRow][targetCol] === 1) {
            return [];
        }
        
        if (startRow === targetRow && startCol === targetCol) {
            return [[startRow, startCol]];
        }
        
        const visited = Array(rows).fill(null).map(() => Array(cols).fill(false));
        const parent = Array(rows).fill(null).map(() => Array(cols).fill(null).map(() => [-1, -1]));
        const queue = [];
        
        // Directions: up, down, left, right
        const directions = [[-1, 0], [1, 0], [0, -1], [0, 1]];
        
        queue.push([startRow, startCol]);
        visited[startRow][startCol] = true;
        
        while (queue.length > 0) {
            const [row, col] = queue.shift();
            
            if (row === targetRow && col === targetCol) {
                // Reconstruct path
                const path = [];
                let currentRow = targetRow, currentCol = targetCol;
                
                while (currentRow !== -1 && currentCol !== -1) {
                    path.push([currentRow, currentCol]);
                    const [parentRow, parentCol] = parent[currentRow][currentCol];
                    currentRow = parentRow;
                    currentCol = parentCol;
                }
                
                return path.reverse();
            }
            
            for (const [dr, dc] of directions) {
                const newRow = row + dr;
                const newCol = col + dc;
                
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                    !visited[newRow][newCol] && grid[newRow][newCol] === 0) {
                    visited[newRow][newCol] = true;
                    parent[newRow][newCol] = [row, col];
                    queue.push([newRow, newCol]);
                }
            }
        }
        
        return []; // No path found
    }
    
    /**
     * Utility function to print BFS traversal result
     * @param {number[]} result - Array of vertices from BFS traversal
     * @param {string} title - Title for the output
     */
    static printTraversal(result, title = "BFS Traversal") {
        console.log(`${title}: ${result.join(" -> ")}`);
    }
    
    /**
     * Utility function to print path
     * @param {number[]} path - Array representing a path
     * @param {string} title - Title for the output
     */
    static printPath(path, title = "Path") {
        if (path.length === 0) {
            console.log(`${title}: No path found`);
        } else {
            console.log(`${title}: ${path.join(" -> ")}`);
        }
    }
    
    /**
     * Utility function to print grid path
     * @param {number[][]} path - Array of coordinate pairs representing a path
     * @param {string} title - Title for the output
     */
    static printGridPath(path, title = "Grid Path") {
        if (path.length === 0) {
            console.log(`${title}: No path found`);
        } else {
            const pathStr = path.map(([row, col]) => `(${row},${col})`).join(" -> ");
            console.log(`${title}: ${pathStr}`);
        }
    }
}

// Export for Node.js environments
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { Graph, BFS };
}

// For browser environments, attach to window
if (typeof window !== 'undefined') {
    window.Graph = Graph;
    window.BFS = BFS;
}
