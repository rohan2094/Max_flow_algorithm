/*
DSA PROJECT (CS201) SUBMISSION
Topic -> Maximum Flow using Ford Fullkerson's Algorithm
$$ Created by ->
    Rohan (2020CSB1117) 
    Raghav (2020CSB1115) 
    Rohit Kinha (2020CSB1118) 
*/

// Header files included
#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 10000 // Assuming there will be atmost 10000 Nodes

// Colors for BFS
//#define WHITE 0
//#define GRAY 1
//#define BLACK 2

int N;      // Number of vertices
int Source; // Source Vertex
int Sink;   // Sink Vertex

int Capacity[MAX_NODES][MAX_NODES]; // 2D matrix to store Capacities of edges \
// Capacity[i][j] will store capacity of edge (i->j)

int color[MAX_NODES]; // Needed in BFS part

// structure for queue
struct queue
{
    int data;
    struct queue *next;
} *front = NULL, *rear = NULL;

//declaring enqueue function to enter an element in the queue
void enqueue(int x)
{
    struct queue *t;
    t = (struct queue *)malloc(sizeof(struct queue));
    if (t == NULL)
        printf("Queue is Full\n");
    else
    {
        t->data = x;
        t->next = NULL;
        if (front == NULL)
            front = rear = t;
        else
        {
            rear->next = t;
            rear = t;
        }
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
    else // else it will return the value at front
    {
        int temp = front->data;
        t = front;
        front = front->next;
        free(t);
        return temp;
    }
}
void BFS(int Capacity[][], int source, int N)
{
    int i = source, j;

    int visited[] = {0};

    printf("%d ", i);
    visited[i] = 1;
    enqueue(i);
    int u = dequeue();
    while (u != -1)
    {
        
        for (j = 1; j < N; j++)
        {
            if (Capacity[i][j] != 0 && visited[j] == 0)
            {
                printf("%d ", j);
                visited[j] = 1;
                enqueue(j);
            }
        }
        u = dequeue();
    }
}

int MaxFlowCalculate()
{
    int max_flow = 0;
    // Logic to be added
    return max_flow;
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
    printf("Once you are done, enter -1 to quit.\n");
    while (1)
    {
        int left;
        int right;
        int cap;
        scanf("%d", &left);
        if (left == -1)
        {
            break;
        }
        scanf("%d %d", &right, &cap);
        Capacity[left][right] = cap;
    }

    printf("Enter the source vertex: ");
    scanf("%d", &Source);
    printf("Enter the sink vertex: ");
    scanf("%d", &Sink);

    printf("Maximum flow from vertex %d to vertex %d is %d\n", Source, Sink, MaxFlowCalculate());
    return 0;
}