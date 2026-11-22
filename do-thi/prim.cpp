#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

void prim(int n, const vector<vector<pii>>& adj, int startNode = 1) {
    vector<int> key(n + 1, INT_MAX);
    vector<int> parent(n + 1, -1);
    vector<bool> visited(n + 1, false);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    key[startNode] = 0;
    pq.push({0, startNode});

    long long totalWeight = 0;
    int edgesCount = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;
        totalWeight += key[u];
        if (parent[u] != -1) edgesCount++;

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!visited[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    if (edgesCount != n - 1) {
        cout << "Do thi khong lien thong\n";
        return;
    }

    cout << "Tong trong so: " << totalWeight << "\n";
    cout << "Cac canh thuoc MST:\n";
    for (int i = 1; i <= n; ++i) {
        if (parent[i] != -1) {
            cout << parent[i] << " - " << i << " (" << key[i] << ")\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<pii>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    prim(n, adj, 1);

    return 0;
}