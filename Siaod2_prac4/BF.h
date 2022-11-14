#pragma once
#ifndef _FILER_H
#define _FILER_H
#include <iostream>
#include <string>
#include <fstream>
#include "Tree.h"

struct record {
	int license;
	char name[40];
	char owner[30];
	bool empty = false;
};

class BF {
	std::string filename;
public:
	BF(std::string);
	void generateFile(int len);
	record findRecord(int key, BST* binTree);
	void changeRecord(record*, int pos);
	void deleteRecord(int key, BST* binTree);
};

#endif