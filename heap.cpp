//
// Created by idanh on 03/05/2025.
//

#include "heap.h"
#include <climits>
using namespace std;

#include <iostream>
#include <ostream>
#include <bits/locale_facets_nonio.h>
#include <bits/ranges_base.h>
#include <bits/range_access.h>

void MinHeap::printArrays()
{
    cout << "heap: ";
    for (int i=0; i < capacity; i++) {
        cout << heapArray[i] << " ";
    }
    cout << endl << "key: ";
    for (int i=0; i < capacity; i++) {
        cout << keyArray[i] << " ";
    }
    cout << endl << "pos: ";
    for (int i=0; i < capacity; i++) {
        cout << position[i] << " ";
    }
    cout << endl;
    cout << "capacity: " << capacity << endl;
    cout << "size: " << size << endl;
    cout << endl;
}

MinHeap::MinHeap(int capacity) {
    size = 0;
    this -> capacity = capacity;
    heapArray = new int[capacity];
    keyArray = new int[capacity];
    position = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        position[i] = -1;
    }
    for (int i = 0; i < capacity; i++) {
        heapArray[i] = -1;
    }
    for (int i = 0; i < capacity; i++) {
        keyArray[i] = INT_MAX;
    }
}


MinHeap::~MinHeap() {
    delete[] heapArray;
    delete[] keyArray;
    delete[] position;
}

void MinHeap::insert(int vertex, int key) {
    if (size >= capacity) {
        cout<<"Heap is full, capacity: " << capacity << ", size: " << size << endl;
        return;
    }
    if (vertex >= capacity) {
        cout << "Vertex out of bounds: " << vertex << ", capacity: " << capacity << endl;
        return;
    }
    if (isInMinHeap(vertex)) {
        cout<<"Vertex already exists: " << vertex << endl;
        decreaseKey(vertex, key);
        return;
    }
    //cout << "Inserting vertex: " << vertex << ", key: " << key << endl;

    keyArray[vertex] = key;
    int index = size;
    heapArray[index] = vertex;
    position[vertex] = index;
    size++;
    minHeapify(index);

    //printArrays();
}


int MinHeap::extractMin() {
    if (size <= 0) {
        cout << "Heap is empty" << endl;
        return -1;
    }

    int min = heapArray[0];
    size--;
    heapArray[0] = heapArray[size];
    heapArray[size] = -1;
    position[min] = -1;
    if (size == 0) {
        heapArray[0] = -1;
    }
    else {
        position[heapArray[0]] = 0;
        traverseDown(0);
    }

    //printArrays();

    return min;
}

void MinHeap::traverseDown(int index) {
    int vertex = heapArray[index];
    position[vertex] = index;
    int key = getKey(vertex);

    int left = getLeft(index);
    int right = getRight(index);
    int leftKey = -1;
    int rightKey = -1;
    if (left != -1){leftKey = getKey(left);}
    if (right != -1){rightKey = getKey(right);}

    if (right == -1) {
        if (left == -1) {
            return;
        }
        else if (leftKey < key) {
            traverseTo(index, vertex, getLeftPosition(index), left);
        }
    }
    else if (min(leftKey, rightKey) < key) {
        if (leftKey <= rightKey) {
            traverseTo(index, vertex, getLeftPosition(index), left);
        }
        else {
            traverseTo(index, vertex, getRightPosition(index), right);
        }
    }

}

void MinHeap::traverseTo(int index, int vertex, int childIndex, int child) {
    heapArray[index] = child;
    position[child] = index;
    heapArray[childIndex] = vertex;
    position[vertex] = childIndex;
    traverseDown(childIndex);
}



void MinHeap::decreaseKey(int vertex, int newKey) {
    if (newKey < keyArray[vertex]) {
        keyArray[vertex] = newKey;
        minHeapify(position[vertex]);
    }
}

bool MinHeap::isInMinHeap(int vertex) {
    if (vertex >= capacity) {
        cout << "Vertex out of bounds: " << vertex << ", capacity: " << capacity << endl;
        return false;
    }
    return position[vertex] != -1;
}

bool MinHeap::isEmpty() {
    return this->size == 0;
}

int MinHeap::getRightPosition(int currentPosition) {
    return currentPosition * 2 + 2;
}

int MinHeap::getRight(int currentPosition) {
    int rp = getRightPosition(currentPosition);
    if (rp >= capacity) {
        return -1;
    }
    return heapArray[rp];
}

int MinHeap::getLeftPosition(int currentPosition) {
    return currentPosition * 2 + 1;
}

int MinHeap::getLeft(int currentPosition) {
    int lp = getLeftPosition(currentPosition);
    if (lp >= capacity) {
        return -1;
    }
    return heapArray[lp];
}

int MinHeap::getParentPosition(int currentPosition) {
    return (currentPosition - 1) / 2;
}

int MinHeap::getParent(int currentPosition) {
    return heapArray[getParentPosition(currentPosition)];
}

int MinHeap::getVertexPosition(int vertex) {
    return position[vertex];
}

int MinHeap::getKey(int vertex) {
    return keyArray[vertex];
}

void MinHeap::minHeapify(int idx) {
    if (idx >= capacity) {
        cout << "Error: index out of bounds" << endl;
    }
    else if (idx == 0) {
        return;
    }
    else {
        int vertex = heapArray[idx];
        position[vertex] = idx;
        int key = getKey(vertex);
        int parent = getParent(idx);
        int parentKey = getKey(parent);
        if (key < parentKey) {
            heapArray[idx] = parent;
            position[parent] = idx;
            int parentIdx = getParentPosition(idx);
            //cout << "parentIdx: " << parentIdx << endl;
            heapArray[parentIdx] = vertex;
            position[vertex] = parentIdx;
            minHeapify(parentIdx);
        }
    }
}


