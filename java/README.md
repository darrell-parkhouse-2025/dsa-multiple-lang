# Java Data Structures and Algorithms

This directory contains Java implementations of various data structures and algorithms.

## Structure

```
java/
├── src/
│   └── algorithms/
│       └── BFS.java           # Breadth-First Search implementation
└── tests/
    └── BFSTest.java           # Comprehensive BFS tests
```

## Algorithms Implemented

### Breadth-First Search (BFS)
- **File**: `src/algorithms/BFS.java`
- **Features**:
  - Graph traversal
  - Shortest path finding in unweighted graphs
  - Connected components detection
  - Grid-based pathfinding
  - Distance calculations

## Running the Code

### Prerequisites
- Java 8 or higher
- Basic understanding of graph theory

### Compilation and Execution

```bash
# Compile the BFS implementation and tests
javac -cp . src/algorithms/BFS.java tests/BFSTest.java

# Run the tests
java -cp . tests.BFSTest
```

### Example Usage

```java
import algorithms.BFS;
import algorithms.BFS.Graph;

// Create an undirected graph
Graph graph = new Graph(false);

// Add edges
graph.addEdge(0, 1);
graph.addEdge(0, 2);
graph.addEdge(1, 3);

// Perform BFS traversal
List<Integer> traversal = BFS.traverse(graph, 0);
System.out.println("BFS Traversal: " + traversal);

// Find shortest path
List<Integer> path = BFS.shortestPath(graph, 0, 3);
BFS.printPath(path, "Shortest Path");

// Check connectivity
boolean connected = BFS.isConnected(graph);
System.out.println("Graph is connected: " + connected);
```

## Algorithm Complexity

- **Time Complexity**: O(V + E) where V = vertices, E = edges
- **Space Complexity**: O(V) for the queue and visited set

## Features

- **Graph Representation**: Adjacency list using HashMap
- **Directed/Undirected**: Support for both graph types
- **Path Reconstruction**: Tracks parent nodes for path building
- **Grid Support**: BFS on 2D grids for pathfinding
- **Connected Components**: Finds all connected components in a graph
- **Performance Optimized**: Efficient queue operations and memory usage

## Test Coverage

The test suite includes:
- Basic graph traversal
- Shortest path finding
- Distance calculations
- Connected components
- Directed graph handling
- Grid-based pathfinding
- Edge cases and error handling
- Performance testing with large graphs
