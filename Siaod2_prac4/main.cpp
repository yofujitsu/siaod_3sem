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
        //Чтение записи из файла
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

    // Бинарное дерево поиска (обычное)
   
    BST* binTree = nullptr;
    int fileIndex = 0, menu = 0, k, pos;
    ifstream fin(filename, ios::binary | ios::in);
    record rec, res = {0, "", "", true};
  /*  cout << "Генерируем файл... Готово." << endl;*/

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
        cout << "Меню: " << endl;
        cout << "--бинарный файл--" << endl;
        cout << "1) Поиск записи по ключу " << endl;
        cout << "2) Удалить запись" << endl;
        cout << "--бинарное дерево поиска--" << endl;
        cout << "3) Добавить элемент в дерево" << endl;
        cout << "4) Удалить элемент из дерева" << endl;
        cout << "5) Найти элемент в дереве" << endl;
        cout << "6) Вывод дерева" << endl;
        cout << "7) обход дерева в глубину" << endl;
        cout << "8) Выход" << endl;
        cin >> menu;
        switch (menu) {
            case 1:
                cout << "Введите ключ: ";
                cin >> k;
                res = binFile.findRecord(k, binTree);
                if (res.empty != true) cout << "Запись найдена! " << res;
                else cout << "Запись не найдена :(" << endl;
                break;
            case 2:
                cout << "Введите ключ записи, которую нужно удалить: ";
                cin >> k;
                binFile.deleteRecord(k, binTree);
                cout << "Запись успешно удалена!" << endl;
                break;
            case 3:
                cout << "Введите ключ: ";
                cin >> k;
                cout << "Введите позицию в файле: ";
                cin >> pos;
                binTree->insertItem(binTree, k, pos);
                cout << "Узел успешно вставлен!" << endl;
                break;
            case 4:
                cout << "Введите ключ: ";
                cin >> k;
                binTree->deleteItem(binTree, k);
                cout << "Узел успешно удален!" << endl;
                break;
            case 5:
                cout << "Введите ключ: ";
                cin >> k;
                if (binTree->findItem(binTree, k) != nullptr) cout << "Узел найден!" << endl;
                else cout << "Такого узла нет!" << endl;
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
    
    
    // Поиск элемента
    //avltree->display(0, avltree);
    auto start = chrono::system_clock::now();
    cout << binFile.findRecord(33175032, binTree);
    //cout << findRecord(25656440, avltree);

    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << elapsed.count() << " секунд" << '\n';


    
    //АВЛ дерево
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
    //    cout << "Меню: " << endl;
    //    cout << "--АВЛ дерево--" << endl;
    //    cout << "1) Добавить элемент в дерево" << endl;
    //    cout << "2) Поиск по ключу в дереве" << endl;
    //    cout << "3) Удалить элемент из дерева" << endl;
    //    cout << "4) Вывод дерева" << endl;
    //    cout << "5) Определить число поворотов при построении СДП" << endl;
    //    cout << "6) Выход" << endl;
    //    cin >> menu;
    //    switch (menu) {
    //    case 1:
    //        cout << "Введите ключ: ";
    //        cin >> k;
    //        cout << "Введите позицию в файле: ";
    //        cin >> pos;
    //        avltree->addNode(k, pos, avltree);
    //        cout << "Элемент успешно вставлен!" << endl;
    //        break;
    //    case 2:
    //        cout << "Введите ключ записи: ";
    //        cin >> k;
    //        if (avltree->findNode(k, avltree) != nullptr) cout << "Элемент найден!" << endl;
    //        else cout << "Такого элемента нету!" << endl;
    //        break;
    //    case 3:
    //        cout << "Введите ключ: ";
    //        cin >> k;
    //        avltree->deleteNode(k, avltree);
    //        cout << "Элемент успешно удален!" << endl;
    //        break;
    //    case 4:
    //        avltree->display(0, avltree);
    //        break;
    //    case 5:
    //        cout << "Количество поворотов на 100000 элементов: " << avltree->getRotations() << endl;
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