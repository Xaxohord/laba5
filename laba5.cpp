#include <iostream>
#include <fstream>
#include <cstring> 
#include <string> 

struct Elem
{
    int data;   
    Elem* left;
    Elem* right;
    Elem* parent;
};

Elem* MAKE(int data, Elem* p)
{
    Elem* q = new Elem;       
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

void PASS(Elem* v)
{
    if (v == nullptr)
        return;
 
    PASS(v->left);
    std::cout << v->data << std::endl;

    PASS(v->right);
}

Elem* DEEP(int data, Elem* v, int& k)  
{
    k += 1;
    if (v == nullptr)
        return v;
    if (v->data == data)
        return v;
    if (data < v->data)
    {
        return DEEP(data, v->left, k);
    }
    else
    {
        return DEEP(data, v->right, k);
    }
}

Elem* SEARCH(int data, Elem* v)   
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
    Elem* u = SEARCH(data, root);
    if (u == nullptr)
        return;

    if (u->left == nullptr && u->right == nullptr && u == root)
    {
        delete root;
        root = nullptr;
        return;
    }

    if (u->left == nullptr && u->right != nullptr && u == root) 
    {
        Elem* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }

    if (u->left != nullptr && u->right == nullptr && u == root) 
    {
        Elem* t = u->left;
        while (t->right != nullptr)
            t = t->right;
        u->data = t->data;
        u = t;
    }
  
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



void CLEAR(Elem*& v)
{
    if (v == nullptr)
        return;
    CLEAR(v->left);

    CLEAR(v->right);

    delete v;
    v = nullptr;
}


int main()
{
    Elem* root = nullptr; 

    std::ifstream file("1.txt");
    std::ofstream fin("2.txt");
    std::string line;
    while (file>>line)
    {
        if (line[0] == 'E')
            break;
        if (line[0] == '+')
            ADD(std::stoi(line), root);
        if (line[0] == '-')
            DELETE(std::stoi(line.substr(1, line.length() - 1)), root);
        if (line[0] == '?')
        {
            int k = 0;
            if ((SEARCH(std::stoi(line.substr(1, line.length() - 1)), root) == nullptr))
                fin << "n";
            else
            {
                DEEP(std::stoi(line.substr(1, line.length() - 1)), root, k);
                fin << k;
            }
        }
    }

    PASS(root);

    CLEAR(root);

    return 0;
}