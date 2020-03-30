#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>
using namespace std;

class Graph {
    private: 
        vector<int> *adj;
        int size;
    public:
        Graph(int size){
            this->size = size;
            adj = new vector<int>[size];
        }

        void add_edge(int u, int v) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> shortest_reach(int start){
            vector<int> distances(size, -1);
            queue<int> q;
            unordered_set<int> seen;

            q.push(start);
            distances[start] = 0;

            seen.insert(start);

            while(!q.empty()) {
               int current = q.front();
               q.pop();

               for (int i = 0; i < adj[current].size(); i++) {
                   int node = adj[current][i];
                   if (seen.find(node) == seen.end()) {
                       q.push(node);
                       seen.insert(node);
                       distances[node] = distances[current] + 6;
                   }
               }
            }
            return distances;
        }
};

int main() {
    int queries;
    cin >> queries;
        
    for (int t = 0; t < queries; t++) {
      
		int n, m;
        cin >> n;
        // Create a graph of size n where each edge weight is 6: 
        Graph graph(n);
        cin >> m;
        // read and set edges
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            // add each edge to the graph
            graph.add_edge(u, v);
        }
		int startId;
        cin >> startId;
        startId--;
        // Find shortest reach from node s
        vector<int> distances = graph.shortest_reach(startId);

        for (int i = 0; i < distances.size(); i++) {
            if (i != startId) {
                cout << distances[i] << " ";
            }
        }

        cout << endl;
    }
    
    return 0;
}