#include<stdio.h>
#include<stdlib.h>
#include<limits.h>


/* 
Name:C bhavesh kumar
Roll no.:S20190010034
Assignment 11
*/

/*          Utility function        */

int min(int a,int b,int c){
    return (a>b?(b>c?c:b):(a>c?c:a));
}

/*      end of utility function     */


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

void Bellmann_ford(struct Graph *graph,int source){
    int parent[graph->vertices];//Used for calculating shortest path
    int n=graph->vertices;
    int a[n+1][n];
    for(int i=0;i<n+1;i++){
        for(int j=0;j<n;j++){
            a[i][j]=INT_MAX;
        }
        if(i<n){
            parent[i]=i;
        }
    }

    a[0][source]=0;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n;j++){
            if(a[i][j]!=INT_MAX){
                struct node *temp=graph->adj[j];
                while(temp!=NULL){
                    int src=j;
                    int dest=temp->vertex;
                    int weight=temp->weight;
                    a[i+1][dest]=min(a[i+1][dest],a[i][dest],a[i][src]+weight);
                    if(a[i+1][dest]==a[i][src]+weight){
                        parent[dest]=src;
                    }
                    temp=temp->next;
                }
            }
            a[i+1][j]=min(a[i+1][j],a[i][j],INT_MAX);
        }
    }
    //Checking for negative cycle
    int i=n-1;
    for(int j=0;j<n;j++){
        if(a[i][j]!=INT_MAX){
                struct node *temp=graph->adj[j];
                while(temp!=NULL){
                    int src=j;
                    int dest=temp->vertex;
                    int weight=temp->weight;
                    a[i+1][dest]=min(a[i+1][dest],a[i][dest],a[i][src]+weight);
                    if(a[i][dest]!=a[i+1][dest]){
                        printf("Graph contains negative cycle\n");
                        return;
                    }
                    temp=temp->next;
                }
            }
    }
    printf("\nVertex     Distance from source  shortestPath\n");
    for(i=0;i<n;i++){
        printf("%6d    %21d   ",i,a[n-1][i]);
        if(a[n-1][i]!=INT_MAX){
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
    /*
    for(i=0;i<n;i++){
        printf("%d ",a[n-1][i]);
    }
    printf("\n");
    for(i=0;i<n;i++){
        printf("%d ",parent[i]);
    }
    printf("\n");
    */
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
        printf("1.Add undirected edge\n2.Add directed edge\n3.Print graph\n4.Bellman ford algorithm\n5.Exit\n");
        printf("======================================================\n");
        printf("Enter your choice:");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                printf("Enter the vertices invloved in undirected edge:");
                scanf("%d%d",&u,&v);
                printf("Enter the weight of edge:");
                scanf("%d",&weight);
                if(u>=graph->vertices || v>=graph->vertices){
                    printf("out of range, please try again\n");
                    break;
                }
                addedge(graph,u,v,weight);
                addedge(graph,v,u,weight);
                break;
            case 2:
                printf("Enter source and destination respectively:");
                scanf("%d%d",&u,&v);
                printf("Enter the weight of edge:");
                scanf("%d",&weight);
                if(u>=graph->vertices || v>=graph->vertices){
                    printf("out of range, please try again\n");
                    break;
                }
                addedge(graph,u,v,weight);
                break;
            case 3:
                printgraph(graph);
                break;
            case 4:
                printf("Enter the Source vertex for Bellman-ford algorithm:");
                scanf("%d",&source);
                Bellmann_ford(graph,source);
                break;
            case 5:
                exit(1);
            default:
                printf("Invalid option\n");
        }
    }
	return 0;
}
