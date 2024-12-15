#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

struct dsu {
    vector<int> par, sz;

    void init(int n) {
        par.resize(n + 1);
        sz.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            par[i] = i;
            sz[i] = 1;
        }
    }

    int find_par(int u) {
        if (par[u] == u)
            return u;
        return par[u] = find_par(par[u]);
    }

    void connect(int u, int v) {
        u = find_par(u);
        v = find_par(v);
        if (u == v)
            return;

        if (sz[u] < sz[v]) {
            swap(u, v);
        }
        sz[u] += sz[v];
        par[v] = u;
    }
};

int main() {
    int num_of_nodes, num_of_edges;
    cout << "Enter the number of nodes: ";
    cin >> num_of_nodes;
    cout << "Enter the number of edges: ";
    cin >> num_of_edges;

    vector<pair<int, pair<int, int>>> edges;

    cout << "Enter the edges (u, v, w):\n";
    for (int i = 0; i < num_of_edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({ w, {u, v} });
    }

    dsu ds;
    ds.init(num_of_nodes);

    sort(edges.begin(), edges.end());

    int cost = 0, edge_count = 0;

    for (const auto& edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;
        int c = edge.first;
        if (ds.find_par(u) != ds.find_par(v)) {
            ds.connect(u, v);
            cost += c;
            edge_count++;
        }
        if (edge_count == num_of_nodes - 1)
            break;
    }

    if (edge_count == num_of_nodes - 1) {
        cout << "Minimum Cost of Spanning Tree: " << cost << endl;
    }
    else {
        cout << "The graph is disconnected. MST is not possible." << endl;
    }

    return 0;
}
