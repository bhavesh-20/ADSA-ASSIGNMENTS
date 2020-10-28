#include<stdio.h>
#include<stdlib.h>

/*                            min heap implementation                                      */

//datatype edge to hold the details of an edge in the graph
struct edge{
    int src;
    int dest;
    int weight;
};

//swaps two edges including their src,dest,weight.
//used for implementing min heap.
void swap(struct edge *edge1,struct edge *edge2){
    struct edge temp=*edge1;
    *edge1=*edge2;
    *edge2=temp;
}

//min heapify used for insertion.if after inserting any property is not maintained this function restores it.
void min_heapify(struct edge *edges,int n,int i){
    int parentnode = (i - 1) / 2; 
        if (edges[i].weight<edges[parentnode].weight) { 
            swap(&edges[i],&edges[parentnode]);
            min_heapify(edges,n,parentnode); 
        } 
}

//converts the heap into min heap
//used when minimum is extracted and deleted to maintain property of min heap
void heapify(struct edge *edges,int n,int i){
    int l = 2*i+1; 
    int r = 2*i+2; 
    int smallest = i; 
    if (l < n && edges[l].weight<edges[smallest].weight) 
        smallest = l; 
    if (r < n && edges[r].weight<edges[smallest].weight) 
        smallest = r; 
    if (smallest != i) 
    { 
        swap(&edges[i], &edges[smallest]); 
        heapify(edges,n,smallest); 
    } 
}

void insert(struct edge *edges,int n,int src,int dest,int weight){
    edges[n].src=src;
    edges[n].dest=dest;
    edges[n].weight=weight;
}

struct edge extract_min(struct edge *edges,int *n){
    if(*n==0){
        printf("No edge exists\n");
        struct edge temp;
        temp.src=-1;
        temp.dest=-1;
        temp.weight=-100;
        return temp;
        //returning fake values.
    }
    else if(*n==1){
        *n=*n-1;
        return edges[0];
    }
    else{
        struct edge temp=edges[0];
        edges[0]=edges[*n-1];
        *n=*n-1;
        heapify(edges,*n,0);
        return temp;
    }
}

/*                          ending min heap implementation                                  */

/*
 Name:C bhavesh kumar
 Roll no.:S20190010034
 Adsa Lab assignment 9
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

//up root tree
struct set
{ 
    int parent; 
    int level; 
}; 
  
//find and union to implement kruskal mst.
int find(struct set s[], int i) 
{ 
    if (s[i].parent!=i) 
        s[i].parent=find(s,s[i].parent);  
    return s[i].parent; 
} 

//U is used instead of u as union is a keyword,hence Union is used.
  
void Union(struct set s[], int x, int y) 
{ 
    int u = find(s,x); 
    int v = find(s,y); 
    if (s[u].level < s[v].level) 
        s[u].parent = v; 
    else if (s[u].level > s[v].level) 
        s[v].parent = u; 
    else
    { 
        s[v].parent = u; 
        s[u].level++; 
    } 
}

void kruskalmst(struct Graph *graph,struct edge *edges,int *n){
    int V=graph->vertices;
    int E=*n;
    int i;
    struct edge mst[V];
    struct set *s=(struct set *)malloc(V*sizeof(struct set));
    for(i=0;i<V;i++){
        s[i].parent=i;
        s[i].level=0;
    }
    i=0;
    while(i<V-1 && *n>0){
        struct edge check_edge=extract_min(edges,n);
        int u=find(s,check_edge.src);
        int v=find(s,check_edge.dest);
        if(u!=v){
            mst[i]=check_edge;
            i++;
            Union(s,u,v);
        }
    }
    printf("\n"); 
    printf("Edges in mst:\n\n");
    printf("Edge        Weight\n");
    for (int j = 0; j< i; j++) 
        printf("%-3d- %3d    %6d\n",mst[j].src,mst[j].dest,mst[j].weight); 
}

int main()
{
	int vertices;
	printf("Enter the number of vertices you want to have in a graph:");
	scanf("%d",&vertices);
	struct Graph* graph=makegraph(vertices);
    int max_edges=vertices*(vertices-1)/2;
    int n=0;
    struct edge* edges=(struct edge *)malloc(max_edges*sizeof(struct edge));
    int ch,u,v,check,weight;
    while(1){
        printf("======================================================\n");
        printf("Graph Operations\n");
        printf("1.Add undirected edge\n2.Print graph\n3.Kruskal MST\n4.Exit\n");
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
                addedge(graph,u,v);
                addedge(graph,v,u);
                insert(edges,n,u,v,weight);
                n++;
                min_heapify(edges,n,n-1);
                break;
            case 2:
                printgraph(graph);
                break;
            case 3:
                kruskalmst(graph,edges,&n);
                break;
            case 4:
                exit(1);
            default:
                printf("Invalid option\n");
        }
    }
	return 0;
}
