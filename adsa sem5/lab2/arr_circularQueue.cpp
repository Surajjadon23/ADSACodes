#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

class CQueue
{
    int front, rear, size, *arr;

public:
    CQueue(int);
    void enqueue(int);
    int dequeue();
    bool isEmpty();
    bool isFull();
};

CQueue::CQueue(int cap)
{
    size = cap;
    front = rear = -1;
    arr = new int(sizeof(int) * cap);
}

void CQueue::enqueue(int val)
{
    if (isFull())
    {
        cout << "Circular Queue is full" << endl;
        return;
    }
    rear = (rear + 1) % size;
    arr[rear] = val;
    if (front == -1)
        front = rear = 0;
}

int CQueue::dequeue()
{
    if (isEmpty())
    {
        cout << "Circular Queue is empty" << endl;
        return -1;
    }
    int val = arr[front];
    front = (front + 1) % size;
    if (front == (rear + 1) % size)
        front = rear = -1;
    return val;
}

bool CQueue::isEmpty()
{
    return front == -1;
}

bool CQueue::isFull()
{
    return ((rear + 1) % size == front);
}

int main()
{

    CQueue q(5);

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
        cnt += 4;
    }
    cnt += 2;

    cout << "Using counter method : " << cnt << endl;

    cout.precision(5);
    cout << fixed << float(clock() - start) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}