/* Am folosit codul de la Algoritmul Dijkstra din laboratoarele rezolvate.
Solutia se afla pe Teams, laborator 8, task-2.*/

#include <fstream>
#include <vector>
#include <set>
#include <climits>
#define NMAX 100005
#define INF LONG_MAX

using namespace std;

struct DijkstraResult {
    vector<long> d;
    vector<int> p;

    DijkstraResult(const vector<long>& d, const vector<int>& p)
        : d(d)
        , p(p) { }
};

DijkstraResult dijkstra(int source, int nodes,
            vector<pair<int, int>> adj[NMAX]) {
    // Initializam vectorul de distante cu distante infinite.
    vector<long> d(nodes + 1, INF);
    vector<int> p(nodes + 1, 0);

    // In loc de un priority_queue<> folosim set<>, cu elemente tupluri de
    // tipul (distanta pana la nod, nod). Setul tine elementele ordonate, deci
    // mereum in pq.begin() vom avea tuplul care ii corespunde nodului cu
    // distanta minima.
    set<pair<long, int>> pq;

    // Inseram nodul de plecare in coada si ii actualizam distanta.
    d[source] = 0;
    pq.insert({d[source], source});

    while (!pq.empty()) {
        // Scoatem top-ul.
        auto top = pq.begin();
        const auto [_, node] = *top;
        pq.erase(top);

        // Ii parcurgem toti vecinii.
        for (const auto& [neigh, w] : adj[node]) {
            // Se imbunatateste distanta?
            if (d[node] + w < d[neigh]) {
                // Scoatem vechea pereche/distanta din set.
                pq.erase({d[neigh], neigh});

                // Actualizam distanta si parintele.
                d[neigh] = d[node] + w;
                p[neigh] = node;

                // Inseram noua distanta.
                pq.insert({d[neigh], neigh});
            }
        }
    }
    // Toate nodurile catre care distanta este inca INF nu pot fi atinse din
        // nodul source, deci le setam pe -1.
    for (int node = 1; node <= nodes; node++) {
        if (d[node] == INF) {
            d[node] = -1;
        }
    }

    return {d, p};
}

long getCost(int n, vector<long> distX, vector<long> distY,
            vector<long> distZ) {
    long minCost, total;
    minCost = INF;
    int node;
    // Vom considera fiecare nod, un nod intermediar
    for (node = 1; node <= n; node++) {
        // Nodurile catre care distanta a ramas INF, au fost setate cu -1
        // Pe acestea nu le vom lua in considerare.
        if (distX[node] == -1 || distY[node] == -1 || distZ[node] == -1) {
            continue;
        }
        // avem costul de la nodul x la nodul curent: distX[node]
        // costul de la nodul y la nodul curent: distY[node]
        // costul de la nodul curent la nodul final: distZ[node]
        total = distX[node] + distY[node] + distZ[node];
        minCost = min(minCost, total);
    }
    return minCost;
}

int main() {
    ifstream fin("drumuri.in");
    vector<pair<int, int>> graph[NMAX];
    vector<pair<int, int>> reverseGraph[NMAX];

    int n, m, a, b, c, i, x, y, z;
    long minCost = INF;
    vector<long> distX;
    vector<long> distY;
    vector<long> distZ;
    fin >> n >> m;

    for (i = 0; i < m; i++) {
        fin >> a >> b >> c;
        graph[a].push_back({b, c});
        // Determinam graful invers
        reverseGraph[b].push_back({a, c});
    }
    fin >> x >> y >> z;

    fin.close();
    // Aflam distanta de la nodurile x si y la toate celelalte noduri
    distX = dijkstra(x, n, graph).d;
    distY = dijkstra(y, n, graph).d;
    // Aflam distanta de la toate celelalte noduri la nodul z
    distZ = dijkstra(z, n, reverseGraph).d;

    minCost = getCost(n, distX, distY, distZ);
    ofstream fout("drumuri.out");

    fout << minCost << "\n";
    fout.close();

    return 0;
}
