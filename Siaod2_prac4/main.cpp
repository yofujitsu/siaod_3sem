#include <iostream>
#include<fstream>
#include<string>
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include "Tree.h"
#include "BF.h"
#include "avltree.h"
using namespace std;

string filename = "file10000.bin";

void operator<<(ostream& stream, const record r) {
    cout << r.license << " " << r.name << " " << r.owner << endl;
}

record findRecord(int key, AVLTree* binTree) {
    AVLTree* node = binTree->findNode(key, binTree);

    if (node) {
        //������ ������ �� �����
        fstream fdirect(filename, ios::binary | ios::out | ios::in);
        record rec;
        fdirect.seekg((node->getIndex()) * sizeof(record), ios::beg);
        fdirect.read((char*)&rec, sizeof(record));

        return rec;
    }
    record rec;
    rec.empty = true;
    return rec;
}

int main() {
    setlocale(0, "rus");

    BF binFile = BF("file10000.bin");

    // �������� ������ ������ (�������)
   
    BST* binTree = nullptr;
    int fileIndex = 0, menu = 0, k, pos;
    ifstream fin(filename, ios::binary | ios::in);
    record rec, res = {0, "", "", true};
  /*  cout << "���������� ����... ������." << endl;*/

    while (!fin.eof()) {
        fin.read((char*)&rec, sizeof(record));
        if (!rec.empty) {
            if (fileIndex == 0) {
                binTree = (new BST())->insertItem(binTree, rec.license, fileIndex);
            }
            else {
                binTree->insertItem(binTree, rec.license, fileIndex);
            }
        }
        fileIndex++;
    }
    /*while (menu != 8) {
        cout << "����: " << endl;
        cout << "--�������� ����--" << endl;
        cout << "1) ����� ������ �� ����� " << endl;
        cout << "2) ������� ������" << endl;
        cout << "--�������� ������ ������--" << endl;
        cout << "3) �������� ������� � ������" << endl;
        cout << "4) ������� ������� �� ������" << endl;
        cout << "5) ����� ������� � ������" << endl;
        cout << "6) ����� ������" << endl;
        cout << "7) ����� ������ � �������" << endl;
        cout << "8) �����" << endl;
        cin >> menu;
        switch (menu) {
            case 1:
                cout << "������� ����: ";
                cin >> k;
                res = binFile.findRecord(k, binTree);
                if (res.empty != true) cout << "������ �������! " << res;
                else cout << "������ �� ������� :(" << endl;
                break;
            case 2:
                cout << "������� ���� ������, ������� ����� �������: ";
                cin >> k;
                binFile.deleteRecord(k, binTree);
                cout << "������ ������� �������!" << endl;
                break;
            case 3:
                cout << "������� ����: ";
                cin >> k;
                cout << "������� ������� � �����: ";
                cin >> pos;
                binTree->insertItem(binTree, k, pos);
                cout << "���� ������� ��������!" << endl;
                break;
            case 4:
                cout << "������� ����: ";
                cin >> k;
                binTree->deleteItem(binTree, k);
                cout << "���� ������� ������!" << endl;
                break;
            case 5:
                cout << "������� ����: ";
                cin >> k;
                if (binTree->findItem(binTree, k) != nullptr) cout << "���� ������!" << endl;
                else cout << "������ ���� ���!" << endl;
                break;
            case 6:
                binTree->display(0, binTree);
                cout << endl;
                break;
            case 7:
                binTree->traverseNLR(binTree);
                cout << endl;
                break;
            case 8:
                exit(0);
                break;
            default:
                break;
        }
    }*/
    
    
    // ����� ��������
    //avltree->display(0, avltree);
    auto start = chrono::system_clock::now();
    cout << binFile.findRecord(33175032, binTree);
    //cout << findRecord(25656440, avltree);

    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << elapsed.count() << " ������" << '\n';


    
    //��� ������
    AVLTree* avltree = new AVLTree();
    int fileIndex = 0, menu = 0, k, pos;
    ifstream fin(filename, ios::binary | ios::in);
    record rec;
    while (!fin.eof()) {
        fin.read((char*)&rec, sizeof(record));
        //cout << rec;
        if (!rec.empty)
        {
            if (fileIndex == 0) {
                avltree = avltree->addNode(rec.license, fileIndex);
            }
            else
                avltree = avltree->addNode(rec.license, fileIndex, avltree);
        }
        fileIndex++;
    }
    //while (menu != 6) {
    //    cout << "����: " << endl;
    //    cout << "--��� ������--" << endl;
    //    cout << "1) �������� ������� � ������" << endl;
    //    cout << "2) ����� �� ����� � ������" << endl;
    //    cout << "3) ������� ������� �� ������" << endl;
    //    cout << "4) ����� ������" << endl;
    //    cout << "5) ���������� ����� ��������� ��� ���������� ���" << endl;
    //    cout << "6) �����" << endl;
    //    cin >> menu;
    //    switch (menu) {
    //    case 1:
    //        cout << "������� ����: ";
    //        cin >> k;
    //        cout << "������� ������� � �����: ";
    //        cin >> pos;
    //        avltree->addNode(k, pos, avltree);
    //        cout << "������� ������� ��������!" << endl;
    //        break;
    //    case 2:
    //        cout << "������� ���� ������: ";
    //        cin >> k;
    //        if (avltree->findNode(k, avltree) != nullptr) cout << "������� ������!" << endl;
    //        else cout << "������ �������� ����!" << endl;
    //        break;
    //    case 3:
    //        cout << "������� ����: ";
    //        cin >> k;
    //        avltree->deleteNode(k, avltree);
    //        cout << "������� ������� ������!" << endl;
    //        break;
    //    case 4:
    //        avltree->display(0, avltree);
    //        break;
    //    case 5:
    //        cout << "���������� ��������� �� 100000 ���������: " << avltree->getRotations() << endl;
    //        break;
    //    case 6:
    //        exit(0);
    //        break;
    //    default:
    //        break;
    //    }
    //}


    //// RAM used
    //PROCESS_MEMORY_COUNTERS_EX pmc;
    //GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    //SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
    //SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
    //std::cout << physMemUsedByMe << '\n';

	return 0;
}