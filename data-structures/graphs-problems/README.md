# Graph Algorithms - EDA QXD0115

C++ implementations for three graph theory problems.

- **Author:** Gustavo Gurgel Medeiros
- **Date:** July 2023 
- [**Link to the Portuguese report document**](./relatorio.pdf)

## Problems Overview

| Problem | Description | Key Algorithms & Structures | Time Complexity |
| :--- | :--- | :--- | :--- |
| **1. Two-Color Graph** | Check if a graph can be colored with two colors (Bipartite check). | DFS, Odd-cycle detection | O(\|V\| + \|E\|) |
| **2. Kevin Bacon Number** | Find the shortest path between any actor and Kevin Bacon. | BFS, HashTable, AVL Tree | O(\|V\| + \|E\|) |
| **3. One-Way Streets** | Convert undirected roads to directed while maintaining connectivity. | DFS, Kosaraju's Algorithm | O(\|V\| + \|E\|) |

## Implementation Details

### 1. Two-Color Graph
*   **Logic:** A graph is bipartite if and only if it has no odd-length cycles.
*   **Process:** Explores vertices using DFS. If an adjacent explored vertex creates an odd-distance cycle, the graph cannot be colored with two colors.
*   **Space Complexity:** O(\|V\| + \|E\|)

### 2. Kevin Bacon Number
*   **Logic:** Shortest path calculation in an unweighted graph.
*   **Process:** Uses BFS starting from "Kevin Bacon" (distance 0). Maps relationships and movies.
*   **Data Structures:** 
    *   `HashTable<string, list<Actor>>` for O(1) average adjacency lookups.
    *   `AvlTree<string>` to store unique vertices and retrieve them in alphabetical order.

### 3. One-Way Streets Conversion
*   **Logic:** Converts a bidirectional graph into a directed graph and links Strongly Connected Components (SCCs).
*   **Process:** 
    *   Creates a preliminary directed graph using DFS and backedges.
    *   Identifies components using Kosaraju's Algorithm.
    *   Connects isolated SCCs to ensure global reachability across the city.
