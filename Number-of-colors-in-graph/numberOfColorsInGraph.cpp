#include "numberOfColorsInGraph.h"

int main() {

    // citim nr. de varfuri si nr. de muchii
    int vertexes, edges;
    fin >> vertexes >> edges;

    // matricea de adiacenta
    vector<vector<bool>> graph(vertexes, vector<bool>(vertexes));   

    // vector de varfuri vizitate ( g_visited[i] = true <=> nodul a fost vizitat in BFS)
    vector<bool> visited(vertexes, false);   

    // vector de culori ( v[i] = n <=> varful i are culoare n, n -> nr. natural)  
    vector<int> colors(vertexes, -1);   

    // citim muchiile din fisier
    int x, y;
    for (int i = 0; i < edges; i++) {
        fin >> x >> y;
        graph[x][y] = true;
        graph[y][x] = true;
    }

    // echivalam valorile globale pentru nr. varfuri si de muchii, atat si pentru vectorul de culori, matricea de adiacenta cat si cel de varfuri vizitate,
    // cu cele locale, pentru a le folosi pe cele globale, in scopul usurarii muncii
    // ( reducem numarul de parametrii primite ale functiilor )
    g_vertexes = vertexes;
    g_edges = edges;
    g_colors = colors;
    g_visited = visited;
    g_graph = graph;

    // aplicam procedura BFS pentru toate varfurile nevizitate din graf
    // daca graful este conex, se va apela o singura data BFS
    // for-ul asigura ca, in cazul a mai multor componente conexe, se parcurge algoritmul pentru toate astfel de componente
    // marcam nodul de start ( un nod nevizitat inca ) ca vizitat
    for (int i = 0; i < vertexes; i++) {
        if (!g_visited[i]) {
            g_visited[i] = true;
            BFS(i);
        }
    }

    // scriem in fisier numarul de culori necesare, cat si culorile fiecarui varf
    fout << maxColor + 1 << endl;
    for (int i = 0; i < vertexes; i++) 
        fout << g_colors[i] << " ";

    return 0;
}

void BFS(int startNode) {
    
    // initializam un queue pentru procedura BFS
    // initial, doar nodul sursa face parte din queue
    queue<int> q;
    q.push(startNode);

    while (!q.empty()) {

        // extragem primul varf din coada
        int currentVertex = q.front();
        q.pop();

        // in neighbors primim toti vecinii varfului curent
        vector<int> neighbors = getNeighbors(currentVertex, g_graph);
        
        // in visitedNeighbors primim toti vecinii vizitati ai varfului curent
        vector<int> visitedNeighbors = getVisitedNeighbors(neighbors, g_visited);
        
        // in color obtinem cea mai mica culoare posibila pentru varful curent ( unde culoare este un numar natural mai mare ca 0, care
        //                                                                       nu apare la niciun vecin )
        // ii dam varfului curent culoarea obtinuta
        int color = generateColor(visitedNeighbors);
        g_colors[currentVertex] = color;

        // daca culoarea curenta este mai mare ca nr. de culori, nr. de culori este actualizat
        if (color > maxColor)
            maxColor = color;

        // pentru toti vecinii nevizitati ai varfului curent, ii adaugam in coada pentru procedura BFS si ii marcam ca vizitati
        for (auto x : neighbors) {
            if (!g_visited[x]) {
                g_visited[x] = true;
                q.push(x);
            }
        }
    }
}

vector<int> getNeighbors(int currentVertex, vector<vector<bool>> g_graph) {

    vector<int> neighbors;

    // adaugam toti vecinii varfului currentVertex in vectorul neighbors
    // ( doua varfuri i si j sunt vecine daca si numai daca valoarea de linie/coloana i si coloana/linie j este true)
    for (int i = 0; i < g_vertexes; i++)
        if (g_graph[i][currentVertex] == true) 
            neighbors.push_back(i); // If a certain element is linked with currentVertex -- neighbor
    return neighbors;
}

vector<int> getVisitedNeighbors(const vector<int>& neighbors, const vector<bool>& g_visited) {

    // adaugam toti vecinii vizitati ai varfului currentVertex, afltati in vectorul neighbors, in vectorul visitedNeighbors
    // ( un varf vecin i este vizitat daca si numai daca g_visited[i] este true)
    vector<int> visitedNeighbors;
    for (auto x : neighbors) 
        if (g_visited[x] == true) 
            visitedNeighbors.push_back(x);
    return visitedNeighbors;
}

int generateColor(const vector<int>& visitedNeighbors) {

    // gasim cea mai mica culoare pentru varful curent
    // pornind de la 1, incrementam culoarea de fiecare data cand exista deja un vecin care are culoare respectiva
    // while-ul se opreste cand am gasit o culoare nefolosita de niciunul dintre vecini
    int color = 0;
    while (colorIsUsed(color, visitedNeighbors))
        color++;
    return color;
}

bool colorIsUsed(int color, const vector<int>& visitedNeighbors) {

    // daca unul dintre vecinii varfului este deja de culoarea color, returnam true
    // altfel, false
    for (const auto& x : visitedNeighbors)
        if (g_colors[x] == color) 
            return true;
    return false;
}