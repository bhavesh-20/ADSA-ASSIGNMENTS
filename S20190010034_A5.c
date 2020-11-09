#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>


#define print(s) printf("%s",s);
#define for_i(i,j) for(int i=0;i<j;i++)
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
Assignment 5
*/


//Solved using dijkstra
//implementation of dijkstra used from lab assignment 10.


struct node{
	int city;
    int cost;
    char flight[200];
    int arrival,departure;
	struct node* next;
};

struct Graph{
	int vertices;
	struct node** adj;
};

struct node* makenode(int n,int cost,char *flight,int arr,int dep){
	struct node *temp=(struct node *)malloc(sizeof(struct node));
	temp->city=n;
	temp->next=NULL;
    temp->cost=cost;
    temp->arrival=arr;
    temp->departure=dep;
    strcpy(temp->flight,flight);
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

void addedge(struct Graph *graph,int src,int dest,int cost,char *flight,int arr,int dep)
{
	struct node* temp=makenode(dest,cost,flight,arr,dep);
    temp->cost=cost;
	struct node *t=graph->adj[src];
    if(graph->adj[src]==NULL){
        graph->adj[src]=temp;
    }
    else{
        while(t->next!=NULL){
            if(t->city==temp->city && t->arrival==temp->arrival && t->cost==temp->cost && t->departure==temp->departure && !strcmp(t->flight,temp->flight)){
                return;//avoiding duplicacy
            }
            t=t->next;
        }
        if(!(t->city==temp->city && t->arrival==temp->arrival && t->cost==temp->cost && t->departure==temp->departure && !strcmp(t->flight,temp->flight)))//avoiding duplicacy
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
			printf("%d->%d,cost=%d ",i,temp->city,temp->cost);//-> represents directed edge a->b which means there is a possible way from a to b.
			temp=temp->next;
		}
		printf("\n");
	}
}

//utility functions used to check when code went wrong and didnt pass test cases.

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




void cheapesttripplanner(struct Graph *graph,int source,int destination,int departure,int arrival){
    int n=0;
    struct heapnode a[graph->vertices];
    int pos[graph->vertices];  //Used to locate the indices of vertices in heap.
    int visited[graph->vertices];//maintained to keep track of visited vertices.
    int dist[graph->vertices];//Contains distances or path length from source to the vertices,
    int time[graph->vertices];//TIme array to keep track of the arriving time in the cities.
    for(int i=0;i<graph->vertices;i++){
        a[n].v=i;
        pos[a[n].v]=n;
        a[n].dist=INT_MAX;
        n++;
        min_heapify(a,n,n-1,pos);
        visited[i]=0;
        dist[i]=INT_MAX;
        time[i]=2400;
    }
    /*Using dijkstra algorithm using min heap */
    a[source].dist=0;
    dist[source]=0;
    time[source]=departure;
    min_heapify(a,n,source,pos);
    while(n>0){
        struct heapnode temp=extract_min(a,&n,pos);
        visited[temp.v]=1;
        int u=temp.v;
        pos[u]=graph->vertices;
        struct node *t=graph->adj[temp.v];
        while(t!=NULL){
            int v=t->city;
            int cost=t->cost;
            if(visited[v]!=1 && dist[u]!=INT_MAX && cost+dist[u]<dist[v] && time[u]<=t->departure && t->arrival<=arrival){
                dist[v]=dist[u]+cost;
                time[v]=t->arrival+30;
                if(time[v]%100>=60){
                    time[v]+=40;
                }
                time[v]=time[v]%2400;
                int position=pos[v];
                decreasekey(a,n,position,dist[v],pos);
            }
            t=t->next;
        }
    }
    if(dist[destination]!=INT_MAX)
        printf("%d\n",dist[destination]);
    else{
        print("-1\n")
    }
    //printpos(dist,graph->vertices);
}

void main(void){
    FILE *fp;
    char s[200];
    print("Enter the input filename:")
    scanf("%s",s);
    fp=fopen(s,"r");
    if(fp!=NULL){
        int n;
        fscanf(fp,"%d",&n);
        struct Graph *graph=makegraph(n);
        int edges;
        fscanf(fp,"%d",&edges);
        int city1,city2,arr,dep,cost;
        char flight[200];
        for_i(i,edges){
            fscanf(fp,"%d%d%d%d%s%d",&city1,&city2,&dep,&arr,flight,&cost);
            city1--;
            city2--;
            addedge(graph,city1,city2,cost,flight,arr,dep);
        }
        int queries;
        fscanf(fp,"%d",&queries);
        while(queries>0){
            fscanf(fp,"%d%d%d%d",&city1,&city2,&dep,&arr);
            city1--;
            city2--;
            cheapesttripplanner(graph,city1,city2,dep,arr);
            --queries;
        }
    }
    else{
        print("File with name give doesnt exist,please try again\n")
    }
    fclose(fp);
}