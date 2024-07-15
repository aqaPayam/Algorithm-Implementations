# Algorithm Implementations

This repository contains various algorithm implementations in Python and C++. Each file focuses on a specific algorithm or problem-solving technique, including sorting, graph algorithms, and game strategies.

## Files and Descriptions

### Python Files

1. **merge_sort_inversion.py**
   - Implementation of Merge Sort with inversion count calculation. This script reads an array of integers and outputs the number of inversions required to sort the array.
   
2. **equal_sum_subarrays.py**
   - This script finds the maximum number of equal sum subarrays from two input lists. It reads two lists of integers and outputs the maximum count of equal sum subarrays.

3. **graph_bipartite_component.py**
   - Contains the implementation of a graph algorithm to check if a graph is bipartite and counts its components. It uses Depth First Search (DFS) and Breadth First Search (BFS) for the operations.

4. **tic_tac_toe_minimax.py**
   - Implements the Minimax algorithm for a Tic-Tac-Toe game. This script determines the optimal move for the 'X' player, assuming both players play optimally.

5. **tic_tac_toe_checker.py**
   - Checks the current state of a Tic-Tac-Toe board to determine if there's a winner or if the game is a draw. It uses a simplified version of the Minimax algorithm to evaluate the board.

### C++ Files

1. **graph_bipartite.cpp**
   - Implementation of an algorithm to check if a graph is bipartite. It uses BFS to ensure no two adjacent nodes have the same color.

2. **graph_maxflow.cpp**
   - Implements the Ford-Fulkerson method for computing the maximum flow in a flow network. The script reads a graph with capacities and calculates the maximum possible flow from the source to the sink.

3. **graph_component_count.cpp**
   - This script counts the number of connected components in an undirected graph. It uses DFS for counting the components.
