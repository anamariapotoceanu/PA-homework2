/* Pentru aceasta problema am folosit algoritmul implementat de catre echipa
de PA, pus la dispozitie pe Teams.
Am folosit rezolvarea de la laboratorul 6, task-2, pentru TopSort - DFS.*/
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

// porneste o parcurgere DFS din node
// foloseste vectorul used pentru a marca nodurile vizitate
void dfs(const string& node, unordered_map<string, int>& used,
        vector<string>& topsort, unordered_map<string, vector<string>>& adj) {
    used[node] = 1;  // marcheze nodul ca fiind vizitat

    // parcurg vecinii
    for (auto& neigh : adj[node]) {
        if (!used[neigh]) {
            dfs(neigh, used, topsort, adj);
        }
    }

    // dupa ce am vizitat recursiv toti vecinii, adaugam
    // nodul la sortare
    topsort.push_back(node);
}

vector<string> solve_dfs(unordered_map<string, int>& used,
                        unordered_map<string, vector<string>>& adj) {
    // vectorul rezultat
    vector<string> topsort;

    // pentru fiecare nod
    for (auto& node : used) {
        string city = node.first;
        // daca nodul este nevizitat, pornim o parcurgere
        if (!used[city]) {
            dfs(city, used, topsort, adj);
        }
    }
    // rezultatul a fost obtinut in ordine inversa
    reverse(topsort.begin(), topsort.end());

    return topsort;
}

int main() {
    ifstream fin("trenuri.in");
    int m;
    size_t j;
    size_t i;
    string city_start, city_final;
    fin >> city_start;
    fin >> city_final;

    fin >> m;

    // Matricea de adiacenta reprezentata printr-o cheie, care reprezinta
    // orasul curent si valoarea ca find un vector de stringuri care semnifica
    // orasele in care se poate ajunge
    unordered_map<string, vector<string>> adj;
    string x, y;

    // Pentru fiecare oras in parte retinem daca a fost vizitat intr-un
    // unordered_map
    unordered_map<string, int> visited;
    // Vom retine distantele maxime de la orasul de start la celelalte orase
    unordered_map<string, int> dp;

    for (int i = 0; i < m; i++) {
        fin >> x;
        fin >> y;
        visited[x] = 0;
        visited[y] = 0;
        dp[x] = 0;
        adj[x].push_back(y);
    }
    fin.close();

    vector<string> topsort;

    dp[city_start] = 1;

    topsort = solve_dfs(visited, adj);

    // Pentru fiecare nod din sortarea topologica, vom parcurge lista de vecini
    // si vom actualiza distanta maxima
    for (i = 0; i < topsort.size(); i++) {
        string city = topsort[i];
        // Verificam daca exista o cale de la orasul de start la orasul curent
        if (dp[city] != 0) {
            for (j = 0; j < adj[city].size(); j++) {
                string neighbor = adj[city][j];
                dp[neighbor] = max(dp[neighbor], dp[city] + 1);
            }
        }
    }
    ofstream fout("trenuri.out");
    // Afisam numarul maxim de orase care pot fi vizitate, mai exact distanta
    // maxima de la orasul de start la destinatie
    fout << dp[city_final] << "\n";

    fout.close();

    return 0;
}
