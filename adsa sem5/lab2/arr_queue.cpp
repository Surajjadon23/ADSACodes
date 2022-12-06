#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

class Queue
{
    int front, rear, capacity, *arr;

public:
    Queue(int);
    void enqueue(int);
    int dequeue();
    int size();
    int getFront();
};

Queue::Queue(int cap)
{
    capacity = cap;
    front = rear = -1;
    arr = new int(sizeof(int) * cap);
}

void Queue::enqueue(int val)
{
    if (rear == capacity - 1)
    {
        cout << "Queue is full" << endl;
        return;
    }
    arr[++rear] = val;
    if (!rear)
        front = rear = 0;
}

int Queue::dequeue()
{
    if (rear == -1)
    {
        cout << "Queue is empty" << endl;
        return -1;
    }
    int val = arr[front++];
    if (front > rear)
        front = rear = -1;
    return val;
}

int Queue::size()
{
    if (rear == -1)
        return 0;
    return rear - front + 1;
}

int Queue::getFront()
{
    if (rear == -1)
        return -1;
    return arr[front];
}

int main()
{

    Queue q(1e5);

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