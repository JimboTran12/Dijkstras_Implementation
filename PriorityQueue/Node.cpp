
#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<cstdlib>
#include<climits>
#include<cctype>
using namespace std;

class Node {
public:
    int ID;
    vector<int> adjID;
    vector<double> w;
    int parentID;
    int parentW;
    double key;
    vector<int> edges;
    vector<double> edgesW;
    Node(){}
    Node(int ID) {this->ID = ID;}

    Node(string info) {
        istringstream iss(info);
        string word;
        getline(iss, word, ' ');
        this->ID = stoi(word);
        while(getline(iss, word, ' ')) {
            if (!isspace(word.at(0)))  {
                adjID.push_back(stod(word));
                getline(iss, word, ' ');
                w.push_back(stod(word));
            }
        }
        parentID = -1;
        key = INT_MAX;
    }

    Node& operator=(const Node& other) {
        if(this != &other) {
            this->ID = other.ID;
            this->adjID = other.adjID;
            this->w = other.w;
            this->parentID = other.parentID;
            this->parentW = other.parentW;
            this->key = other.key;
            this->edges = other.edges;
            this->edgesW = other.edgesW;

        }
        return *this;
    }

    // Node(Node& other) {
    //     this->ID = other.ID;
    //     this->parentID = -1;
    //     this->key = other.key;
    //     this->adjID = other.adjID;
    //     this->w = other.w;
    // }
    void print() {
        for (int i = 0; i < adjID.size(); i++) {
            cout << adjID.at(i) << "|" << w.at(i) << " ";
        }
    }



    bool operator<(const Node& other) {
        return (this->key < other.key);
    }

    
};