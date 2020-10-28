#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Queue Template starts */
#define MAX 100

struct queue{
	int data[MAX],rear,front;
};

struct queue* createqueue()
{
	struct queue *q=(struct queue *)malloc(sizeof(struct queue));
	q->rear=q->front=-1;
	return q;
}

void enqueue(struct queue *q,int i)
{
	if(q->rear==MAX-1)
		printf("Queue is overflow\n");
	else{
		if(q->front==-1)
		{
			q->front=q->front+1;
			q->rear=q->rear+1;
		}
		else
			q->rear=q->rear+1;
		q->data[q->rear]=i;
	}
}

int dequeue(struct queue *q)
{
	if(q->rear==q->front && q->front==-1)
	{
		printf("Queue is underflow\n");
		return -10101;
	}
	else{
		int item=q->data[q->front];
		q->front++;
		if(q->front>q->rear)
		{
			//printf("resetting queue\n");
			q->rear=q->front=-1;
		}
		return item;
	}
}

int isempty(struct queue *q)
{
	if(q->rear==q->front && q->front==-1)
		return 1;
	return 0;
}

/* Queue template ends */

/*
 Name:C bhavesh kumar
 Roll no.:S20190010034
 Adsa Lab assignment 8
 */
 

struct node{
	int vertex;
	struct node* next;
};

struct Graph{
	int vertices;
	struct node** adj;
};

struct node* makenode(int n){
	struct node *temp=(struct node *)malloc(sizeof(struct node));
	temp->vertex=n;
	temp->next=NULL;
	return temp;
}

struct Graph* makegraph(int n)
{
	struct Graph* graph=(struct Graph *)malloc(sizeof(struct Graph));
	graph->vertices=n;
	graph->adj=(struct node **)malloc(n*sizeof(struct node *));
	for(int i=0;i<n;i++)
	{
		graph->adj[i]=NULL;
	}
	return graph;
}

void addedge(struct Graph *graph,int src,int dest)
{
	struct node* temp=makenode(dest);
	struct node *t=graph->adj[src];
    if(graph->adj[src]==NULL){
        graph->adj[src]=temp;
    }
    else{
        while(t->next!=NULL){
            if(t->vertex==temp->vertex){
                return;//avoiding duplicacy
            }
            t=t->next;
        }
        if(t->vertex!=temp->vertex)//avoiding duplicacy
            t->next=temp;
    }
}

void addedge_matrix(int n,int a[n][n],int u,int v){
    a[u][v]=1;
}

void printgraph(struct Graph *graph)
{
	printf("No. of vertices=%d\n",graph->vertices);//-> represents directed edge a->b which means there is a possible way from a to b.
	struct node *temp;
	for(int i=0;i<graph->vertices;i++)
	{
		temp=graph->adj[i];
		while(temp!=NULL)
		{
			printf("%d->%d ",i,temp->vertex);
			temp=temp->next;
		}
		printf("\n");
	}
}

void printgraph_matrix(int n,int a[n][n]){
    int i,j;
    printf("No. of vertices=%d\n",n);
    printf("   ");
    for(i=0;i<n;i++){
        printf("%2d ",i);
    }
    printf("\n");
    for(i=0;i<n;i++){
        for(j=0;j<=n;j++){
            if(j==0){
                printf("%2d ",i);
                continue;
            }
            printf("%2d ",a[i][j-1]);
        }
        printf("\n");
    }
}

void BFS(struct Graph *graph,int visited[]){
    struct queue *q=createqueue();
    int v;
    printf("Enter starting vertex to start BFS:");
    scanf("%d",&v);
    enqueue(q,v);
    visited[v]=1;
    printf("BFS Traversal:");
    //printf("%d ",v);
    while(!isempty(q)){
        v=dequeue(q);
        printf("%d ",v);
        struct node *temp=graph->adj[v];
        while(temp!=NULL){
            if(visited[temp->vertex]==0){
                enqueue(q,temp->vertex);
                //printf("%d ",temp->vertex);
                visited[temp->vertex]=1;
            }   
            temp=temp->next;
        }
    }
    printf("\n");
}

