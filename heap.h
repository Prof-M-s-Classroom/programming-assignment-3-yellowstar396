#ifndef HEAP_H
#define HEAP_H

class MinHeap {
public:
    void printArrays();

    MinHeap(int capacity);
    ~MinHeap();
    void insert(int vertex, int key);
    int extractMin();
    void decreaseKey(int vertex, int newKey);
    bool isInMinHeap(int vertex);
    bool isEmpty();

    int getKey(int vertex);



private:
    int* heapArray;        // Heap of vertex indices - [4, 2, 0, 1, 3]
    int* keyArray;         // Corresponding key values - [2, 7, 5, 11, 10]
    int* position;         // Maps vertex to its position in heap - [

    int capacity;
    int size;


    void minHeapify(int idx); //after inserting
    int getVertexPosition(int vertex);
    int getRightPosition(int currentPosition);
    int getRight(int currentPosition);
    int getLeftPosition(int currentPosition);
    int getLeft(int currentPosition);
    int getParentPosition(int currentPosition);
    int getParent(int currentPosition);
    void traverseDown(int index);
    void traverseTo(int index, int vertex, int childIndex, int child);


};

#endif