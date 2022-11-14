#include "BF.h"
using namespace std;

BF::BF(string filename) {
	this->filename = filename;
}

void BF::generateFile(int len) {
	srand(time(NULL));
	ofstream fout("file" + to_string(len) + ".bin", ios::out | ios::binary);
	record* x = new record[len];
	for (int i = 0; i < len; i++) {
		x[i].license = rand() << 10 | rand();
		strcpy_s(x[i].name, ("name" + to_string(i)).c_str());
		strcpy_s(x[i].owner, ("owner" + to_string(i)).c_str());
		x->empty = false;
	}
	fout.write((char*)x, len * sizeof(record));
	fout.close();
}

record BF::findRecord(int key, BST* binTree) {
	BST* node = binTree->findItem(binTree, key);

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

void BF::changeRecord(record* r, int pos)
{
	fstream fdirect(filename, ios::binary | ios::out | ios::in);
	fdirect.seekg(pos * sizeof(record), ios::beg);
	record temp;
	fdirect.read((char*)&temp, sizeof(record));
	if ((r->empty) || (r->license == temp.license)) {
		fdirect.seekg(pos * sizeof(record), ios::beg);
		fdirect.write((char*)r, sizeof(record));
	}
	fdirect.close();
}

void BF::deleteRecord(int key, BST* binTree) {
	record* r = new record();
	r->empty = true;
	BST* del = binTree->findItem(binTree, key);
	if (del) {
		binTree = binTree->deleteItem(binTree, key);
		changeRecord(r, del->getIndex());
	}
}