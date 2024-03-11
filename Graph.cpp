#pragma once
#include"./PriorityQueue/PriorityQueue.cpp"
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<chrono>
using namespace std;

class Graph {
public:
    PriorityQueue nodes;
    PriorityQueue queue;
    int size;
    double totalDistance;
    int circuit;
    chrono::microseconds timer;
    int step;
    vector<int> path;


    Graph(PriorityQueue& queue, int rootNodeID) {
        this->nodes = queue;
        this->queue = nodes;
        this->nodes.changeKey(rootNodeID,0);
        this->queue.changeKey(rootNodeID,0);
        //this->queue.buildHeap();
        this->size = nodes.heap.size();
        totalDistance = INT_MAX;
    }
    void backtrack(Node* node, int steps, double distance) {
        

        if (distance > totalDistance || queue.nodeID(0)->key == 2) {
            return;
        }
        //check if there's a hamiltonion circuit
        if (steps == this->size && node->adjID.at(0) == 0) {
            distance += node->w.at(0);
            if(distance < totalDistance) {
                totalDistance = distance;
                nodes = queue;
                circuit = node->ID;
            }
            node->key = 2;
            return;
        }
        node->key = 1; //set color to grey
        for(int i = 0; i < node->adjID.size(); i++) {
            if(queue.nodeID(node->adjID.at(i))->key == 0 || queue.nodeID(node->adjID.at(i))->key == 2) {
                queue.nodeID(node->adjID.at(i))->parentID = node->ID;
                backtrack(queue.nodeID(node->adjID.at(i)), steps + 1, distance + node->w.at(i));
            }
        }
        node->key = 2; //set color to black
    }

    void bruteForce() {
        auto beg = chrono::high_resolution_clock::now();
        for(int i = 0; i < size; i++) {
            this->nodes.heap.at(i).key = 0; //initalize all nodes to white
            this->nodes.heap.at(i).parentID = -1; //initalize all nodes' parents to null
        }
        queue = nodes;
        totalDistance = INT_MAX;
        backtrack(this->queue.nodeID(0), 1, 0.0);
        auto end = chrono::high_resolution_clock::now();
        this->timer = chrono::duration_cast<chrono::microseconds>(end - beg);

    }

    void DFS_Visit(Node* node, int steps, double distance) {
        step++;
        path.push_back(node->ID);

        //check if the end node is reached
        if (step == size) {

            node->key = 2;

            nodes = queue;
            return;
        }
        node->key = 1; //set color to grey
        for(int i = 0; i < node->edges.size(); i++) {
            if(queue.nodeID(node->edges.at(i))->key == 0) {
                queue.nodeID(node->edges.at(i))->parentID = node->ID;
                DFS_Visit(queue.nodeID(node->edges.at(i)), steps + 1,  node->edgesW.at(i));
            }
        }
        node->key = 2; //set color to black
        
    }

    void DFS() {
        auto beg = chrono::high_resolution_clock::now();
        for(int i = 0; i < size; i++) {
            this->nodes.heap.at(i).key = 0; //initalize all nodes to white
            this->nodes.heap.at(i).parentID = -1; //initalize all nodes' parents to null
        }
        queue = nodes;
        step = 0;
        totalDistance = 0;
        DFS_Visit(this->queue.nodeID(0), 1, 0.0);
        for(int i = 0; i < size - 1; i++) {
            bool found = false;
            for(int j = 0; j < nodes.nodeID(path.at(i))->adjID.size(); j++) {
                if(nodes.nodeID(path.at(i))->adjID.at(j) == path.at(i+1)) {
                    totalDistance += nodes.nodeID(i)->w.at(j);
                    found = true;
                }
            }
            if (!found) {
                cout << "Edge (" << path.at(i) << "," << path.at(i+1) << ") not found" << endl;
            }
        }
        totalDistance += nodes.nodeID(path.at(path.size()-1))->w.at(0);
        auto end = chrono::high_resolution_clock::now();
        this->timer = chrono::duration_cast<chrono::microseconds>(end - beg);

    }


