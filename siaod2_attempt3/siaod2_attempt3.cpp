#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <forward_list>
#include <random>
#include <chrono>

using namespace std;

struct company
{
	int id; //key
	string name;
	string founder;
};

struct keys
{
	int id;
	int filePosition;
};

class HashTable
{
	forward_list<keys>* table;
	int capacity; //размер таблицы
	int size; //кол-во элементов в таблице
public:
	HashTable(int k);
	~HashTable();
	void resize();
	void insertItem(keys);
	void addCompany();
	void deleteItem();
	void findItem();
	int getSize() { return size; }
	int getHash(int key){ return (key % capacity); }
	void printTable();
};

HashTable::HashTable(int x)
{
	this->capacity = x;
	table = new forward_list<keys>[capacity];
}

HashTable::~HashTable() { delete[] table; }

void HashTable::resize()
{
	forward_list<keys>* temp = new forward_list<keys>[capacity * 2];
	capacity *= 2;
	for (auto i = 0; i < capacity; ++i)
	{
		for (auto j = table[i].begin(); j != table[i].end(); ++j)
		{
			keys t = *(j);
			temp[getHash(t.id)].push_front(t);
		}
	}
	delete[] table;
	table = temp;
}

void HashTable::insertItem(keys elem)
{
	int index = getHash(elem.id);
	table[index].push_front(elem);
	size++;
	if (double(size) / double(capacity) >= 0.75) { resize(); }
}

void HashTable::addCompany()
{
	string founder, name;
	int id;
	cout << "Введите название предприятия: " << endl;
	cin >> name;
	cout << "Введите учредителя: " << endl;
	cin >> founder;
	cout << "Введите номер лицензии: " << endl;
	cin >> id;
	company* addCompany = new company();
	addCompany->name = name;
	addCompany->founder = founder;
	addCompany->id = id;
	keys key;
	key.id = id;
	key.filePosition = size;
	insertItem(key);
	ofstream fout;
	fout.open("Companies.bin", ios::binary | ios::app);
	fout.write((char*)&addCompany, sizeof(addCompany));
	fout.close();
}

void HashTable::deleteItem()
{
	int key, position = -1;
	cout << "Введите номер лицензии компании, которую хотите удалить: " << endl;
	cin >> key;
	int index = getHash(key);
	forward_list<keys>::iterator i, deleter;
	for (i = table[index].begin(), deleter = table[index].before_begin();
		i != table[index].end(); ++i, ++deleter)
	{
		if (i->id == key)
		{
			position = i->filePosition;
			break;
		}
	}

	if (i != table[index].end()) table[index].erase_after(deleter);

	ifstream fin;
	fin.open("Companies.bin", ios::binary | ios::in);
	company* Company = new company();
	vector<company*> v;
	for (int i = 0; i < size; ++i)
	{
		fin.read((char*)&Company, sizeof(Company));
		if (i == position) break;
		v.push_back(Company);
	}
	for (int i = position + 1; i < size; ++i)
	{
		fin.read((char*)&Company, sizeof(Company));
		v.push_back(Company);
		int key = Company->id;
		int hash = getHash(key);
		for (auto j = table[hash].begin(); j != table[hash].end(); ++j)
		{
			if ((*j).id == key)
			{
				(*j).filePosition--;
				break;
			}
		}
	}
	fin.close();
	size--;
	ofstream fout;
	fout.open("Companies.bin", ios::binary | ios::out | ios::trunc);
	for (int j = 0; j < v.size(); ++j)
	{
		fout.write((char*)&v[j], sizeof(v[j]));
	}

	fout.close();
	printTable();
}

