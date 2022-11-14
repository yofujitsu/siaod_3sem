#include "avltree.h"
using namespace std;

int AVLTree::rotations = 0;

int AVLTree::getValue() {
    return this->root->license;
}

int AVLTree::getIndex() {
    return this->root->fileIndex;
}

int AVLTree::getBalance(AVLTree* next)
{
    if (!next)
        return 0;
    else if (next->root->left && next->root->right)
        return (next->root->left)->height - (next->root->right)->height;
    else if (next->root->left)
        return next->root->left->height;
    else if (next->root->right)
        return 0 - (next->root->right->height);
    return 0;
}

AVLTree* AVLTree::rightRotate(AVLTree* y)
{
    AVLTree* x = (y->root)->left;
    AVLTree* T2 = (x->root)->right;

    // Выполнение поворота 
    (x->root)->right = y;
    (y->root)->left = T2;

    // Обновление высот 
    y->height = 1 + max( ((y->root)->left) ? ((y->root)->left)->height : 0,
                            ((y->root)->right) ? ((y->root)->right)->height : 0);
    x->height = 1 + max( ((x->root)->left) ? ((x->root)->left)->height : 0,
                            ((x->root)->right) ? ((x->root)->right)->height : 0);

    rotations += 1;

    // Возврат нового корня 
    return x;
}

AVLTree* AVLTree::leftRotate(AVLTree* x)
{
    AVLTree* y = (x->root)->right;
    AVLTree* T2 = (y->root)->left;

    // Выполнение поворота 
    (y->root)->left = x;
    (x->root)->right = T2;

    // Обновление высот 
    x->height = 1 + max(((x->root)->left) ? ((x->root)->left)->height : 0,
                        ((x->root)->right) ? ((x->root)->right)->height : 0);
    y->height = 1 + max(((y->root)->left) ? ((y->root)->left)->height : 0,
                        ((y->root)->right) ? ((y->root)->right)->height : 0);

    rotations += 1;

    // Возврат нового корня 
    return y;
}

AVLTree* AVLTree::addNode(int license, int fileIndex, AVLTree* next) {
    // Добавление узла в бинарное дерево
    if (!next) {
        AVLTree* node = new AVLTree();
        node->root = new Node(license, fileIndex);
        return node;
    }
    if (license < next->getValue())
        (next->root)->left = addNode(license, fileIndex, (next->root)->left);
    else if (license > next->getValue())
        (next->root)->right = addNode(license, fileIndex, (next->root)->right);

    // Обновление высоты дерева
    next->height = 1 + max( ((next->root)->left) ? ((next->root)->left)->height : 0, 
                            ((next->root)->right) ? ((next->root)->right)->height : 0);

    int balance = getBalance(next);

    // Левый 
    if (balance > 1 && license < ((next->root)->left)->getValue()) {
        return rightRotate(next);
    }
    // Правый 
    if (balance < -1 && license > ((next->root)->right)->getValue()) {
        return leftRotate(next);
    }
    // Левый правый 
    if (balance > 1 && license > ((next->root)->left)->getValue())
    {
        (next->root)->left = leftRotate((next->root)->left);
        return rightRotate(next);
    }
    // Правый левый 
    if (balance < -1 && license < ((next->root)->right)->getValue())
    {
        (next->root)->right = rightRotate((next->root)->right);
        return leftRotate(next);
    }

    return next;
}

AVLTree* AVLTree::findNode(int key, AVLTree* next)
{
    // Элемента нет в дереве
    if (!next)
        return next;

    // Поиск элемента в дереве
    if (next->getValue() > key) {
        return findNode(key, (next->root)->left);
    }
    else if (next->getValue() < key) {
        return findNode(key, (next->root)->right);
    }

    return next;
}
    
AVLTree* AVLTree::deleteNode(int key, AVLTree* next)
{
    // Узел не существует
    if (!next)
        return nullptr;

    // Поиск узла в дереве
    if (key < next->getValue())
        (next->root)->left = deleteNode(key, (next->root)->left);
    else if (key > next->getValue())
        (next->root)->right = deleteNode(key, (next->root)->right);
    // Текущий узел является искомым
    else
    {
        // У узла не более одного потомка
        if (!((next->root)->left) || !((next->root)->right))
        {
            // Выбираем существующего потомка
            AVLTree* temp = (next->root)->left ? (next->root)->left : (next->root)->right;

            // Потомок существует
            if (temp)
                return temp;

            return nullptr;
        }

        // У узла 2 потомка
        else
        {
            // Ищем узел для переноса
            AVLTree* child;
            if (getBalance(next) >= 0) {
                child = (next->root)->left;
                while ((child->root)->right) {
                    child = (child->root)->right;
                }
            }
            else {
                child = (next->root)->right;
                while ((child->root)->left) {
                    child = (child->root)->left;
                }
            }
            // Перенос крайнего узла на место удаляемого
            (next->root)->license = (child->root)->license;
            (next->root)->fileIndex = (child->root)->fileIndex;

            // Удаляем перенесенный узел
            if (getBalance(next) >= 0) {
                (next->root)->left = deleteNode(child->getValue(), (next->root)->left);
            }
            else {
                (next->root)->right = deleteNode(child->getValue(), (next->root)->right);
            }
            return next;
        }
    }
    // Обновление высоты дерева
    next->height = 1 + max(((next->root)->left) ? ((next->root)->left)->height : 0,
                            ((next->root)->right) ? ((next->root)->right)->height : 0);
    int balance = getBalance(next);
    // Левый 
    if (balance > 1 && getBalance((next->root)->left) >= 0) {
        return rightRotate(next);
    }
    // Правый 
    if (balance < -1 && getBalance((next->root)->right) <= 0) {
        return leftRotate(next);
    }
    // Левый правый 
    if (balance > 1 && getBalance((next->root)->left) < 0)
    {
        (next->root)->left = leftRotate((next->root)->left);
        return rightRotate(next);
    }
    // Правый левый 
    if (balance < -1 && getBalance((next->root)->right) > 0)
    {
        (next->root)->right = rightRotate((next->root)->right);
        return leftRotate(next);
    }

    return next;
}

void AVLTree::display(int level, AVLTree* current) {
    // Параметры не указаны
    if (!current) {
        return;
    }
    // Расчет отступа
    std::string offset = "";
    for (int i = 0; i < level; i++) {
        offset += "\t\t  ";
    }
    // Отрисовка правой ветви
    if ((current->root)->right) {
        display(level + 1, (current->root)->right);
    }
    // Вывод значения узла
    std::cout << offset << "(" << (current->root)->license << ", " << (current->root)->fileIndex << ")" << std::endl;
    // Отрисовка левой ветви
    if ((current->root)->left) {
        display(level + 1, (current->root)->left);
    }
}