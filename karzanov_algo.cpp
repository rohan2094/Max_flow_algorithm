// CS-302 Analysis and design of algorithm

#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;
#define MAX_NODES 1000

int N; // Number of vertices
int Capacity[MAX_NODES][MAX_NODES];
int NodeAtLevel[MAX_NODES][MAX_NODES];
int Flow[MAX_NODES][MAX_NODES];
int mxLevel = -1 ;
// structure for queue
struct queue
{
    int data;           // stores the data
    struct queue *next; // pointer to next node of graph
} *front = NULL, *rear = NULL;

struct pair{
    int level;
    int node; 
}
struct pair pr[MAX_NODES];
//declaring enqueue function to enter an element in the queue
void enqueue(int x)
{
    struct queue *t = new queue;                                  // creating new node for new element
    t->data = x;                                   // updating value/data of node
    t->next = NULL;                     //updating next to NULL
    if (front == NULL){
        front =  t;
        rear = t ;
        front->next = NULL;
        rear->next = NULL;
    }
    else
    {
        rear->next = t;
        rear = t;
        rear->next = NULL;
    }
}
// delete an element from queue
int dequeue()
{
    struct queue *t ;
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

void initialize_values(){
    for(int i = 0; i < MAX_NODES ; i++){
        for(int j = 0; j < MAX_NODES ; j++){
            Flow[i][j] = 0 ;
            Capacity[i][j] = 0;
            NodeAtLevel[i][j] = 0;
        }
    }
}
void generate_acyclic_network(int src){
    // Generating level array based on given Graph Capacity[MAX_NODES][MAX_NODES]
    int* level = (int*)malloc((N+1)*sizeof(int));
    
    for(int i = 0; i < N+1 ; i++){
        level[i] = -1;
    }
    enqueue(src) ;
    level[src] = 0 ;
    int u = dequeue();
    while(u!=-1){
        for(int j = 1; j < N+1 ; j++){
            if(Capacity[u][j] != 0){
                enqueue(j);
                level[j] = level[u] + 1 ;
            }
        }
        u = dequeue();
    }
    // Debug output
    for(int i = 1 ; i < N+1; i++){
        if(level[i] > mxLevel){
            mxLevel = level[i];
        }
    }
    for(int i = 1; i <= N ; i++){
        NodeAtLevel[level[i]] = i ;
    }
}

bool balanced_flow_assigned(){
    for(int i = 1 ; i <= n; i++){
        int inDegree = 0 ;
        for(int j = 1 ; j <= n; j++){
            if(Capacity[j][i] != 0){
                inDegree += Flow[j][i];
            }
        }
        int outDegree = 0 ;
        for(int i = 1 ; i <= n; i++){
            for(int j = 1 ; j <= n; j++){
                if(Capacity[i][j] != 0){
                    outDegree += Flow[i][j];
                }
            }
        }
        if(inDegree != outDegree){
            return false;
        }
    }
    return true ;
}


int main(){
    initialize_values();
    cout << "Enter number of vertices: ";
    cin >> N;
    // Initializing Capacity 2D matrix to all elements 0
    printf("Enter edges and capacity as three spaced integers : ");
    printf("\n\nNote That : If you inter x y z then it means egdes goes from x to y i.e x->y , having weight z \n\n");
    printf("\n\nMake sure you use 1-based indexing for graph nodes.\n\n");
    printf("Once you are done, enter -1 to quit.\n");
    while (1)
    {
        int left;  // left vertex
        int right; // right vertex
        int cap;   // capacity of an edge

        cin >> left ;
        if (left == -1){
            break;
        }
        cin >> right >> cap;
        Capacity[left][right] = cap;
        cout << "Inserted Edge !!\n";
    }
    int source, sink;
    cout << "Enter source vertex : ";
    cin >> source ;
    cout << "Enter sink vertex : ";
    cin >> sink;
    generate_acyclic_network(source);
    for(int j = 1 ; j <= N ; j++){
        Flow[source][i] = Capacity[source][j];
    }
    
}