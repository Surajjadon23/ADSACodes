#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int val;
    Node *left, *right;
    int height;
    Node(int);
};

Node::Node(int x)
{
    val = x;
    height = 1;
    left = right = NULL;
}

class AVLTree
{
    Node *root;

public:
    AVLTree() { root = NULL; }
    Node *insert(Node *, int);
    Node *insert(int);
    Node *Delete(Node *, int);
    void Delete(int);
    Node *inSucc(Node *, Node *);
    Node *inSucc(Node *);
    void inorder(Node *);
    void inorder();
    void preorder(Node *);
    void preorder();
    int NodeHeight(Node *);
    int balanceFactor(Node *);
    Node *LL_Rotation(Node *);
    Node *LR_Rotation(Node *);
    Node *RL_Rotation(Node *);
    Node *RR_Rotation(Node *);
};

Node *AVLTree::insert(Node *root, int val)
{

    if (!root)
    {
        Node *newNode = new Node(val);
        return newNode;
    }

    if (val == root->val)
        return root;
    else if (val > root->val)
        root->right = insert(root->right, val);
    else
        root->left = insert(root->left, val);

    root->height = NodeHeight(root);

    if (balanceFactor(root) == 2)
    {
        if (balanceFactor(root->left) == 1)
            return LL_Rotation(root);
        else if (balanceFactor(root->left) == -1)
            return LR_Rotation(root);
    }
    else if (balanceFactor(root) == -2)
    {
        if (balanceFactor(root->right) == -1)
            return RR_Rotation(root);
        else if (balanceFactor(root->right) == 1)
            return RL_Rotation(root);
    }

    return root;
}

Node *AVLTree::insert(int val)
{

    if (!root)
    {
        root = insert(root, val);
        return root;
    }

    return insert(root, val);
}

Node *AVLTree::Delete(Node *root, int x)
{
    Node *temp = NULL;
    if (root->val == x)
    {
        if (!root->right and !root->left)
        {
            delete (root);
            return NULL;
        }
        else if (!root->right or !root->left)
        {
            temp = ((root->right) ? (root->right) : (root->left));
            *root = *temp;
            delete temp;
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

    root->height = NodeHeight(root);

    if (balanceFactor(root) > 1)
    {
        if (balanceFactor(root->left) >= 0)
            return LL_Rotation(root);
        else if (balanceFactor(root->left) < 0)
            return LR_Rotation(root);
    }
    else if (balanceFactor(root) < -1)
    {
        if (balanceFactor(root->right) <= 0)
            return RR_Rotation(root);
        else if (balanceFactor(root->right) > 0)
            return RL_Rotation(root);
    }

    return root;
}

void AVLTree::Delete(int x)
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

Node *AVLTree::inSucc(Node *root, Node *ptr)
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

Node *AVLTree::inSucc(Node *ptr)
{
    return inSucc(root, ptr);
}

void AVLTree::inorder(Node *root)
{
    if (!root)
        return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

void AVLTree::inorder()
{
    inorder(root);
    cout << endl;
}

void AVLTree::preorder(Node *root)
{
    if (!root)
        return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

void AVLTree::preorder()
{
    preorder(root);
    cout << endl;
}

int AVLTree::NodeHeight(Node *root)
{
    if (!root)
        return 0;

    return max(NodeHeight(root->left), NodeHeight(root->right)) + 1;
}

int AVLTree::balanceFactor(Node *root)
{
    if (!root)
        return 0;

    int left = root->left ? NodeHeight(root->left) : 0;
    int right = root->right ? NodeHeight(root->right) : 0;

    return left - right;
}

Node *AVLTree::LL_Rotation(Node *p)
{

    Node *l = p->left, *lr = l->right;

    p->left = lr;
    l->right = p;

    if (p == root)
        root = l;

    return l;
}

Node *AVLTree::RR_Rotation(Node *p)
{

    Node *r = p->right, *rl = r->left;

    p->right = rl;
    r->left = p;

    if (p == root)
        root = r;

    return r;
}

Node *AVLTree::LR_Rotation(Node *p)
{

    Node *l = p->left, *lr = l->right;

    l->right = lr->left;
    p->left = lr->right;

    lr->left = l;
    lr->right = p;

    p->height = NodeHeight(p);
    l->height = NodeHeight(l);
    lr->height = NodeHeight(lr);

    if (p == root)
        root = lr;

    return lr;
}

Node *AVLTree::RL_Rotation(Node *p)
{

    Node *r = p->right, *rl = r->left;

    r->left = rl->right;
    p->right = rl->left;

    rl->left = p;
    rl->right = r;

    p->height = NodeHeight(p);
    r->height = NodeHeight(r);
    rl->height = NodeHeight(rl);

    if (p == root)
        root = rl;

    return rl;
}

int main()
{

    AVLTree tree;

    // int n;
    // cout << "Enter the number of values to be inserted in the tree : ";
    // cin >> n;

    // int arr[n];
    // for (int i = 0; i < n; i++)
    // {
    //     arr[i] = rand() % 100001;
    // }

    // clock_t start = clock();

    // for (int i = 0; i < n; i++)
    // {
    //     tree.insert(arr[i]);
    // }

    // cout.precision(5);
    // cout << fixed << float(clock() - start) / CLOCKS_PER_SEC << " seconds" << endl;

    tree.insert(10);

    tree.insert(15);

    tree.insert(13);

    tree.insert(7);

    tree.insert(8);

    tree.insert(6);

    tree.insert(3);

    tree.inorder();

    tree.preorder();

    tree.Delete(8);
    tree.preorder();
    tree.Delete(10);
    tree.preorder();

    return 0;
}