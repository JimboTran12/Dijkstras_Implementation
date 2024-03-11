//#include "./oldPriorityQueue/PriorityQueue.h"
//#include "./oldPriorityQueue/hi.h"
#include"./PriorityQueue/Node.cpp"
#include"./PriorityQueue/PriorityQueue.cpp"
#include"Graph.cpp"
#include<fstream>
#include <iostream>
using namespace std;

int main() { 
    string fileName = "";
    string outputBF = "BFOut.txt";
    string outputApprox = "ApproxOut.txt";
    ostringstream oss;
    ostringstream oss2;
    string input;

    for (int fileNum = 1; fileNum <= 10; fileNum++) {
        PriorityQueue queue;
        fileName = "graphs/graph" + to_string(fileNum);
        fileName += ".txt";

        ifstream inFS(fileName);
        int i = 0;
        while(getline(inFS, input)) {
            queue.heap.push_back(Node(input));
            queue.location.at(i) = i;
            i++;
        }
        inFS.close();
        Graph graph(queue, 0);
        graph.bruteForce();
        graph.printPath(oss, fileNum);
    }
    cout << oss.str();
    ofstream BFstream(outputBF);
    BFstream << oss.str();
    BFstream.close();

    


    for (int fileNum = 1; fileNum <= 10; fileNum++) {
        PriorityQueue queue;
        fileName = "graphs/graph" + to_string(fileNum);
        fileName += ".txt";

        ifstream inFS(fileName);
        int i = 0;
        while(getline(inFS, input)) {
            queue.heap.push_back(Node(input));
            queue.location.at(i) = i;
            i++;
        }
        inFS.close();
        Graph graph(queue, 0);
        graph.MST();
        graph.DFS();
        graph.printPath2(oss2, fileNum);
        graph.print(oss2, fileNum);
    }
    cout << oss2.str();
    ofstream ApproxStream(outputApprox);
    ApproxStream << oss2.str();
    ApproxStream.close();


 
 


    
    return 0;
}
