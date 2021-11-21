#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 10000 // Assuming there will be atmost 10000 Nodes

int N; // Number of vertex in graph

int Capacity[MAX_NODES][MAX_NODES];
// 2D matrix to store Capacities of edges
// Capacity[i][j] will store capacity of edge (i->j)

// structure for queue
struct queue
{
    int data;           // stores the data
    struct queue *next; // pointer to next node of graph
} *front = NULL, *rear = NULL;

//declaring enqueue function to enter an element in the queue
void enqueue(int x)
{
    struct queue *t;                                  // creating new node for new element
    t = (struct queue *)malloc(sizeof(struct queue)); // allocating memory dynamically
    t->data = x;                                      // updating value/data of node
    t->next = NULL;                                   //updating next to NULL

    if (front == NULL)
        front = rear = t;
    else
    {
        rear->next = t;
        rear = t;
    }
}
// delete an element from queue
int dequeue()
{
    struct queue *t;
    if (front == NULL)
    {
        return -1; // the function will return -1 if queue is empty
    }
    int temp = front->data;
    t = front;           // copy the data of front to temp
    front = front->next; // updating front to next node
    free(t);             // now we free t
    return temp;         // returning the pop up element
}

// BFS algorithm to check weather the path exist between the source and sink or not
// if yes then it also tells exact the path, since it also maintain parent array

int BFS(int rgraph[N][N], int src, int snk, int parent[N])
{
    int ssrc = src; //copying the source
    int x = 0;

    int visited[N]; // maintains whether we visit particular vertex or not

    for (int i = 0; i < N; i++)
        visited[i] = 0; // initializing visited array to zero

    enqueue(ssrc);     // enqueue source vertex
    visited[ssrc] = 1; // updating visited array
    parent[ssrc] = -1; // parent of source to -1

    int u = dequeue(); // dequeue source to start algorithm from source

    while (u != -1)
    {

        for (int j = 0; j < N; j++)
        {
            if (rgraph[u][j] > 0 && visited[j] == 0) // if residual capacity is > 0 and the vertex is not visited
            {
                visited[j] = 1;

                enqueue(j);

                parent[j] = u;

                if (j == snk) // it checks that whether we reach to sink or not
                {
                    x = 1;
                    break;
                }
            }
        }
        u = dequeue();
    }
    if (x == 1)
        return 1; // if path exist
    else
        return 0; // if path does not exist
}

// This is function to calculate max flow from source to sink

int MaxFlowCalculate(int so, int si)
{
    int max_flow = 0;
    int rCapacity[N][N]; // stores the residual capacity
    int parent[N];       // stores the path basically parent of vertex

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            rCapacity[i][j] = Capacity[i][j]; // coping values from capacity to residual capacity
        }
    }

    while (BFS(rCapacity, so, si, parent)) // while path exist
    {
        long long int PathFlow = 1e9; // initialize path to bigger value

        //below loop for finding minimum flow through each path
        for (int i = si; i != so; i = parent[i]) // loop starts from sink and moves toward source, backward direction
        {
            if (PathFlow < rCapacity[parent[i]][i])
                PathFlow = PathFlow;
            else
                PathFlow = rCapacity[parent[i]][i];
        }

        //below loop for updating values of residual matrix
        for (int i = si; i != so; i = parent[i])
        {
            rCapacity[parent[i]][i] = rCapacity[parent[i]][i] - PathFlow;
            rCapacity[i][parent[i]] = rCapacity[i][parent[i]] + PathFlow;
        }
        max_flow = max_flow + PathFlow;
    }

    return max_flow; // return the maximum flow from source to sink in graph
}

int main()
{
    printf("Enter number of vertices: ");
    scanf("%d", &N);

    // Initializing Capacity 2D matrix to all elements 0
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            Capacity[i][j] = 0;
        }
    }
    printf("Enter edges and capacity as three spaced integers : ");
    printf("\n\nNote That : If you inter x y z then it means egdes goes from x to y i.e x->y , having weight z \n\n");
    printf("             Once you are done, enter -1 to quit.\n");
    while (1)
    {
        int left;  // left vertex
        int right; // right vertex
        int cap;   // capacity of an edge

        scanf("%d", &left);

        if (left == -1)
        {
            break;
        }

        scanf("%d %d", &right, &cap);

        Capacity[left][right] = cap;
    }
    int Source, Sink;

    printf("\nEnter the source vertex: ");
    scanf("%d", &Source);

    printf("Enter the sink vertex: ");
    scanf("%d", &Sink);

    printf("\nMaximum flow from source vertex %d to sink vertex %d is %d\n", Source, Sink, MaxFlowCalculate(Source, Sink));

    return 0;
}
