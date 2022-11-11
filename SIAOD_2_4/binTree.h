#ifndef _BINTREE_H
#define _BINTREE_H

#include <string>
using namespace std;

class binTree {
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

    int height(Node* p);
    int fixheight(binTree::Node* p);
    void BuildByFile(string bin);
    void addNode(Node*& node, char* key, int index);
    void deleteByKey(Node*& node, char* key);
    int searchByKey(Node* node, char* key);
    void directAccess(Node* node, int index);
    void print(Node* node, string offset);
    void printTree(Node* element = nullptr, string  prefix = "", bool root = true);



};

#endif 
