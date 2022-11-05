#include <iostream>
#include <string>
#include <cmath>
#include <random>

using namespace std;

struct node {
	char data;
	node* l = nullptr; 
	node* r = nullptr;
};

class Tree {
	node* root;
public:
	Tree() {
		root = nullptr;
	}
	void createTree(node* T, int n)
	{
		int nl = 0, nr = 0;
		if (n != 0)
		{
			T->data = rand() % 95 + 32;
			nl = n / 2;
			nr = n - nl - 1;
			if (nl != 0)
			{
				T->l = new node;
				createTree(T->l, nl);
			}
			if (nr != 0)
			{
				T->r = new node;
				createTree(T->r, nr);
			}
		}
	}

	void mirroringOperation(node* T, int n) {
		int nl = 0, nr = 0;
		if (T) {
			if (n != 0) {
				node* temp_node = new node;
				temp_node = T->r;
				T->r = T->l;
				T->l = temp_node;
				nl = n / 2;
				nr = n - nl - 1;
				mirroringOperation(T->l, nl);
				mirroringOperation(T->r, nr);
			}
		}
		
	}

	int detectNodeHeight(node* T, char x, int level = 1)
	{
		if (T->data == x) return level;
		if (T->l)
		{
			int leftValue = detectNodeHeight(T->l, x, level + 1);
			if (leftValue) return leftValue;
		}
		if (T->r) return detectNodeHeight(T->r, x, level + 1);
		return 0;
	}

	void printTreeVertically(node* T, int depth)
	{
		if (T)
		{
			printTreeVertically(T->l, depth + 1);
			for (int i = 0; i < depth; ++i)
			{
				cout << "\t";
			}
			cout << T->data << endl;
			printTreeVertically(T->r, depth + 1);
		}
	}

	int countLeftElements(node* T)
	{
		if (!T->r && !T->l) return 1;
		if (!T->r) return countLeftElements(T->l) + 1;
		if (!T->l) return countLeftElements(T->r) + 1;
		return countLeftElements(T->l) + countLeftElements(T->r);
	}

	int leftTreeCounter(node* T)
	{
		int n = 0;
		if (T->data > 47 && T->data < 58) n++;
		if (T->l)
			if(T->l->data > 47 && T->l->data < 58)
				n += leftTreeCounter(T->l);
		if (T->r)
			if (T->r->data > 47 && T->r->data < 58)
				n += leftTreeCounter(T->r);
		return n;
	}
	~Tree() {
		delete(root);
	}
};

int main()
{
	setlocale(0, "rus");
	int i = 0, count = 0;
	node* T = new node;
	srand(time(0));
	Tree* tree = new Tree();
	cout << "Инициализация дерева. Сколько элементов в дереве? ";
	cin >> count;
	tree->createTree(T, count);
	cout << "\nДерево успешно создано.\n";
	while (i != 7) {
		cout << "\nМеню:" << endl
			<< "1) Вывод дерева вертикально" << endl
			<< "2) Отражение дерева" << endl
			<< "3) Определить уровень, на котором находится значение" << endl
			<< "4) Вывод количества цифр в левом поддереве" << endl
			<< "5) Выход" << endl;
		cin >> i;

		switch (i)
		{
		case 1:
			cout << "\nВывод дерева вертикально: \n";
			tree->printTreeVertically(T, 0);
			break;
		case 2:
			tree->mirroringOperation(T, count);
			cout << "\nДерево успешно отражено.\n";
			break;
		case 3:
			char x;
			cout << "\nВведите значение: ";
			cin >> x;
			if (tree->detectNodeHeight(T, x) == 0) cout << "Такого элемента нет.\n";
			else cout << x << " находится на " << tree->detectNodeHeight(T, x) << " уровне." << endl;
			break;
		case 4:
			cout << "\nКоличество цифр в левом поддреве: " << tree->leftTreeCounter(T->l) << endl;
			break;
		case 5:
			system("pause");
			return(0);
		default:
			break;
		}
	}
}
