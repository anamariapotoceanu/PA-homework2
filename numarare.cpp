/* Pentru aceasta problema, am luat rezolvarea de la task-2 din laboratorul
6 pus la dispozitie de echipa pe teams, respectiv TopSort - BFS: algoritmul lui
Kahn, din laboratoarele rezolvate. */

#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#define NMAX 100005
#define MOD 1000000007
using namespace std;

vector<int> solve_bfs(vector<int> adj[], vector<int>& in_degree, int n) {
    // Step 0: initializare topsort - permutare vida initial
    vector<int> topsort;

    // Step 1: declaram o coada in care putem baga noduri
    queue<int> q;

    // Step 2: pasul initial: pun in coada TOATE nodurile cu grad intern 0
    for (int node = 1; node <= n; ++node) {
        if (in_degree[node] == 0) {
            q.push(node);
        }
    }

    // Step 3: parcurg in latime graful
    while (!q.empty()) {
        // 3.1: SCOT primul nod din coada
        int node = q.front();
        q.pop();

        // adaug la solutie elementul scos
        topsort.push_back(node);

        // 3.2 Ii parcurg toti vecinii
        for (auto neigh : adj[node]) {
            // sterg muchia node->neigh
            // obs1. NU e nevoie sa o sterg la propriu
            //       Daca nu am cicluri, nu se va ajunge aici
            // obs2. Simulez stergerea prin scaderea gradului intern a lui neigh
            --in_degree[neigh];

    // daca neigh a ajuns nod cu grad intern 0, atunci este adaugat in coada
            if (in_degree[neigh] == 0) {
                q.push(neigh);
            }
        }
    }

    // Step 4: verifica ca topsort chiar reprezinta o sortare topologica valida
    // Ce inseamna asta? S-au sters toate muchiile din graf.
    // Daca nu s-a sters tot, atunci graful este ciclic!
    bool is_valid = true;
    for (int node = 1; node <= n; ++node) {
        if (in_degree[node] > 0) {
            is_valid = false;
            break;
        }
    }

    if (is_valid) {
        return topsort;  // sortarea topologica obtinuta
    } else {
        return {};  // vector gol == nu se poate face o sortare topologica
    }
}

/* Pentru fiecare nod din sortarea topologica, vom lua fiecare vecin adiacent.
    Facem verificarea daca muchia care se afla in primul graf 
    apare si in al doilea graf, mai exact daca nodurile adiacente din cele
    doua grafuri sunt aceleasi.
*/
void get_nr_path(vector<int> adj1[], vector<int> adj2[], vector<int>& edges,
                vector<int>& topSort) {
    for (auto node : topSort) {
        for (auto node1 : adj1[node]) {
            for (auto node2 : adj2[node]) {
                // Daca avem noduri adiacente comune in cele doua grafuri
                // actualizam numarul de muchii care ajung in nodul
                // respectiv pornind din nodul 1.
                if (node1 == node2) {
                    edges[node1] = (edges[node1] + edges[node]) % MOD;
                }
            }
        }
    }
}

int main() {
    ifstream fin("numarare.in");
    int n, m, i;
    int x, y;
    vector<int> adj1[NMAX];
    vector<int> adj2[NMAX];
    fin >> n;
    fin >> m;

    vector<int> in_degree(n + 1, 0);
    vector<int> topSort;
    vector<int> edges(NMAX, 0);
    edges[1] = 1;


    for (i = 0; i < m; i++) {
        fin >> x >> y;
        adj1[x].push_back(y);
        in_degree[y]++;
    }

    for (i = 0; i < m; i++) {
        fin >> x >> y;
        adj2[x].push_back(y);
    }

    fin.close();
    // Determinam sortarea topologica
    topSort = solve_bfs(adj1, in_degree, n);
    get_nr_path(adj1, adj2, edges, topSort);


    ofstream fout("numarare.out");
    // Numarul de lanturi elementare de la nodul 1 la nodul n
    fout << edges[n]<< "\n";

    fout.close();
    return 0;
}
