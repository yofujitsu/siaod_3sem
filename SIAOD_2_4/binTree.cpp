#include "binTree.h"
#include "Node.h"
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

void binTree::BuildByFile(string bin) {
    ifstream file(bin, ios::binary | ios::in);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return;
    }
    Node node;
    int i = 0;
    while (file.read((char*)&node, sizeNode)) {
        addNode(root, node.name, i);
        i++;
    }
    file.close();
}

int binTree::height(binTree::Node* p) {
    return p ? p->height : 0;
}

int binTree::fixheight(binTree::Node* p) {
    int hl = height(p->left);
    int hr = height(p->right);
    return (hl > hr ? hl : hr) + 1;
}


void binTree::addNode(Node*& node, int key, int index) {
    if (node == nullptr) {
        node = new Node;
        strcpy(node->key, key);
        node->index = index;
        node->left = nullptr;
        node->right = nullptr;
        node->height = fixheight(node);
        size++;
    }
    else if (strcmp(key, node->key) < 0) {
        addNode(node->left, key, index);
    }
    else if (strcmp(key, node->key) > 0) {
        addNode(node->right, key, index);
    }
}

void binTree::deleteByKey(Node*& node, int key) {
    if (node == nullptr) {
        return;
    }
    else if (strcmp(key, node->key) < 0) {
        deleteByKey(node->left, key);
    }
    else if (strcmp(key, node->key) > 0) {
        deleteByKey(node->right, key);
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        else if (node->left == nullptr) {
            Node* temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node;
            node = node->left;
            delete temp;
        }
        else {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            strcpy(node->key, temp->key);
            node->index = temp->index;
            deleteByKey(node->right, temp->key);
        }
    }
}

int binTree::searchByKey(Node* node, int key) {
    if (node == nullptr) {
        cout << "Not found" << endl;
        return -1;
    }
    else if (strcmp(key, node->key) < 0) {
        searchByKey(node->left, key);
    }
    else if (strcmp(key, node->key) > 0) {
        searchByKey(node->right, key);
    }
    else {
        cout << "Found" << node->key << " at " << node->index << endl;
        return node->index;
    }
}

void binTree::print(Node* node, string offset) {
    if (node == nullptr) {
        return;
    }
    printTree(node->right, offset + "   ");
    cout << offset << node->key << " Pos: " << node->index << endl;
    printTree(node->left, offset + "   ");
}

void binTree::printTree(Node* element, string prefix, bool root) {
    if (root) {
        element = this->root;
    }

    if (!element) return;

    if (element->right) {
        printTree(element->right, prefix + (root ? "    " : "│   "), false);
    }
    cout << prefix << (root ? "└── " : "├── ") << element->key << " " << element->index << endl;
    if (element->left) {
        printTree(element->left, prefix + (root ? "    " : "│   "), false);
    }
}

