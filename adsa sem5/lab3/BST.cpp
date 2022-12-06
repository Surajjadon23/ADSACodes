#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
    int val;
    Node *left, *right;
    Node(int);
};

Node::Node(int x)
{
    val = x;
    left = right = NULL;
}

class BST
{

public:
    Node *root;
    BST() { root = NULL; }
    Node *insert(Node *, int);
    void insert(int);
    Node *Delete(Node *, int);
    void Delete(int);
    Node *inSucc(Node *, Node *);
    Node *inSucc(Node *);
    Node *inPre(Node *, Node *);
    Node *inPre(Node *);
    void preOrder(Node *);
    void preOrder();
    void postOrder(Node *);
    void postOrder();
    void inOrder(Node *);
    void inOrder();
};

Node *BST::insert(Node *root, int x)
{
    if (!root)
    {
        return new Node(x);
    }
    if (root->val == x)
        return root;
    else if (root->val < x)
        root->right = insert(root->right, x);
    else
        root->left = insert(root->left, x);
    return root;
}

void BST::insert(int x)
{
    if (!root)
        root = insert(root, x);
    else
        insert(root, x);
}

Node *BST::Delete(Node *root, int x)
{
    if (root->val == x)
    {
        if (!root->right and !root->left)
        {
            delete (root);
            return NULL;
        }
        else if (!root->right or !root->left)
        {
            Node *temp = ((root->right) ? (root->right) : (root->left));
            delete root;
            return temp;
        }
        else
        {
            Node *temp = inSucc(root);
            root->val = temp->val;
            Delete(root->right, temp->val);
        }
    }
    else if (root->val > x)
    {
        root->left = Delete(root->left, x);
    }
    else
    {
        root->right = Delete(root->right, x);
    }
    return root;
}

void BST::Delete(int x)
{
    Delete(root, x);
}

Node *minValue(Node *root)
{
    while (root and root->left)
        root = root->left;
    return root;
}

Node *maxValue(Node *root)
{
    while (root and root->right)
        root = root->right;
    return root;
}

Node *BST::inSucc(Node *root, Node *ptr)
{
    if (ptr->right != NULL)
        return minValue(ptr->right);

    Node *succ = NULL;

    while (root != NULL)
    {
        if (ptr->val < root->val)
        {
            succ = root;
            root = root->left;
        }
        else if (ptr->val > root->val)
            root = root->right;
        else
            break;
    }

    return succ;
}

Node *BST::inSucc(Node *ptr)
{
    return inSucc(root, ptr);
}

Node *BST::inPre(Node *root, Node *ptr)
{
    if (ptr->left != NULL)
        return maxValue(ptr->left);

    Node *pre = NULL;

    while (root != NULL)
    {
        if (ptr->val > root->val)
        {
            pre = root;
            root = root->right;
        }
        else if (ptr->val < root->val)
            root = root->left;
        else
            break;
    }

    return pre;
}

Node *BST::inPre(Node *ptr)
{
    return inPre(root, ptr);
}

void BST::preOrder(Node *root)
{
    if (!root)
        return;
    cout << root->val << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void BST::preOrder()
{
    preOrder(root);
    cout << endl;
}

void BST::postOrder(Node *root)
{
    if (!root)
        return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->val << " ";
}

void BST::postOrder()
{
    postOrder(root);
    cout << endl;
}

void BST::inOrder(Node *root)
{
    if (!root)
        return;
    inOrder(root->left);
    cout << root->val << " ";
    inOrder(root->right);
}

void BST::inOrder()
{
    inOrder(root);
    cout << endl;
}

int main()
{

    BST tree;

    int n;
    cout << "Enter the number of values to be inserted in the tree : ";
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100001;
    }

    clock_t start = clock();

    for (int i = 0; i < n; i++)
    {
        tree.insert(arr[i]);
    }

    cout.precision(5);
    cout << fixed << float(clock() - start) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}