#include <bits/stdc++.h>

using namespace std;

class Node
{
public:
    int val;
    Node *next;
    Node(int);
};

Node::Node(int x)
{
    val = x;
    next = NULL;
}

class Queue
{
    Node *front, *rear;

public:
    Queue();
    void enqueue(int);
    int dequeue();
    bool isEmpty();
};

Queue::Queue()
{
    front = rear = NULL;
}

void Queue::enqueue(int x)
{
    Node *newNode = new Node(x);
    if (isEmpty())
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = rear->next;
    }
}

int Queue::dequeue()
{
    if (isEmpty())
    {
        cout << "Queue is empty." << endl;
        return -1;
    }
    int x = front->val;
    Node *temp = front;
    front = front->next;
    delete temp;
    return x;
}

bool Queue::isEmpty()
{
    return front == NULL;
}

int main()
{

    Queue q;

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
        q.enqueue(arr[i]);
        cnt += 4;
    }
    cnt += 2;

    for (int i = 0; i < n; i++)
    {
        cnt += 3;
        q.dequeue();
        cnt += 6;
    }
    cnt += 2;

    cout << "Using counter method : " << cnt << endl;

    cout.precision(5);
    cout << fixed << float(clock() - start) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}