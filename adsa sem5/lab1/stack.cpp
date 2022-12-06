#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

class Stack
{
    int top, capacity, *arr;

public:
    Stack(int);
    void push(int);
    int pop();
    int size();
};

Stack::Stack(int cap)
{
    capacity = cap;
    top = -1;
    arr = new int(sizeof(int) * cap);
}

void Stack::push(int val)
{
    if (top == capacity - 1)
    {
        cout << "Stack is full" << endl;
        return;
    }
    arr[++top] = val;
}

int Stack::pop()
{
    if (top == -1)
    {
        cout << "Stack is empty" << endl;
        return -1;
    }
    return arr[top--];
}

int Stack::size()
{
    return top + 1;
}

int main()
{

    Stack st(1e5);

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

    cout << "Using counter method : " << cnt << endl;

    cout.precision(5);
    cout << fixed << float(clock() - start) / CLOCKS_PER_SEC << " seconds" << endl;

    return 0;
}