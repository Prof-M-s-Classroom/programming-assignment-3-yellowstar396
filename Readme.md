[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/K_t6ffJX)
# Prim's Algorithm with Min Heap and Adjacency Matrix

## Author
Idan Haim

## Description
In my code, I have implemented both a min-heap (using an array representation), and a graph class.
In the graph class, i have also implemented the primMST method, that find the minimum spanning tree of of the graph, and prints its edges, individual weights, and total MST weight.

## Files
- graph.h / graph.cpp
- heap.h / heap.cpp
- main.cpp (unchanged)
- README.md

## How to Compile and Run
This project was developed and tested in CLion.  
Run directly from the IDE.

## Time Complexity Analysis

| Operation            | Time Complexity |
|----------------------|-----------------|
| Insert in MinHeap    | O(log_n)        |
| Extract Min          | O(log_n)        |
| Decrease Key         | O(log_n)        |
| Prim’s MST Overall   | O(v^2 * logV)   |

_Explain why your MST implementation has the above runtime._
 - Insert
   - We will start by placing the new value at the end of the current values (O(1))
   - Then, we will iterate up through the specific branch we are on - swapping values - until our inserted value will reach its correct position (the minHeapify method)
     - Since we are only iterating through only one branch, the time complexity will be O(log_n)
 - Extract
   - We will start by taking out the first values and placing the value at the end of the current values instead of it (O(1))
   - Then, we will iterate down through one of the branches - swapping values - until our 'root' value will reach its correct position
     - Since we are only iterating through only one branch, the time complexity will be O(log_n)
 - Decrease key
   - Checks if the new value is smaller than the value of the current key (O(1))
   - Changes the values of two array elements (O(1))
   - Calls minHeapify (also called by the insert method) (O(log_n))
 - Prim’s MST Overall
   - The code consists of 2 nested loops
     - The outer loop will eventually go over all of the vertices - so V times
     - The inner loop:
       - For each vertex, the code will go over all adjacent vertices (best case O(1), worst case O(V))
         - For each adjacent vertex, the code will run either insert (O(logV)) or decreaseKey (O(logV))
   - Final result:
     - Best case: V * logV --> O(V*logV)
     - Worst case: V * V * logV --> O(V^2 * logV)


## Assumptions
 - The graph is connected
 - The graph is undirected
 - The graph is weighted
 - No vertices above (numVertices) will exist in the graph (Ex: if numVertices = 5, the vertices v=5 or v=7 cannot and will not exist in the graph)


## Test Case Description
### Here are some code runs and their output:

#### Input 1:

    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);
    g.primMST();

#### Output 1:

    Edges:
    1 -- 4 | 5
    0 -- 3 | 6
    1 -- 2 | 3
    0 -- 1 | 2
    Total Weight: 16

#### Input 2:

    Graph g(6);
    g.addEdge(0, 1, 3);
    g.addEdge(0, 3, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 3);
    g.addEdge(1, 4, 6);
    g.addEdge(2, 4, 5);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 5);
    g.addEdge(4, 5, 2);
    g.primMST();

#### Output 2:
    
    Edges:
    5 -- 4 | 2
    2 -- 5 | 4
    1 -- 2 | 1
    0 -- 1 | 3
    0 -- 3 | 1
    Total Weight: 11

#### Input 3:

    Graph g(4);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.primMST();

#### Output 3:

    Edges:
    1 -- 3 | 2
    2 -- 1 | 1
    0 -- 2 | 3
    Total Weight: 6

## Challenges, Bugs, and Difficulties
 - One complicated bug the I had was that when trying to test the heap code, I kept getting a sigmentation fault:
   - The error pointed to the line "delete[] position" being the problem
   - For some reason, deleting position lead to an error, while deleting the other arrays did not cause any error
   - After searching the code, I realized that at some point, I tried to access the position array at index (-1), which caused a Memory Override
     - This resulted in an error when trying to delete the said position array