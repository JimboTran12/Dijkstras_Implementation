#pragma once
#include"Node.cpp"
#include"Node.cpp"
#include <stdexcept>
#include <fstream>
#define MAX_QUEUE_SIZE 100
using namespace std;

class Heap {
public:
    vector<Node> heap;
    vector<int> location;

    Heap() {
        for(int i = 0; i < MAX_QUEUE_SIZE; i++) {
            location.push_back(-1);
        }
    }

    void heapify(int i) {
        int parent = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < heap.size() && heap[l] < heap[i])
            parent = l;

        if (r < heap.size() && heap[r] < heap[parent])
            parent = r;

        if (parent != i) {
            swap(heap[i], heap[parent]);
            swap(location.at(heap[i].ID), location.at(heap[parent].ID));
            heapify(parent);
        }
    };
    void buildHeap() {
        for(int i = heap.size() / 2; i >= 0; --i) {
            heapify(i);
        }
    };
    

};

class PriorityQueue : public Heap {
public:
    

    // PriorityQueue(string fileName) {
    //     Heap();
    //     ifstream inFS;
    //     string input;
    //     int i = 0;
    //     while(getline(inFS, input)) {
    //         heap.push_back(Node(input));
    //         location.at((int)(input.at(0) - '0')) = i;
    //         i++;
    //     }
    //     inFS.close();
    // }

    PriorityQueue() {
        Heap();
    }

    PriorityQueue& operator=(PriorityQueue& other) {
        Node currNode;
        if (this != &other) {
            heap.clear();
            for(int i = 0; i < other.heap.size(); i++) {
                currNode = other.heap.at(i);
                location.at(currNode.ID) = other.location.at(currNode.ID);
                heap.push_back(currNode);
            }
        }
        return *this;
    }

    Node extract() {
        if (heap.size() == 0) {
            throw runtime_error("The heap is empty");
        }
        Node root = heap.at(0);
        swap(heap.at(0), heap.at(heap.size() - 1));
        swap(location.at(heap.at(0).ID), location.at(heap.at(heap.size() - 1).ID));
        location.at(heap.at(heap.size() - 1).ID) = -1;
        heap.pop_back();
        

        buildHeap();
        return root;
    }

    Node* nodeID(int ID) {
        if (ID == -1) {
            return NULL;
        }

        if(location.at(ID) == -1) {

            return NULL;
        }
        else {
            return &(heap.at(location.at(ID)));
        }

    }
    void changeKey(int ID, int key) {
        if (location.at(ID) != -1) {
            nodeID(ID)->key = key;
        }
    };



};