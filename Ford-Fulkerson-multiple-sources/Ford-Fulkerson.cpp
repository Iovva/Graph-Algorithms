#include "Ford-Fulkerson.h"

int main()
{
    // citim nr. de varfuri, nr. de surse si nr. de muchii
    int vertexes, sources, edges;
    fin >> vertexes >> sources >> edges;

    // matricea de adiacenta
    vector<vector<int>> graph(vertexes, vector<int>(vertexes));

    // citim muchiile si ponderile lor din fisier
    int x, y, weight;
    for (int i = 0; i < edges; i++)
    {
        fin >> x >> y >> weight;
        graph[x][y] = weight;
    }

    // echivalam valorile globale pentru nr. de varfuri, de muchii si de surse, atat si pentru matricea de adiacenta,
    // cu cele locale, pentru a le folosi pe cele globale, in scopul usurarii muncii
    // ( reducem numarul de parametrii primite ale functiilor )
    g_vertexes = vertexes;
    g_edges = edges;
    g_sources = sources;
    g_graph = graph;

    // algoritmul Ford-Fulkerson returneaza max_flow-ul primit de destinatie,
    // dar modifica si graful rezidual
    int max_flow = fordFulkerson();
    fout << max_flow << "\n";

    // pentru fiecare nod sursa, calculam fluxul iesit si il afisam
    // ( adunand fluxul doar daca varfurile sunt legate )
    for (int i = 0; i < g_sources; i++) {
        int flowSource = 0;
        for (int j = 0; j < g_vertexes; j++) {
            if (g_graph[i][j] != 0)
                flowSource += g_residualGraph[j][i];
        }
        fout << flowSource << " ";
    }

    return 0;
}


int fordFulkerson() {
    
    // initializam vectorul global de parinti si matricea globala a grafului rezidual
    initFordFulkerson();

    int u, v;

    // nodul sursa este nr. varfurilor intrucat este primul numar 
    // ce poate fi luat drept nod al grafului, dupa cele existente deja
    // ( putea fi orice numar natural neaparut in graf )
    int source = g_vertexes;

    int destination = g_vertexes - 1;
    int max_flow = 0;

    // procedura BFS verifica daca exista drum de la start la destinatie
    // si actualizeaza vectorul g_parent, pentru a reprezenta drumul de crestere
    // prin parintii fiecarui nod
    // este adevarat ca se actualizeaza inutil si cateva noduri care nu fac parte
    // din drumul de crestere
    while (BFS(g_vertexes, source, destination)) {

        // cauta "bottleneck-ul" 
        // parcurge drumul de crestere si gaseste arcul cu fluxul cel mai mic
        int path_flow = INT_MAX;
        for (v = destination; v != source; v = g_parent[v])
        {
            u = g_parent[v];
            path_flow = min(path_flow, g_residualGraph[u][v]);
        }

        // actualizeaza ponderile arcelor din drumul de crestere
        for (v = destination; v != source; v = g_parent[v])
        {
            u = g_parent[v];
            g_residualGraph[u][v] -= path_flow;
            g_residualGraph[v][u] += path_flow;
        }

        // adaugam la flow-ul primit pana acum de destinatie valoarea obtinuta din iteratia curenta
        max_flow += path_flow;
    }

    // functia returneaza flow-ul total primit de destinatie
    return max_flow;
}

void initFordFulkerson() {
    
    int u, v;

    // nodul sursa este nr. varfurilor intrucat este primul numar 
    // ce poate fi luat drept nod al grafului, dupa cele existente deja
    // ( putea fi orice numar natural neaparut in graf )
    int source = g_vertexes;

    // matricea de adiacenta a grafului residual
    vector<vector<int>> residualGraph(g_vertexes + 1, vector<int>(g_vertexes + 1));

    // realizam o copie a ponderilor din graful initial in cel rezidual
    for (u = 0; u < g_vertexes; u++)
        for (v = 0; v < g_vertexes; v++)
            residualGraph[u][v] = g_graph[u][v];

    // adaugam un varf sursa "artificial" care trimite flux, in cantintate infinita,
    // la toate sursele, care devin astfel varfuri oarecare in reteaua de flux
    for (int i = 0; i < g_sources; i++) {
        residualGraph[source][i] = INT_MAX;
    }

    // echivalam valorea globale pentru matricea de adiacenta a grafului residual
    // acelasi motiv ca la celelalte variabile globale
    g_residualGraph = residualGraph;

    // echivalam valorea globale pentru vectorul de parinti al varfurilor din graful rezidual
    // acelasi motiv ca la celelalte variabile globale
    vector<int> parent(g_vertexes + 1);
    g_parent = parent;
}

bool BFS(int g_vertexes, int source, int destination) {

    // marcam parintele sursei ca fiind inexistent
    // ( in cazul acesta, sursa este cea "artificiala", creeata de noi, in nici un caz nu una dintre cele initiale )
    g_parent[source] = -1;

    // initializam un vector care arata daca un nod a fost sau nu vizitat in procedura BFS
    // initial, doar sursa este vizitata
    bool* visited = new bool[g_vertexes + 1];
    for (int i = 0; i < g_vertexes; i++)
        visited[i] = false;
    visited[source] = true;

    // initializam un queue pentru procedura BFS
    // initial, doar nodul sursa face parte din queue
    queue<int> queue;
    queue.push(source);
   
    // cat timp coadad nu este goala si destinatia nu a fost vizitata se executa algoritmul
    while (!queue.empty() and visited[destination] != true) {

        // extragem primul varf din coada
        int currentVertex = queue.front();
        queue.pop();

        // pentru fiecare varf din graful rezidual, exceptand sursa "artificiala", executa
        for (int v = 0; v < g_vertexes; v++) {
            
            // daca varful nu a fost vizitat, si fluxul transmis din 
            // varful curent in alt varf din graful rezidual este mai mare ca 0, executa
            if (visited[v] == false && g_residualGraph[currentVertex][v] > 0)
            {

                // adauga varful in coada pentru procedura BFS si il marcam ca vizitat
                // de asemenea, actualizam parintele varfului nou ( din vectorul de parinti ) descoperit cu varful curent
                queue.push(v);
                g_parent[v] = currentVertex;
                visited[v] = true;
            }
        }
    }

    // daca s-a ajuns gasit un drum de la start la destinatie, returneaza true
    // dezaloca vectorul de varfuri vizitate
    if (visited[destination] == true) {
        delete[] visited;
        return true;
    }

    // daca nu s-a ajuns gasit un drum de la start la destinatie, returneaza false
    // dezaloca vectorul de varfuri vizitate
    delete[] visited;
    return false;
}