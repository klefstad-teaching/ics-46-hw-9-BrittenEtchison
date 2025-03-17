#include "dijkstras.h"




vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.size();
    vector <int> distances(numVertices, INF);
    vector <bool> visited(numVertices, false);
    distances[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});
    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (Edge edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}
vector<int> extract_shortest_path(const vector<int>& previous, int destination) {
    vector<int> shortest_path;
    int curr_vertex = destination;
    while (curr_vertex != UNDEFINED) {
        shortest_path.push_back(curr_vertex);
        curr_vertex = previous[curr_vertex];
    }
    reverse(shortest_path.begin(), shortest_path.end());
    return shortest_path;

}
void print_path(const vector<int>& v, int total) {
    if (total == INF)
        cout << "No path found. \n";
        return;

    for (int vertex : v)
        cout << vertex << " ";
    cout << endl;
    cout << "Total cost is " << total << endl;
}
string get_arg(int argc, char *argv[], string def) {
    if (argc > 1)
        return string(argv[1]);
    return def;
}