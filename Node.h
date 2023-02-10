#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <sstream>
using namespace std;

//this function is to store the information for each node that need to be explored
class Node{
    public:
        unsigned gn;
        unsigned hn;
        vector<vector<string>> puzzle;
        pair<int,int> zero;

        string twodtostring();
        bool goal();
        Node();
        Node(vector<vector<string>> puzz);
        void findgnandhncost(int algorithm_choice);
        int cost() const;
        bool operator<(const Node& lhs) const;
        void printpuzzle();
};

#endif
