
#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include "Node.h"

using namespace std;

class AVLTree {
public:
    struct Node {
        char key[45];
        int index;

        Node* left;
        Node* right;
        int height;
    };
    Node* root = nullptr;
    int size;
    int rotations = 0;

    void BuildByFile(string bin);
    int height(Node* p);
    int bfactor(Node* p);
    void fixheight(Node* p);
    Node* rotateright(Node* p);
    Node* rotateleft(Node* q);
    Node* balance(Node* p);
    Node* insert(Node* p, char* k, int index);

    Node* findMin(Node* p);
    Node* removeMin(Node* p);
    Node* deleteNode(Node* p, char* k);

    int search(char* k);

    void print(Node* p, string prefix);
    void printTree(Node* element = nullptr, string  prefix = "", bool root = true);




};


#endif 

