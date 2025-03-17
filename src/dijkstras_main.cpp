#include "dijkstras.h"

int main(int argc, char *argv[]) {
    string filename = get_arg(argc, argv, "../src/small.txt");
    Graph G;
    file_to_graph(filename, G);
    int numVertices = G.size();
    vector<int> previous(numVertices, UNDEFINED);
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    for ( int i = 0; i < numVertices; ++i) {
        vector<int> shortest_path = extract_shortest_path(distances, previous, i);
        print_path(shortest_path, distances[i]);
    }
}