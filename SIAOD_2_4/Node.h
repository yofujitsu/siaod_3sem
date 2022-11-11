#ifndef _NODE_H
#define _NODE_H
#include <iostream>
#include <string>

using namespace std;

struct Node {
    string name;
    string founder;
    int license_id; //key
};

const int sizeNode = sizeof(Node);


#endif
