#pragma once
#ifndef _TREE_H
#define _TREE_H
#include <iostream>

class BST {
	int license;
	int fileIndex;

	BST* left = nullptr;
	BST* right = nullptr;
public:

	BST();
	BST(int lic, int indx);

	int getIndex() {
		return this->fileIndex;
	}
	void setRight(BST* right) {
		this->right = right;
	}
	void setLeft(BST* left) {
		this->left = left;
	}

	// Добавление узла в дерево
	BST* insertItem(BST* root, int license, int fileIndex);
	// Поиск элемента в дереве
	BST* findItem(BST* root, int license);
	// Удаление элемента из дерева
	BST* deleteItem(BST* root, int lic);
	// Вывод дерева на экран
	void display(int level = 0, BST* current = nullptr);
	// Прямой обход дерева в глубину
	void traverseNLR(BST* current);
};

#endif