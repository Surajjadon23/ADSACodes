#include <bits/stdc++.h>

using namespace std;

void removeIncident(vector<pair<int, int>> &edges, pair<int, int> selEdge)
{
    int u1 = selEdge.first, v1 = selEdge.second;
    int i = 0;
    while (i < edges.size())
    {
        int u2 = edges[i].first, v2 = edges[i].second;
        if (u1 == u2 or u1 == v2 or v1 == u2 or v1 == v2)
        {
            edges.erase(edges.begin() + i);
        }
        else
        {
            i++;
        }
    }
}

void findVertexCover(vector<pair<int, int>> &edges, int n, vector<int> &vertexCover)
{
    vector<int> vis(n, false);
    while (edges.size() != 0)
    {
        int random = rand() % edges.size();
        pair<int, int> selEdge = edges[random];

        vis[selEdge.first] = vis[selEdge.second] = true;

        vertexCover.push_back(selEdge.first);
        vertexCover.push_back(selEdge.second);
        removeIncident(edges, selEdge);
        cout << "Selected edge : " << selEdge.first << " " << selEdge.second << endl;
        cout << edges.size() << endl;
    }
}

int main()
{
    srand(time(0));
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        edges.push_back({u, v});
    }

    vector<int> vertexCover;
    findVertexCover(edges, n, vertexCover);
    cout << "Vertex Cover : ";
    for (auto i : vertexCover)
        cout << i << " ";
}

/*

7 6
0 1
0 2
1 3
3 4
4 5
5 6

*/