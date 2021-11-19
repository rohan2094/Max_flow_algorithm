#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 10000 // Assuming there will be atmost 10000 Nodes

// Colors for BFS
//#define WHITE 0
//#define GRAY 1
//#define BLACK 2

int N;      // Number of vertices

int Capacity[MAX_NODES][MAX_NODES]; // 2D matrix to store Capacities of edges \
// Capacity[i][j] will store capacity of edge (i->j)
int flow[MAX_NODES][MAX_NODES]; // flow matrix

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
// delete an element from queue
int dequeue()
{
    struct queue *t;
    if (front == NULL)
    {
        return -1; // the function will return -1 if queue is empty
    }
     // else it will return the value at front

        int temp = front->data;
        t = front;
        front = front->next;
        free(t);
        return temp;

}

int BFS(int rgraph[N][N],int src, int snk,int parent[N])
{
    int ssrc = src;
    int x=0;
    int visited[N];

    for(int i=0;i<N;i++) visited[i]=0;

    enqueue(ssrc);
    visited[ssrc] = 1;
    parent[ssrc]=-1;

    //printf("%d  ",ssrc);
    int u = dequeue();
    //printf()
    /*for(int i=0;i<N;i++)
    {
        printf("%d ",rgraph[u][i]);
    }*/
    while (u != -1)
    {

        for (int j = 0; j < N; j++)
        {
            //printf("%d\n",rgraph[u][j]);
            //printf("%d ",j);
            if (rgraph[u][j] > 0 && visited[j] == 0)
            {
                visited[j] = 1;
                //printf("%d -> %d \n",j,visited[j]);
                enqueue(j);
                //printf("%d  ",j);
                parent[j]=u;
                //printf("%d -> %d\n",u,j);
                if(j==snk)
                {
                    x=1;
                    break;
                }
                //printf("YESSSS00");

            }
            //else printf("NO");
        }
        u = dequeue();
        //printf("%d  ", u);
    }
    if(x==1) return 1;
    else return 0;
}

int MaxFlowCalculate(int so, int si)
{
    int max_flow = 0;
    int rCapacity[N][N];
    int parent[N];
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            rCapacity[i][j]=Capacity[i][j];
        }
    }

    while(BFS(rCapacity,so,si,parent))
    {
        long long int PathFlow = 1e9;
        //printf("YES");
        for(int i= si;i!=so;i=parent[i])
        {
            //printf("%d->%d \n",parent[i],i);
            //printf("IFEO");
            //PathFlow=min(PathFlow, rCapacity[parent[i]][i]);
            if(PathFlow<rCapacity[parent[i]][i])
                PathFlow=PathFlow;
            else PathFlow=rCapacity[parent[i]][i];
            //printf("hj");
        }
        //printf("YHATK");
        for(int i= si;i!=so;i=parent[i])
        {
            rCapacity[parent[i]][i] = rCapacity[parent[i]][i] - PathFlow;
            //printf("%d->%d = %d \n",parent[i],i,rCapacity[parent[i]][i]);
            rCapacity[i][parent[i]] = rCapacity[i][parent[i]] + PathFlow;
        }
        //printf("YHABHI");
        max_flow = max_flow + PathFlow;

    }

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
    int Source,Sink;
    printf("Enter the source vertex: ");
    scanf("%d", &Source);
    printf("Enter the sink vertex: ");
    scanf("%d", &Sink);

    printf("Maximum flow from vertex %d to vertex %d is %d\n", Source, Sink, MaxFlowCalculate(Source,Sink));
    return 0;
}
