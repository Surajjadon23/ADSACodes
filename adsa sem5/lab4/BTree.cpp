#include <bits/stdc++.h>

using namespace std;

int maxChild(int m)
{
    return m;
}

int minChild(int m)
{
    return (m + 1) / 2;
}

int maxKeys(int m)
{
    return m - 1;
}

int minKeys(int m)
{
    return (m + 1) / 2 - 1;
}

map<int, vector<int>> mp;

class Node
{
public:
    int n, order;
    vector<int> keys;
    vector<Node *> child;
    bool leaf;
    Node(int, bool);
    void traverse(int);
    Node *search(int);
    void splitChild(int, Node *);
    void insertNotFull(int);

    int findKey(int k);
    void remove(int k);

    void removeFromLeaf(int idx);

    void removeFromNonLeaf(int idx);

    int getPred(int idx);

    int getSucc(int idx);

    void fill(int idx);

    void borrowFromPrev(int idx);

    void borrowFromNext(int idx);

    void merge(int idx);
};

Node::Node(int x, bool isLeaf)
{
    order = x;
    keys.resize(order - 1);
    child.resize(order, NULL);
    leaf = isLeaf;
    n = 0;
}

void Node::traverse(int x)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            child[i]->traverse(10 * x + i + 1);
        mp[x].push_back(keys[i]);
    }
    if (!leaf)
        child[i]->traverse(i + 1);
}

Node *Node::search(int k)
{
    int i = 0;
    while (i < n and k > keys[i])
        i++;
    if (keys[i] == k)
        return this;
    if (leaf)
        return NULL;
    return child[i]->search(k);
}

void Node::splitChild(int i, Node *node)
{

    Node *temp = new Node(node->order, node->leaf);
    temp->n = minKeys(order) - 1;

    for (int j = 0; j < minKeys(order) - 1; j++)
    {
        temp->keys[j] = node->keys[j + minKeys(order) + 1];
    }

    if (node->leaf == false)
    {
        for (int j = 0; j < minChild(order); j++)
        {
            temp->child[j] = node->child[j + minChild(order)];
        }
    }
    node->n = minKeys(order);
    for (int j = n; j >= i + 1; j--)
    {
        child[j + 1] = child[j];
    }
    child[i + 1] = temp;
    for (int j = n - 1; j >= i; j--)
    {
        keys[j + 1] = keys[j];
    }
    keys[i] = node->keys[minKeys(order)];
    n++;
}

