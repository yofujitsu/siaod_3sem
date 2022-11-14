#pragma once
#ifndef _AVLTREE_H
#define _AVLTREE_H
#include <iostream>
using namespace std;

class AVLTree;

struct Node
{
    int license;
    int fileIndex;
    AVLTree* left = nullptr;
    AVLTree* right = nullptr;

    Node(int lic, int index) {
        this->license = lic;
        this->fileIndex = index;
    }
};

class AVLTree {
    Node* root = nullptr;
    int height = 1;

    static int rotations;
public:
    int getRotations() {
        return this->rotations;
    }

    // ���������� root->license
    int getValue();
    // ���������� root->fileIndex
    int getIndex();
    // ���������� ������� ����
    int getBalance(AVLTree* next);
    // ������ ������� ������������ ���� �
    AVLTree* rightRotate(AVLTree* y);
    // ����� ������� ������������ ���� �
    AVLTree* leftRotate(AVLTree* x);
    // ���������� ���� � ������
    AVLTree* addNode(int license, int fileIndex, AVLTree* next = nullptr);
    // ����� �������� � ������
    AVLTree* findNode(int key, AVLTree* next);
    // �������� ���� �� ������
    AVLTree* deleteNode(int key, AVLTree* next);
    // ����� ������ (���������� ����� �������)
    void display(int level, AVLTree* current);
};
#endif