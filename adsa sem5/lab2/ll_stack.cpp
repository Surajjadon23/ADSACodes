#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

class Node
{
public:
    int val;
    Node *next;
    Node(int x)
    {
        val = x;
        next = NULL;
    }
};

class Stack
{
    Node *top;

public:
    Stack();
    void push(int);
    int pop();
    bool isEmpty();
};

Stack::Stack()
{
    top = NULL;
}

void Stack::push(int val)
{
    Node *newNode = new Node(val);
    newNode->next = top;
    top = newNode;
}

int Stack::pop()
{
    if (isEmpty())
    {
        cout << "Stack is empty.";
        return -1;
    }
    int val = top->val;
    Node *temp = top;
    top = top->next;
    delete temp;
    return val;
}

bool Stack::isEmpty()
{
    return top == NULL;
}

int main()
{
    Stack st;

    int n;
    cout << "Enter number of elements to be entered : ";
    cin >> n;

    int cnt = 0;

    int arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }

    clock_t start = clock();

    for (int i = 0; i < n; i++)
    {
        cnt += 3;
        st.push(arr[i]);
        cnt += 3;
    }
    cnt += 2;

    for (int i = 0; i < n; i++)
    {
        cnt += 3;
        st.pop();
        cnt += 6;
    }
    cnt += 2;

    cout << "Using counter method : " << cnt << endl;

    cout.precision(5);
    cout << fixed << float(clock() - start) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}