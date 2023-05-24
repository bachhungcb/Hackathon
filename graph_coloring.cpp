#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Vertex {
    int id;
    int degree;
    int color;
};

bool compareDegree(const Vertex &a, const Vertex &b) {
    return a.degree > b.degree;
}

int main() {
    ifstream input("dothi.txt");
    ofstream output("dothitomau.txt");

    int n, m;
    input >> n >> m;

    vector<vector<int>> graph(n);
    vector<Vertex> vertices(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        input >> u >> v;
        u--; v--;

        graph[u].push_back(v);
        graph[v].push_back(u);

        vertices[u].degree++;
        vertices[v].degree++;
    }

    for (int i = 0; i < n; i++) {
        vertices[i].id = i;
    }

    sort(vertices.begin(), vertices.end(), compareDegree);

    int max_color = 0;
    for (Vertex &vertex : vertices) {
        vector<bool> used_colors(n + 1, false);

        for (int neighbor : graph[vertex.id]) {
            used_colors[vertices[neighbor].color] = true;
        }

        int color;
        for (color = 1; color <= n; color++) {
            if (!used_colors[color]) {
                break;
            }
        }

        vertex.color = color;
        max_color = max(max_color, color);
    }

    output << max_color << endl;

    vector<int> result(n);
    for (const Vertex &vertex : vertices) {
        result[vertex.id] = vertex.color;
    }

    for (int i = 0; i < n; i++) {
        output << result[i] << endl;
    }

    input.close();
    output.close();

    return 0;
}
