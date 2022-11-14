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

    // Возвращает root->license
    int getValue();
    // Возвращает root->fileIndex
    int getIndex();
    // Вычисление баланса узла
    int getBalance(AVLTree* next);
    // Правый поворот относительно узла у
    AVLTree* rightRotate(AVLTree* y);
    // Левый поворот относительно узла х
    AVLTree* leftRotate(AVLTree* x);
    // Добавление узла в дерево
    AVLTree* addNode(int license, int fileIndex, AVLTree* next = nullptr);
    // Поиск элемента в дереве
    AVLTree* findNode(int key, AVLTree* next);
    // Удаление узла из дерева
    AVLTree* deleteNode(int key, AVLTree* next);
    // Вывод дерева (повернутым слева направо)
    void display(int level, AVLTree* current);
};
#endif