    void MST() {
        Node currNode;
        queue.buildHeap();
        while(queue.heap.size() > 0) {
            currNode = queue.extract();
            for(int i = 0; i < currNode.adjID.size(); i++) {
                if(queue.nodeID(currNode.adjID.at(i)) != NULL && currNode.w.at(i) < nodes.nodeID(currNode.adjID.at(i))->key) {
                    nodes.nodeID(currNode.adjID.at(i))->parentID = currNode.ID;
                    nodes.nodeID(currNode.adjID.at(i))->parentW = currNode.w.at(i);
                    nodes.changeKey(currNode.adjID.at(i), currNode.w.at(i));
                    queue.changeKey(currNode.adjID.at(i), currNode.w.at(i));
                    queue.buildHeap();
                }
            }
        }
        for(int i = 0; i < nodes.heap.size(); i++) {
            if (nodes.heap.at(i).parentID != -1) {
                nodes.heap.at(i).edges.push_back(nodes.heap.at(i).parentID);
                nodes.nodeID(nodes.heap.at(i).parentID)->edges.push_back(nodes.heap.at(i).ID);
                nodes.heap.at(i).edgesW.push_back(nodes.heap.at(i).parentW);
                nodes.nodeID(nodes.heap.at(i).parentID)->edgesW.push_back(nodes.heap.at(i).parentW);
            }         
        }

    }

    void shortestPath() {
        Node currNode;
        while(queue.heap.size() > 0) {
            currNode = queue.extract();
            for(int i = 0; i < currNode.adjID.size(); i++) {
                if(queue.nodeID(currNode.adjID.at(i)) != NULL && nodes.nodeID(currNode.adjID.at(i))->key > currNode.w.at(i) + currNode.key) {
                    nodes.nodeID(currNode.adjID.at(i))->parentID = currNode.ID;
                    nodes.nodeID(currNode.adjID.at(i))->parentW = currNode.w.at(i) + currNode.key;
                    nodes.changeKey(currNode.adjID.at(i), currNode.w.at(i) + currNode.key);
                    queue.changeKey(currNode.adjID.at(i), currNode.w.at(i) + currNode.key);
                    queue.buildHeap();
                }
            }
        }
        for(int i = 0; i < nodes.heap.size(); i++) {
            if (nodes.heap.at(i).parentID != -1) {
                nodes.heap.at(i).edges.push_back(nodes.heap.at(i).parentID);
                nodes.nodeID(nodes.heap.at(i).parentID)->edges.push_back(nodes.heap.at(i).ID);
                nodes.heap.at(i).edgesW.push_back(nodes.heap.at(i).parentW);
                nodes.nodeID(nodes.heap.at(i).parentID)->edgesW.push_back(nodes.heap.at(i).parentW);
            }         
        }

    }

    void reset(int rootID) {
        vector<int> empty1;
        vector<double> empty2;
        for(int i = 0; i < nodes.heap.size(); i++) {
            nodes.heap.at(i).key = INT_MAX;
            nodes.heap.at(i).edges = empty1;
            nodes.heap.at(i).edgesW = empty2;
            nodes.heap.at(i).parentID = -1;
            nodes.location.at(nodes.heap.at(i).ID) = i;
        }
        nodes.changeKey(rootID,0);
        queue = nodes;
        queue.buildHeap();
    }



    void print(ostringstream& outputStream, int graphNum) {
        outputStream << "MST: " << endl;
        for(int i = 0; i < nodes.heap.size(); i++) {
            
            outputStream << fixed << setprecision(1) << "Node " << nodes.heap.at(i).ID << " adjacent nodes: ";
            for (int j = 0; j < nodes.heap.at(i).edges.size(); j++) {
                outputStream << nodes.heap.at(i).edges.at(j) << " ";
            }
            outputStream << endl;
        }
        outputStream << endl;
 
    }

    void printPath(ostringstream& outputStream, int graphNum) {
        Node* currNode = nodes.nodeID(circuit);
        outputStream << fixed << setprecision(2);
        outputStream << "In graph " << graphNum <<": " << endl;
        outputStream <<  "Minimum distance: " << totalDistance << endl << "Tour: ";
        while(currNode != NULL) {
            outputStream << currNode->ID << " ";
            cout << currNode->parentID << endl;
            currNode = nodes.nodeID(currNode->parentID);
        }
        outputStream << endl << "Elapsed time: " << this->timer.count() / 1000.0 << "ms" << endl;
        outputStream  << endl;
    }

    void printPath2(ostringstream& outputStream, int graphNum) {
        outputStream << fixed << setprecision(2);
        outputStream << "In graph " << graphNum <<": " << endl;
        outputStream <<  "Distance: " << totalDistance << endl << "Tour: ";
        for (int i = 0; i < path.size(); i++) {
            outputStream << path.at(i) << " ";
        }
        outputStream << endl << "Elapsed time: " << this->timer.count() / 1000.0 << "ms" << endl;
        //outputStream  << endl;
    }
};

