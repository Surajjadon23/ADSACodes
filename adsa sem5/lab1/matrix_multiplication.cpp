#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

int main()
{
    int m1, n1, m2, n2;
    cout << "Enter the dimensions of first matrix : ";
    cin >> m1 >> n1;

    cout << "Enter the dimensions of second matrix : ";
    cin >> m2 >> n2;

    if (n1 != m2)
    {
        cout << "Dimensions incompatible" << endl;
        exit(0);
    }

    int A[m1][n1], B[m2][n2], C[m1][n2];

    for (int i = 0; i < m1; i++)
    {
        for (int j = 0; j < n1; j++)
        {
            A[i][j] = rand() % 1000;
        }
    }

    for (int i = 0; i < m2; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            B[i][j] = rand() % 1000;
        }
    }

    clock_t start = clock();

    int cnt = 0;

    for (int i = 0; i < m1; i++)
    {
        cnt += 3;
        for (int j = 0; j < n2; j++)
        {
            cnt += 3;
            C[i][j] = 0;
            cnt += 4;
            for (int k = 0; k < n1; k++)
            {
                cnt += 3;
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
                cnt += 18;
            }
            cnt += 2;
        }
        cnt += 2;
    }
    cnt += 2;

    cout << "Using counter method : " << cnt << endl;

    cout.precision(10);
    cout << "Execution time : " << fixed << double(clock() - start) / CLOCKS_PER_SEC << " seconds" << endl;
    return 0;
}