#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#define INFINITY 100000
int V, E;

// Structure for vertex
typedef struct
{
    int label;
    bool visited;

} Vertex;

// Structure for directed edge from u to v
typedef struct
{
    int u;
    int v;

} Edge;

// Printing Shortest Path Length
void printShortestPathLength(int *path_length)
{
    printf("\nVERTEX \tSHORTEST PATH LENGTH \n");
    int i;
    for (i = 0; i < V; i++)
    {
        printf("%d \t", i);
        if (path_length[i] < INFINITY)
            printf("%d\n", path_length[i]);
        else
            printf("Infinity\n");
    }
}

// Finds weight of the edge that connects Vertex u with Vertex v
int findEdgeWeight(Vertex u, Vertex v, Edge *edges, int *weights)
{
    int i;
    for (i = 0; i < E; i++)
    {
        if (edges[i].u == u.label && edges[i].v == v.label)
        {
            return weights[i];
        }
    }
    // If no edge exists, weight is infinity
    return INFINITY;
}

// Get the minimum path length among the paths
int minimimPathLength(int *path_length, Vertex *vertices)
{
    int i;
    int min_path_length = INFINITY;
    for (i = 0; i < V; i++)
    {
        if (vertices[i].visited == true)
        {
            continue;
        }

        else if (vertices[i].visited == false && path_length[i] < min_path_length)
        {
            min_path_length = path_length[i];
        }
    }
    return min_path_length;
}

int minimimPathVertex(Vertex *vertices, int *path_length)
{
    int i;
    int min_path_length = minimimPathLength(path_length, vertices);

    // Get the vertex with the minimum path length
    // Mark it as visited
    for (i = 0; i < V; i++)
    {
        if (vertices[i].visited == false && path_length[vertices[i].label] == min_path_length)
        {
            vertices[i].visited = true;
            return i;
        }
    }
}

// Dijkstra Algorithm (Serial Version)
void Dijkstra_Serial(Vertex *vertices, Edge *edges, int *weights, Vertex *root)
{
    clock_t serial_start, serial_end;
    double serial_time;
    int path_length[V];

    // Mark first vertex as visited, shortest path = 0
    root->visited = true;
    path_length[root->label] = 0;
    int i, j;
    // Compute distance to other vertices
    for (i = 0; i < V; i++)
    {

        if (vertices[i].label != root->label)
        {
            path_length[vertices[i].label] = findEdgeWeight(*root, vertices[i], edges, weights);
        }
        else
        {

            vertices[i].visited = true;
        }
    }

    serial_start = clock();
    // External For Loop
    for (j = 0; j < V; j++)
    {
        Vertex u;
        // Obtain the vertex which has shortest distance and mark it as visited
        int h = minimimPathVertex(vertices, path_length);
        u = vertices[h];

        // Update shortest path wrt new source
        // Internal For Loop, Serial computation
        for (i = 0; i < V; i++)
        {
            if (vertices[i].visited == false)
            {
                int c = findEdgeWeight(u, vertices[i], edges, weights);
                path_length[vertices[i].label] = std::min(path_length[vertices[i].label], path_length[u.label] + c);
            }
        }
    }
    serial_end = clock();
    printShortestPathLength(path_length);
    serial_time = ((double)(serial_end - serial_start)) / CLOCKS_PER_SEC * 1000; // Convert to milliseconds
    printf("\nRunning time (serial): %.2lf ms\n", serial_time);
}

// Function to generate a random graph
void generateRandomGraph(Vertex *vertices, Edge *edges, int *weights, int density)
{
    // Initialize random number generator
    srand(time(NULL));

    // Generate edges randomly based on the density
    int edge_count = 0;
    for (int i = 0; i < V; i++)
    {
        for (int j = i + 1; j < V; j++)
        {
            if (rand() % 100 < density) // Adjust density as a percentage
            {
                // Random weight for the edge
                int weight = rand() % 100 + 1; // Adjust range of weights as needed

                // Add edge from vertex i to vertex j
                edges[edge_count] = (Edge){.u = i, .v = j};
                weights[edge_count] = weight;
                edge_count++;
            }
        }
    }
}

int main()
{
    printf("==========PARALLEL IMPLEMENTATION OF DIJKSTRA ALGORITHM==========\n");
    printf("\n\t\t\t\t\t\t JANANI HARSHATHA J\n\t\t\t\t\t\t21011101053\n");
    printf("\n\t\t\t\t\t\t LOURTHU MARY RENIGALE\n\t\t\t\t\t\t21011101066\n");
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);
    Vertex vertices[V];
    Edge edges[E];
    int weights[E];

    // Generate a random graph with a specified density (percentage)
    int density;
    printf("Enter graph density (percentage): ");
    scanf("%d", &density);
    generateRandomGraph(vertices, edges, weights, density);

    int source;
    printf("\nEnter Source Vertex: ");
    scanf("%d", &source);
    Vertex root = {source, false};
    printf("Source Vertex: %d\n", source); // Printing the entered source vertex

    Dijkstra_Serial(vertices, edges, weights, &root);

    return 0;
}
