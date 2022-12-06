#include <bits/stdc++.h>

using namespace std;

const int N = 256;

class Node
{
    Node *child[N];
    bool isEnd;

public:
    Node();
    Node *get(char ch);
    void set(Node *, char);
    void setEnd()
    {
        isEnd = true;
    }
    bool getEnd()
    {
        return isEnd;
    }
};

Node::Node()
{
    for (int i = 0; i < N; i++)
        child[i] = NULL;
    isEnd = false;
}

Node *Node::get(char ch)
{
    return child[ch - '\0'];
}

void Node::set(Node *node, char ch)
{
    child[ch - '\0'] = node;
}

class Trie
{
    Node *root;

public:
    Trie() { root = new Node(); }
    void insert(string);
    bool search(string);
};

void Trie::insert(string word)
{

    Node *temp = root;
    for (auto i : word)
    {
        if (!temp->get(i))
            temp->set(new Node(), i);
        temp = temp->get(i);
    }
    temp->setEnd();
}

bool Trie::search(string word)
{

    Node *temp = root;
    for (auto i : word)
    {
        if (!temp->get(i))
            return false;
        temp = temp->get(i);
    }
    return temp->getEnd();
}

int main()
{
    Trie trie;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        trie.insert(str);
    }

    string searchWord;
    cin >> searchWord;
    if (trie.search(searchWord))
        cout << "Word is present.";
    else
        cout << "Word is not present.";

    return 0;
}