void Node::insertNotFull(int k)
{
    int i = n - 1;
    if (leaf)
    {
        while (i >= 0 and keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n++;
    }
    else
    {
        while (i >= 0 and keys[i] > k)
        {
            i--;
        }

        if (child[i + 1]->n == maxKeys(order))
        {
            splitChild(i + 1, child[i + 1]);
            if (keys[i + 1] < k)
                i++;
        }
        child[i + 1]->insertNotFull(k);
    }
}

int Node::findKey(int k)
{
    int idx = 0;
    while (idx < n && keys[idx] < k)
        ++idx;
    return idx;
}

void Node::remove(int k)
{
    int idx = findKey(k);

    if (idx < n && keys[idx] == k)
    {

        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {

        if (leaf)
        {
            cout << "The key " << k << " is does not exist in the tree\n";
            return;
        }

        bool flag = ((idx == n) ? true : false);

        if (child[idx]->n < minChild(order))
            fill(idx);

        if (flag && idx > n)
            child[idx - 1]->remove(k);
        else
            child[idx]->remove(k);
    }
    return;
}

void Node::removeFromLeaf(int idx)
{

    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    n--;

    return;
}

void Node::removeFromNonLeaf(int idx)
{

    int k = keys[idx];

    if (child[idx]->n >= minKeys(order) + 1)
    {
        int pred = getPred(idx);
        keys[idx] = pred;
        child[idx]->remove(pred);
    }

    else if (child[idx + 1]->n >= minKeys(order) + 1)
    {
        int succ = getSucc(idx);
        keys[idx] = succ;
        child[idx + 1]->remove(succ);
    }

    else
    {
        merge(idx);
        child[idx]->remove(k);
    }
    return;
}

int Node::getPred(int idx)
{

    Node *cur = child[idx];
    while (!cur->leaf)
        cur = cur->child[cur->n];

    return cur->keys[cur->n - 1];
}

int Node::getSucc(int idx)
{

    Node *cur = child[idx + 1];
    while (!cur->leaf)
        cur = cur->child[0];

    return cur->keys[0];
}

void Node::fill(int idx)
{

    if (idx != 0 && child[idx - 1]->n >= minKeys(order) + 1)
        borrowFromPrev(idx);

    else if (idx != n && child[idx + 1]->n >= minKeys(order) + 1)
        borrowFromNext(idx);

    else
    {
        if (idx != n)
            merge(idx);
        else
            merge(idx - 1);
    }
    return;
}

void Node::borrowFromPrev(int idx)
{

    Node *chld = child[idx];
    Node *sibling = child[idx - 1];

    for (int i = chld->n - 1; i >= 0; --i)
        chld->keys[i + 1] = chld->keys[i];

    if (!chld->leaf)
    {
        for (int i = chld->n; i >= 0; --i)
            chld->child[i + 1] = chld->child[i];
    }

    chld->keys[0] = keys[idx - 1];

    if (!chld->leaf)
        chld->child[0] = sibling->child[sibling->n];

    keys[idx - 1] = sibling->keys[sibling->n - 1];

    chld->n += 1;
    sibling->n -= 1;

    return;
}

void Node::borrowFromNext(int idx)
{

    Node *chld = child[idx];
    Node *sibling = child[idx + 1];

    chld->keys[(chld->n)] = keys[idx];

    if (!(chld->leaf))
        chld->child[(chld->n) + 1] = sibling->child[0];

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf)
    {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->child[i - 1] = sibling->child[i];
    }

    chld->n += 1;
    sibling->n -= 1;

    return;
}

void Node::merge(int idx)
{
    Node *chld = child[idx];
    Node *sibling = child[idx + 1];

    chld->keys[minKeys(order)] = keys[idx];

    for (int i = 0; i < sibling->n; ++i)
        chld->keys[i + minKeys(order) + 1] = sibling->keys[i];

    if (!chld->leaf)
    {
        for (int i = 0; i <= sibling->n; ++i)
            chld->child[i + minKeys(order) + 1] = sibling->child[i];
    }

    for (int i = idx + 1; i < n; ++i)
        keys[i - 1] = keys[i];

    for (int i = idx + 2; i <= n; ++i)
        child[i - 1] = child[i];

    chld->n += sibling->n + 1;
    n--;

    delete (sibling);
    return;
}

class BTree
{
public:
    Node *root;
    int order;
    BTree(int);
    void traverse()
    {
        mp.clear();
        root->traverse(0);
        for (auto &[x, y] : mp)
        {
            cout << x << " : ";
            for (auto i : y)
                cout << i << " ";
            cout << endl;
        }
        cout << endl;
    }
    Node *search(int k) { return root->search(k); }
    void insert(int);
    void remove(int);
};

BTree::BTree(int order)
{
    this->order = order;
    root = NULL;
}

void BTree::insert(int k)
{
    if (!root)
    {
        root = new Node(order, 1);
        root->keys[0] = k;
        root->n = 1;
        return;
    }

    if (root->n == maxKeys(order))
    {
        Node *node = new Node(order, 0);
        node->child[0] = root;
        node->splitChild(0, root);

        int i = 0;
        if (node->keys[0] < k)
            i++;
        node->child[i]->insertNotFull(k);

        root = node;
    }
    else
    {
        root->insertNotFull(k);
    }
}

void BTree::remove(int k)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }

    root->remove(k);

    if (root->n == 0)
    {
        Node *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->child[0];

        delete tmp;
    }
    return;
}

int main()
{
    BTree t(5);

    t.insert(5);
    t.insert(10);
    t.insert(12);
    t.insert(20);
    t.insert(6);

    t.traverse();

    // t.insert(10);

    // t.insert(20);

    // t.insert(5);

    // t.insert(6);

    // t.insert(12);

    // t.insert(30);

    // t.insert(7);

    // t.insert(17);

    // t.insert(8);

    // t.insert(9);

    // t.insert(3);

    // t.insert(29);

    // t.insert(16);
    // t.insert(18);
    // t.insert(19);
    // t.insert(1);
    // t.insert(2);

    // t.traverse();

    // t.remove(7);

    // t.traverse();
    // t.remove(10);

    // t.traverse();
    // t.remove(20);

    // t.traverse();

    return 0;
}