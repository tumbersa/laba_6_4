#include <iostream>
#include <fstream>
using namespace std;

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(int dist[], bool sptSet[],int n)
{

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 1; v < n+1; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
        else {}

    return min_index;
}

// A utility function to print the constructed distance
// array
void printSolution(int dist[],int n)
{
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 1; i < n+1; i++)
        cout << i << " \t\t\t\t" << dist[i] << endl;
}

int countWay(int** graph,int n,int v){
    int k=0;
    for(int i=1;i<n+1;i++){
        if (graph[i][v]!=0)
            k++;
    }
    return k;
}
// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
void dijkstra(int** graph, int src, int n,int m2,ofstream& f2)
{

    int* dist = new int[n+1]; // The output array. dist[i] will hold the
    // shortest
// distance from src to i
int* predPoint =new int[n+1];
int*fullWay = new int[n+1];
    bool* sptSet = new bool [n+1]; // sptSet[i] will be true if vertex i is
    // included in shortest
// path tree or shortest distance from src to i is
// finalized

// Initialize all distances as INFINITE and stpSet[] as
// false
    for (int i = 0; i < n+1; i++)
        dist[i] = INT_MAX, sptSet[i] = false,predPoint[i]=0,fullWay[i]=0;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;
dist[0]=0;
sptSet[0]=true;
    // Find shortest path for all vertices
    for (int count = 0; count < n - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = minDistance(dist, sptSet,n);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 1; v < n+1; v++)

            // Update dist[v] only if is not in sptSet,
            // there is an edge from u to v, and total
            // weight of path from src to v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v]
                && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v]) {
                if (v != m2)
                    dist[v] = dist[u] + graph[u][v] + countWay(graph, n, v);
                else
                    dist[v] = dist[u] + graph[u][v];
                predPoint[v]=u;
            }
        printSolution(dist,n);
    }

    // print the constructed distance array
    printSolution(dist,n);
    cout<<endl<<dist[m2]<<endl;
    int s=m2;
    cout<<m2<<" ";
    fullWay[m2]=m2;
    while (s!=src){
        fullWay[predPoint[s]]=predPoint[s];
        cout<<predPoint[s]<<' ';
        s=predPoint[s];
    }
    cout<<endl;

    f2<<dist[m2]<<'\n';
    for (int i=0;i<n+1;i++)
        if (fullWay[i]!=0) {
            cout << fullWay[i] << ' ';
            f2<<fullWay[i]<<' ';
        }

    delete[] dist;
    delete[] sptSet;
}
void print(int** a, int n) {
    for (int i = 0; i < n+1; i++)
    {
        for (int j = 0; j < n + 1; j++)
            if (j == 0)cout << i << '\t';
            else if (i == 0) cout << j << '\t';
            else
                cout<<a[i][j]<< '\t';
        cout << endl;
    }
}
int main()
{
    int n,k;
    ifstream f("A.txt");
    ofstream f2("B.txt");
    f >> n;
    f >> k;
    int m1, m2;
    f >> m1 >> m2;
    int** adjMat=new int*[n+1];
    for (int i = 0; i < n+1; i++)
        adjMat[i] = new int[n+1];
    int u, v,t;
    for (int i = 0; i < n+1; i++)
    {
        for (int j = 0; j < n+1; j++)
            adjMat[i][j] = 0;
    }
    for (int i = 0; i < k;i++) {
        f >> u >> v >> t;
        adjMat[u][v] = t;
        adjMat[v][u] = t;
    }
    print(adjMat,n);
    dijkstra(adjMat,m1, n,m2,f2);
    for (int i = 0; i < n; i++)
    {
        delete[] adjMat[i];
    }

    delete[] adjMat;
    return 0;
}