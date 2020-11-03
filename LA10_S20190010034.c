#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
/*                           Min heap implementation                           */

struct heapnode{
    int v,dist;
};

void swap(struct heapnode *e1,struct heapnode *e2){
    struct heapnode temp=*e1;
    *e1=*e2;
    *e2=temp;
}

void min_heapify(struct heapnode *a,int n,int i,int *pos){
    int parentnode = (i - 1) / 2; 
        if (a[i].dist<a[parentnode].dist) {
            pos[a[i].v]=parentnode;
            pos[a[parentnode].v]=i; 
            swap(&a[i],&a[parentnode]);
            min_heapify(a,n,parentnode,pos); 
        }
}

void heapify(struct heapnode *a,int n,int i,int *pos){
    int l = 2*i+1; 
    int r = 2*i+2; 
    int smallest = i; 
    if (l < n && a[l].dist<a[smallest].dist) 
        smallest = l; 
    if (r < n && a[r].dist<a[smallest].dist) 
        smallest = r; 
    if (smallest != i) 
    {
        pos[a[i].v]=smallest;
        pos[a[smallest].v]=i; 
        swap(&a[i], &a[smallest]); 
        heapify(a,n,smallest,pos); 
    } 
}

void decreasekey(struct heapnode *a,int n,int i,int new_val,int *pos){
    a[i].dist=new_val;
    min_heapify(a,n,i,pos);
}

struct heapnode extract_min(struct heapnode *a,int *n,int *pos){
    if(*n==1){
        *n=*n-1;
        return a[0];
    }
    else{
        struct heapnode temp=a[0];
        a[0]=a[*n-1];
        *n=*n-1;
        heapify(a,*n,0,pos);
        return temp;
    }
}
/*                          Min heap implementation ends                       */
/* 
Name:C bhavesh kumar
Roll no.:S20190010034
Assignment 10
*/

struct node{
	int vertex;
    int weight;
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
    temp->weight=0;
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

void addedge(struct Graph *graph,int src,int dest,int weight)
{
	struct node* temp=makenode(dest);
    temp->weight=weight;
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

void printgraph(struct Graph *graph)
{
	printf("No. of vertices=%d\n",graph->vertices);
	struct node *temp;
	for(int i=0;i<graph->vertices;i++)
	{
		temp=graph->adj[i];
		while(temp!=NULL)
		{
			printf("%d->%d,Weight=%d ",i,temp->vertex,temp->weight);//-> represents directed edge a->b which means there is a possible way from a to b.
			temp=temp->next;
		}
		printf("\n");
	}
}

/*
void printpos(int *pos,int n){
    printf("Printing pos\n");
    for(int i=0;i<n;i++){
        printf("%d ",pos[i]);
    }
    printf("\n");
}

void printheap(struct heapnode *a,int n){
    printf("Printing heap\n");
    for(int i=0;i<n;i++){
        printf("%d(%d) ",a[i].v,a[i].dist);
    }
    printf("\n");
}
*/

//finds shortest path if it exists from source to given vertex.
//k is used for ease of printing,does not take part in algorithm,just for printing purpose.
void shortest_path(int *parent,int i,int k){
    if(parent[i]==i){
        printf("%d->",i);
    }
    else{
        shortest_path(parent,parent[i],k+1);
        if(k)
            printf("%d->",i);
        else
            printf("%d",i);
    }
}

void dijkstra(struct Graph *graph,int source){
    int n=0;
    struct heapnode a[graph->vertices];
    int pos[graph->vertices];  //Used to locate the indices of vertices in heap.
    int visited[graph->vertices];//maintained to keep track of visited vertices.
    int dist[graph->vertices];//Contains distances or path length from source to the vertices,
    int parent[graph->vertices];//Used for calculating shortest path
    for(int i=0;i<graph->vertices;i++){
        a[n].v=i;
        pos[a[n].v]=n;
        a[n].dist=INT_MAX;
        n++;
        min_heapify(a,n,n-1,pos);
        visited[i]=0;
        dist[i]=INT_MAX;
        parent[i]=i;
    }
    a[source].dist=0;
    dist[source]=0;
    min_heapify(a,n,source,pos);
    while(n>0){
        struct heapnode temp=extract_min(a,&n,pos);
        visited[temp.v]=1;
        int u=temp.v;
        pos[u]=graph->vertices;
        struct node *t=graph->adj[temp.v];
        while(t!=NULL){
            int v=t->vertex;
            int weight=t->weight;
            if(visited[v]!=1 && dist[u]!=INT_MAX && weight+dist[u]<dist[v]){
                dist[v]=dist[u]+weight;
                parent[v]=u;
                decreasekey(a,n,pos[v],dist[v],pos);
            }
            t=t->next;
        }
    }
    printf("\nVertex     Distance from source  shortestPath\n");
    for(int i=0;i<graph->vertices;i++){
        printf("%6d    %21d   ",i,dist[i]);
        if(dist[i]!=INT_MAX){
            if(i==source){
                printf("%d\n",source);
            }
            else{
                shortest_path(parent,i,0);
                printf("\n");
            }
        }
        else{
            printf("Cannot reach\n");
        }
    }
}

int main(){
    int vertices;
	printf("Enter the number of vertices you want to have in a graph:");
	scanf("%d",&vertices);
	struct Graph* graph=makegraph(vertices);
    int ch,u,v,weight,source;
    while(1){
        printf("======================================================\n");
        printf("Graph Operations\n");
        printf("1.Add undirected edge\n2.Print graph\n3.Dijkstra algorithm\n4.Exit\n");
        printf("======================================================\n");
        printf("Enter your choice:");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                printf("Enter the vertices invloved in undirected edge:");
                scanf("%d%d",&u,&v);
                printf("Enter the weight of edge:");
                scanf("%d",&weight);
                if(u>graph->vertices || v>graph->vertices){
                    printf("out of range, please try again\n");
                    break;
                }
                addedge(graph,u,v,weight);
                addedge(graph,v,u,weight);
                break;
            case 2:
                printgraph(graph);
                break;
            case 3:
                printf("Enter the Source vertex for dijkstra algorithm:");
                scanf("%d",&source);
                dijkstra(graph,source);
                break;
            case 4:
                exit(1);
            default:
                printf("Invalid option\n");
        }
    }
	return 0;
}