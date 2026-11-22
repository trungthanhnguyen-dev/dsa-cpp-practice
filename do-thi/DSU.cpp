#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<int> sz;
    int num_components; // Quản lý số lượng thành phần liên thông hiện tại

    // Khởi tạo DSU với n phần tử (đánh số từ 1 đến n)
    DSU(int n) {
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        num_components = n;
        for (int i = 1; i <= n; ++i) {
            parent[i] = i; // Ban đầu mỗi đỉnh tự là gốc của chính nó
        }
    }

    // Tìm gốc đại diện có nén đường đi (Path Compression)
    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }

    // Hợp nhất hai tập hợp theo kích thước (Union by Size)
    bool union_sets(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);

        // Đã thuộc cùng một tập hợp từ trước, không cần gộp
        if (root_u == root_v) return false;

        // Đảm bảo root_u luôn là gốc của cây có kích thước lớn hơn
        if (sz[root_u] < sz[root_v]) {
            swap(root_u, root_v);
        }

        // Gộp cây nhỏ (root_v) vào cây lớn (root_u)
        parent[root_v] = root_u;
        sz[root_u] += sz[root_v];
        num_components--; // Giảm số lượng thành phần liên thông đi 1

        return true; // Gộp thành công
    }

    // Kiểm tra tính liên thông giữa hai đỉnh
    bool same_set(int u, int v) {
        return find(u) == find(v);
    }

    // Lấy kích thước tập hợp chứa phần tử u
    int get_size(int u) {
        return sz[find(u)];
    }
};