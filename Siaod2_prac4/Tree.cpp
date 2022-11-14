#include "Tree.h"

BST::BST() : license(0) {}

BST::BST(int lic, int index) {
	this->license = lic;
	this->fileIndex = index;
}

BST* BST::insertItem(BST* root, int license, int fileIndex) {
	// Добавление корня
	if (!root) {
		return new BST(license, fileIndex);
	}
	// Добавление листа //
	
	// Вставка в левое поддерево
	if (license < root->license) {
		root->left = insertItem(root->left, license, fileIndex);
	}
	// Вставка в правое поддерево
	else if (license > root->license) {
		root->right = insertItem(root->right, license, fileIndex);
	}

	return root;
}

BST* BST::findItem(BST* root, int lic)
{
    // Элемента нет в дереве
    if (!root)
        return root;

    // Поиск элемента в дереве
    if (root->license > lic) {
        return findItem(root->left, lic);
    }
    else if (root->license < lic) {
        return findItem(root->right, lic);
    }

    return root;
}

BST* BST::deleteItem(BST* root, int lic)
{
    // Элемента нет в дереве
    if (!root)
        return root;

    // Поиск элемента в дереве
    if (root->license > lic) {
        root->left = deleteItem(root->left, lic);
        return root;
    }
    else if (root->license < lic) {
        root->right = deleteItem(root->right, lic);
        return root;
    }

    // Один потомок
    if (!(root->left)) {
        BST* temp = root->right;
        delete root;
        return temp;
    }
    else if (!(root->right)) {
        BST* temp = root->left;
        delete root;
        return temp;
    }

    // Два потомка
    else {
        // Ищем узел для переноса
        BST* child;
        child = root->left;
        while (child->right) {
            child = child->right;
        }

        // Перенос крайнего узла на место удаляемого
        root->license = child->license;
        root->fileIndex = child->fileIndex;

        // Удаляем перенесенный узел
        root->left = deleteItem(root->left, child->license);
        return root;
    }
}

void BST::display(int level, BST* current) {
	// Параметры не указаны
	if (!current) {
        return;
    }
	// Расчет отступа
	std::string offset = "";
	for (int i = 0; i < level; i++) {
		offset += "\t\t";
	}
	// Отрисовка правой ветви
	if (current->right) {
		display(level + 1, current->right);
	}
	// Вывод значения узла
	std::cout << offset << "(" << current->license << ", " << current->fileIndex << ")" << std::endl;
	// Отрисовка левой ветви
	if (current->left) {
		display(level + 1, current->left);
	}
}

void BST::traverseNLR(BST* current) {
	if (current == nullptr) return;

	std::cout << current->license << " ";

	traverseNLR(current->left);
	traverseNLR(current->right);
}