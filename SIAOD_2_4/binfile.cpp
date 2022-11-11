#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include "Node.h"
#include "binfile.h"
using namespace std;

void printNoteNative(Node node) {
    cout << "Узел: " << node.name << " " << node.founder << " " << node.licence_id << endl;
}


void binfile::textToBin(string text, string bin) {
    ifstream fin(text, ios::in);
    ofstream fout(bin, ios::binary | ios::out);
    string line;
    while (getline(fin, line)) {
        Node node;
        stringstream ss(ios::in | ios::out);
        ss << line;
        ss >> node.name >> node.founder >> node.licence_id;

        fout.write((char*)&node, sizeNode);
    }
    fin.close();
    fout.close();
}

int binfile::searchBin(int bin, string name) {
    ifstream fin(bin, ios::binary | ios::in);
    Node node;
    int i = 0;
    while (!fin.eof()) {
        fin.read((char*)&node, sizeNode);

        if (strcmp(node.name, name.c_str()) != 0) {
            printNoteNative(node);
            return i;
        }

        i++;
    }
    fin.close();
    return -1;
}

Node binfile::directAccessBin(string bin, int index) {
    ifstream fin(bin, ios::binary | ios::in);
    Node node;
    fin.seekg(index * sizeNode);
    fin.read((char*)&node, sizeNode);
    printNoteNative(node);
    fin.close();
    return node;
}

void binfile::addBin(string bin, Node node) {
    ofstream fout(bin, ios::binary | ios::app);
    fout.write((char*)&node, sizeNode);
    fout.close();
}
