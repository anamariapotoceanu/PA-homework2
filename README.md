
# PA - Tema 2 - Politisti, Programatori si Scandal

# Numarare

- Pentru fiecare matrice in parte, am retinut matricea de adiacenta. Fiecare
nod din graf va avea asociat un vector cu numere intregi, reprezentand
nodurile adiacente. Matricele de adiacenta, adj1, respectiv adj2, le-am creat
in momentul in care am citit nodurile intre care exista o muchie. 
Pentru Algoritm TopSort cu BFS, am avut nevoie si de gradul intern al fiecarui
nod, pe care l-am retinut in vectorul in_degree.
- Urmatorul pas a fost sa determinam sortarea topologica pentru primul graf.
Pentru a calcula numarul de lanturi elementare din cele doua grafuri, am
parcurs fiecare nod din sortarea topologica. Pentru fiecare nod, parcurgem
cele doua liste de adiacenta. Verific daca exista un nod comun adiacent pentru
nodul curent in cele doua grafuri, mai exact daca avem muchii comune.
- Trebuie sa determinam numarul lanturile elementare comune. Astfel o muchie
care apare in graful 1 trebuie sa se regaseasca si in graful 2 pentru a putea
determina aceste lanturi.
- In cazul in care o muchie apare atat in primul graf, cat si in al doilea,
vom actualiza numarul de muchii care ajung in nodul pentru care se face
verficarea.
- Pentru fiecare nod in parte se calculeaza in cate moduri se poate ajunge
la el, pornind din nodul 1. Vom retine in vectorul edges.

- Complexitatea pentru aceasta problema este T(n) = O(n + m)

# Trenuri

- Am modificat astfel incat am considerat fiecare nod un string, pentru
a lucra mai usor cu orasele.
- Graful are drept noduri stringuri, reprezentand numele oraselor. Matricea
de adiacenta am definit-o ca un unordered_map, unde cheia este orasul, iar
valoarea reprezinta totalitatea oraselor in care se poate ajunge pornind din
orasul curent.
- Pentru fiecare nod in parte, am retinut si daca a fost sau nu vizitat:
visited. Pentru a calcula distanta maxima, mai exact sa avem un numar maxim de
orase prin care putem trece, vom folosi programare dinamica: dp.
- Distanta pentru nodul de start am setat-o cu 1. Pentru prelucrarea
distantelor maxime pentru celelalte orase, am realizat o sortare topologica.
Am utilizat sortarea topologica din cadrul laboratorului. Sortarea topologica
este utila pentru a determina intr-un mod cat mai eficient distantele.
Pentru fiecare oras din sortarea topologica, parcurgem vectorul cu nodurile
adiacente. Astfel, pentru fiecare vecin, am actualizat distanta maxima.
- In final, am afisat distanta maxima de la nodul de start la nodul final, mai
exact, numarul maxim de orase vizitate pentru a ajunge la destinatia finala.

- Complexitatea pentru aceasta problema este T(n) = O(n + m)

# Drumuri

- Pentru fiecare nod x, y, z vom retine:
*distX este lungimea minima de la nodul x la toate celelalte noduri din graf.*
*distY este lungimea minima de la nodul y la toate celelalte noduri din graf.*
*distZ este lungimea minima de la toate celelalte noduri din graf la nodul z.*

- Deoarece trebuie sa gasim un drum care pleaca din nodul x, respectiv y
si ajunge in z, este nevoie sa aflam si graful inversat. Distantele minime
trebuie calculate pentru drumurile care ajung in z (reverseGraph).
Graful inversat il aflam atunci cand citim toate muchiile si costurile.
- Dupa aflarea distantelor minime de la nodurile x si y, prin aplicarea
Algoritmului Dijkstra, vom retine si distantele minime de la celelalte noduri
la nodul destinatie. Pentru a face acest lucru, aplicam Algoritmul Dijkstra,
pe graful inversat.
 *Functia getCost*
- Cum trebuie sa existe un drum de la nodul x, la nodul z, vom parcurge
lista de noduri si vom considera fiecare nod ca fiind un nod intermediar
prin care se va trece. Astfel trebuie sa existe drum de la x la node.
Distanta minima va fi distX[node](costul). Acelasi lucru este valabil si pentru
drumul de la nodul y la nodul z. Avem distY[node](costul). Pentru a putea ajunge
la nodul final, z, trebuie sa luam in considerare si distanta de la node
la z, mai exact distZ[node](costul).
- Se va calcula pentru fiecare nod interemediar costul total.
- Distanța minimă între noduri este costul total al drumului cu costul
cel mai mic care leagă nodurile.

- Complexitate temporală: T = O((n + m) ∗ logn) sau O(|E|∗log|V|)
- Complexitate spațială : S = O(n + m)
