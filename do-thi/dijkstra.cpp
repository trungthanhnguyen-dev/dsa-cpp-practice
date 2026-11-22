#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Hằng số vô cùng lớn an toàn cho kiểu 64-bit (10^18)
const long long INF = 1e18;

// Cấu trúc một cạnh có hướng trong danh sách kề
struct Edge {
    int to;
    long long w;
};

// Cấu trúc trạng thái trong hàng đợi ưu tiên: {khoảng cách, đỉnh}
struct State {
    long long dist;
    int u;

    // Toán tử so sánh dùng cho Min-Heap (phần tử dist nhỏ hơn có độ ưu tiên cao hơn)
    bool operator>(const State& other) const {
        return dist > other.dist;
    }
};

const int MAXN = 300005; // Khai báo an toàn cho quy mô 3 * 10^5 đỉnh

int n, m;
vector<Edge> adj[MAXN];
long long dist[MAXN];
int trace[MAXN];

void dijkstra(int s) {
    // Bước 1: Thiết lập giá trị ban đầu
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
        trace[i] = -1;
    }

    // Min-Heap lưu trữ các trạng thái
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[s] = 0;
    pq.push({0, s});

    // Bước 2: Vòng lặp trích xuất và nới lỏng
    while (!pq.empty()) {
        State top = pq.top();
        pq.pop();

        long long d = top.dist;
        int u = top.u;

        // Bỏ qua vé rác (Stale state check)
        if (d > dist[u]) continue;

        // Thả lỏng tất cả các cung đi ra từ u
        for (int i = 0; i < (int)adj[u].size(); ++i) {
            int v = adj[u][i].to;
            long long weight = adj[u][i].w;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                trace[v] = u; // Lưu đỉnh cha phục vụ truy vết
                pq.push({dist[v], v});
            }
        }
    }
}

// Hàm truy vết và in toàn bộ đường đi từ s đến t
void print_path(int s, int t) {
    if (dist[t] == INF) {
        cout << -1 << "\n";
        return;
    }

    vector<int> path;
    for (int curr = t; curr != -1; curr = trace[curr]) {
        path.push_back(curr);
    }

    // Đường đi bị ngược (t -> s) nên cần đảo lại
    for (int i = (int)path.size() - 1; i >= 0; --i) {
        cout << path[i] << (i == 0 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    // Tối ưu tốc độ nhập xuất
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int s, t;
    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w}); // Đồ thị có hướng: u -> v
        // Nếu đề bài là đồ thị vô hướng: thêm adj[v].push_back({u, w});
    }

    cin >> s >> t;

    dijkstra(s);

    // In chi phí ngắn nhất từ s đến t
    if (dist[t] == INF) {
        cout << -1 << "\n";
    } else {
        cout << dist[t] << "\n";
    }

    return 0;
}