#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Cấu trúc 1 cạnh
struct Edge {
    int u, v;
    long long w;
};

// Hàm so sánh dùng cho hàm sort: Trả về true nếu cạnh a rẻ hơn cạnh b
bool cmp(Edge a, Edge b) {
    return a.w < b.w;
}

// Cấu trúc DSU tối ưu chuẩn
struct DSU {
    vector<int> parent;
    vector<int> sz;

    DSU(int n) {
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]); // Nén đường đi
    }

    bool union_sets(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);

        if (root_u == root_v) {
            return false; // Cùng nhóm -> tạo chu trình
        }

        // Nhỏ cắm vào lớn
        if (sz[root_u] < sz[root_v]) swap(root_u, root_v);
        parent[root_v] = root_u;
        sz[root_u] += sz[root_v];

        return true;
    }
};

const int MAXM = 1000005; // Dự phòng tối đa 10^6 cạnh
Edge edges[MAXM];

int main() {
    // Tối ưu hóa đọc ghi dữ liệu
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    // Bước 1: Sắp xếp các cạnh tăng dần theo trọng số bằng hàm cmp
    sort(edges, edges + m, cmp);

    // Bước 2: Khởi tạo DSU và duyệt cạnh
    DSU dsu(n);
    long long total_weight = 0;
    int edges_picked = 0;

    for (int i = 0; i < m; ++i) {
        // Nếu gộp thành công (không tạo chu trình)
        if (dsu.union_sets(edges[i].u, edges[i].v)) {
            total_weight += edges[i].w;
            edges_picked++;

            // Dừng sớm ngay khi đã gom đủ N - 1 cạnh
            if (edges_picked == n - 1) break;
        }
    }

    // Bước 3: Đánh giá kết quả liên thông
    if (edges_picked < n - 1) {
        cout << -1 << "\n"; // Đồ thị không liên thông, không có MST
    } else {
        cout << total_weight << "\n";
    }

    return 0;
}