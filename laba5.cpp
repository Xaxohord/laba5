#include <iostream>
#include <fstream>



struct Elem
{
    int data;       // Данные
    // Указатели на соседние вершины
    Elem* left;
    Elem* right;
    Elem* parent;
};
Elem* MAKE(int data, Elem* p)
{
    Elem* q = new Elem;         // Выделяем память под вершину
    q->data = data;
    q->left = nullptr;
    q->right = nullptr;
    q->parent = p;
    return q;
}

void ADD(int data, Elem*& root)
{
    if (root == nullptr) {
        root = MAKE(data, nullptr);
        return;
    }
    Elem* v = root;
    while ((data < v->data && v->left != nullptr) || (data > v->data && v->right != nullptr))
        if (data < v->data)
            v = v->left;
        else
            v = v->right;
    if (data == v->data)
        return;
    Elem* u = MAKE(data, v);
    if (data < v->data)
        v->left = u;
    else
        v->right = u;
}
Elem* SEARCH(int data, Elem* v) // v - элемент, от которого начинаем поиск
{
    if (v == nullptr)
        return v;
    if (v->data == data)
        return v;
    if (data < v->data)
        return SEARCH(data, v->left);
    else
        return SEARCH(data, v->right);
}
void DELETE(int data, Elem*& root)
{
    // Проверка на сущ. такого элемента
    Elem* u = SEARCH(data, root);
    if (u == nullptr)
        return;

    // Удаление корня (особый случай)
    if (u->left == nullptr && u->right == nullptr && u == root)
    {
        delete root;
        root = nullptr;
        return;
    }

    // Присутствует правый потомок
    if (u->left == nullptr && u->right != nullptr && u == root) // TODO убрать u==root
    {
        Elem* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }

    // Присутствует левый потомок
    if (u->left != nullptr && u->right == nullptr && u == root) // TODO убрать u==root
    {
        Elem* t = u->left;
        while (t->right != nullptr)
            t = t->right;
        u->data = t->data;
        u = t;
    }

    // Если оба потомка присутствуют
    if (u->left != nullptr && u->right != nullptr)
    {
        Elem* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }
    Elem* t;
    if (u->left == nullptr)
        t = u->right;
    else
        t = u->left;
    if (u->parent->left == u)
        u->parent->left = t;
    else
        u->parent->right = t;
    if (t != nullptr)
        t->parent = u->parent;
    delete u;
}
int SEARCHINT(int data, Elem* v, int dapth) // v - элемент, от которого начинаем поиск
{
    if (v == nullptr)
        return 0;
    if (v->data == data)
        return dapth;
    if (data < v->data)
        return SEARCHINT(data, v->left, dapth + 1);
    else
        return SEARCHINT(data, v->right, dapth + 1);
}
void PASS(Elem* v)
{
    if (v == nullptr)
        return;
    // Префиксный

    PASS(v->left);
    // Инфиксный
    std::cout << v->data << std::endl;

    PASS(v->right);

    // Постфиксный
}





int main() {
    std::ifstream in("1.txt");
    std::ofstream out("2.txt");
    Elem* root = nullptr;
    char c;
    int n, m;
    while (true) {
        in >> c;
        if (c == 'E')
            break;
        in >> n;
        if (c == '+') ADD(n, root);
        if (c == '-') DELETE(n, root);
        if (c == '?') {
            m = SEARCHINT(n, root, 1);
            if (m == 0) out << "n";
            else out << m;
        }

    }

}