void BFS_matrix(int n,int a[n][n],int visited[]){
    struct queue *q=createqueue();
    int v;
    printf("Enter the starting vertex to start BFS:");
    scanf("%d",&v);
    enqueue(q,v);
    visited[v]=1;
    printf("BFS Traversal:");
    while(!isempty(q)){
        v=dequeue(q);
        printf("%d ",v);
        for(int i=0;i<n;i++){
            if(a[v][i]==1 && visited[i]==0){
                enqueue(q,i);
                visited[i]=1;
            }
        }
    }
    printf("\n");
}

int isBipartite(struct Graph *graph){
    int color[graph->vertices];
    memset(color,-1,sizeof(color));
    struct queue *q=createqueue();
    enqueue(q,0);
    int v;
    color[0]=1;
    while(!isempty(q)){
        v=dequeue(q);
        struct node *temp=graph->adj[v];
        while(temp!=NULL){
            if(temp->vertex==v) return 0;
            temp=temp->next;
        }
        temp=graph->adj[v];
        while(temp!=NULL){
            if(color[temp->vertex]==-1){
                enqueue(q,temp->vertex);
                color[temp->vertex]=1-color[v];
            }
            else if(color[temp->vertex]==color[v])
                return 0;
            temp=temp->next;
        }
    }
    return 1;
}

int isBipartite_matrix(int n,int a[n][n]){
    int color[n],v;
    memset(color,-1,sizeof(color));
    struct queue *q=createqueue();
    enqueue(q,0);
    color[0]=1;
    while(!isempty(q)){
        v=dequeue(q);
        if(a[v][v]==1) return 0;
        for(int i=0;i<n;i++){
            if(a[v][i]==1 && color[i]==-1){
                enqueue(q,i);
                color[i]=1-color[v];
            }
            else if(a[v][i]==1 && color[i]==color[v])
                return 0;
        }
    }
    return 1;
}

int main()
{
	int vertices,n;
	printf("Enter the number of vertices you want to have in a graph:");
	scanf("%d",&vertices);
    int visited[vertices];
    for(int i=0;i<vertices;i++){
        visited[i]=0;
    }
	struct Graph* graph=makegraph(vertices);
    int matrix[vertices][vertices];
    int ch,u,v,check;
    memset(matrix,0,sizeof(matrix));
    while(1){
        printf("======================================================\n");
        printf("Graph Operations\n");
        printf("1.Add directed edge\n2.Add undirected edge\n3.Print graph(Adjacency list)\n4.Print graph(Adjacency matrix)\n5.BFS traversal(Adjacency list)\n6.BFS traversal(Adjacency matrix)\n7.isBipartite(Adjacency list)\n8.isBipartite(Adjacency matrix)\n9.Exit\n");
        printf("======================================================\n");
        printf("Enter your choice:");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                printf("Enter the source and destination respectively:");
                scanf("%d%d",&u,&v);
                addedge(graph,u,v);
                addedge_matrix(vertices,matrix,u,v);
                break;
            case 2:
                printf("Enter the vertices invloved in undirected edge:");
                scanf("%d%d",&u,&v);
                addedge(graph,u,v);
                addedge(graph,v,u);
                addedge_matrix(vertices,matrix,u,v);
                addedge_matrix(vertices,matrix,v,u);
                break;
            case 3:
                printgraph(graph);
                break;
            case 4:
                printgraph_matrix(vertices,matrix);
                break;
            case 5:
                memset(visited,0,sizeof(visited));
                BFS(graph,visited);
                break;
            case 6:
                memset(visited,0,sizeof(visited));
                BFS_matrix(vertices,matrix,visited);
                break;
            case 7:
                check=isBipartite(graph);
                if(check){
                    printf("Given graph is Bipartite\n");
                }
                else{
                    printf("Given graph is not Bipartite\n");
                }
                break;
            case 8:
                check=isBipartite_matrix(vertices,matrix);
                if(check){
                    printf("Given graph is Bipartite\n");
                }
                else{
                    printf("Given graph is not Bipartite\n");
                }
                break;
            case 9:
                exit(1);
            default:
                printf("Invalid option\n");
        }
    }
	return 0;
}