void HashTable::findItem()
{
	cout << "Введите номер лицензии: " << endl;
	int key;
	cin >> key;
	int index = getHash(key);
	int position = -1;
	forward_list<keys>::iterator i;
	for (i = table[index].begin(); i != table[index].end(); ++i)
	{
		if (i->id == key)
		{
			position = i->filePosition;
			break;
		}
	}

	if (i != table[index].end())
	{
		ifstream file;
		file.open("Companies.bin", ios::binary | ios::in);
		company* Company = new company();
		file.seekg(sizeof(Company) * position, file.beg);
		file.read((char*)&Company, sizeof(Company));
		cout << "Название предприятия: " << Company->name << \
			"; Учредитель: " << Company->founder << "; Номер лицензии : " << Company->id << endl;
		file.close();
	}
	else { cout << "Предприятие не найдено." << endl; }
}

void HashTable::printTable()
{
	for (int i = 0; i < capacity; ++i)
	{
		cout << "HashTable[" << i << "]";
		for (auto x : table[i]) cout << " ==> " << x.id;
		cout << endl;
	}

	cout << "Колчиество элементов в таблице и файле: " << size << endl;
}

void fromFileToTable(HashTable& h, int length)
{
	ifstream fin;
	fin.open("Companies.bin", ios::binary | ios::in);
	for (int i = 0; i < length; ++i)
	{
		company* Company = new company();
		fin.read((char*)&Company, sizeof(Company)); //считали информацию
		keys key;
		key.id = Company->id;
		key.filePosition = i;
		h.insertItem(key);
	}
	fin.close();
}

string randomString(int length)
{
	static const char alphabet[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string tmp_s;
	tmp_s.reserve(length);

	for (int i = 0; i < length; ++i) {
		tmp_s += alphabet[rand() % (sizeof(alphabet) - 1)];
	}

	return tmp_s;
}

void generateRandomFile(int length)
{
	ofstream fout;
	fout.open("Companies.bin", ios::binary | ios::out | ios::trunc);
	int id;
	string name;
	string founder;
	for (int i = 0; i < length; ++i)
	{
		id = 1 + rand() % 999999;
		name = randomString(5);
		founder = randomString(10);
		company* Company = new company();
		Company->id = id;
		Company->founder = founder;
		Company->name = name;
		fout.write((char*)&Company, sizeof(Company));
	}
	fout.close();
}

void createFile(int length)
{
	ofstream fout;
	fout.open("Companies.bin", ios::binary | ios::out | ios::trunc);
	int id;
	string name;
	string founder;
	for (int i = 0; i < length; ++i)
	{
		cout << "Введите название предприятия: ";
		cin >> name;
		cout << "Введите учредителя: ";
		cin >> founder;
		cout << "Введите номер лицензии: ";
		cin >> id;
		company* Company = new company();
		Company->id = id;
		Company->founder = founder;
		Company->name = name;
		fout.write((char*)&Company, sizeof(Company));
	}
	fout.close();
}

int main()
{
	setlocale(0, "rus");
	int menu, length;
	cout << "Введите количество записей: ";
	cin >> length;
	createFile(length);
	//generateRandomFile(length);
	HashTable* h = new HashTable(10);
	fromFileToTable(*h, length);
	//h->printTable();
	//auto start_time = std::chrono::steady_clock::now();
	//h->findItem();
	//auto end_time = chrono::steady_clock::now();
	//auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
	//cout << endl << elapsed_ns.count() << " ns\n";
	//cout << endl;
	h->printTable();
	cout << "\nМеню\n";
	cout << "1) Добавить предприятие\n2) Удалить по номеру\n3) Найти предприятие по номеру\n4) Выход\n";
	cin >> menu;
	while (menu != 4)
	{
		switch (menu)
		{
		case 1:
			h->addCompany();
			h->printTable();
			break;
		case 2:
			h->deleteItem();
			break;
		case 3:
			h->findItem();
			break;
		case 4:
			h->printTable();
			break;
		default:
			break;
		}
		cout << "1) Добавить предприятие\n2) Удалить по номеру\n3) Найти предприятие по номеру\n4) Выход\n";
		cin >> menu;
	}
	return(0);
}