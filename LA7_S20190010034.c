#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 50

struct stack{
	int top;
	int data[MAX];
};

struct stack* createstack()
{
	struct stack *s=(struct stack *)malloc(sizeof(struct stack));
	s->top=-1;
	return s;
}

void push(struct stack *s,int i)
{
	if(s->top==MAX-1)
		printf("Stack overflow\n");
	else
	{
		s->top=s->top+1;
		s->data[s->top]=i;
	}
}

int pop(struct stack *s)
{
	if(s->top==-1){
		printf("Stack Underflow\n");
		return -10101;
	}
	else{
	int temp=s->data[s->top];
	s->data[s->top]=-1;
	s->top=s->top-1;
	return temp;
	}
}

int isempty(struct stack *s)
{
	if(s->top==-1)
		return 1;
	return 0;
}

int top(struct stack *s)
{
	return s->data[s->top];
}


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
	temp->next=graph->adj[src];
	graph->adj[src]=temp;
}

void printgraph(struct Graph *graph)
{
	printf("No. of vertices=%d\n",graph->vertices);//-> represents directed edge a->b means there is a possible way from a to b.
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

void dfs(struct Graph *graph,int v,int visited[])
{
	struct node *list=graph->adj[v];
	struct node *temp=list;
	printf("%d ",v);
	visited[v]=1;
	int i;
	while(temp!=NULL)
	{
		i=temp->vertex;
		if(visited[i]==0)
		{
            visited[i]=1;
			dfs(graph,i,visited);
		}
		temp=temp->next;
	}
}

void dfs_recursive(struct Graph *graph,int visited[]){
    int x;
    printf("Enter the number of the node to start dfs:");
	scanf("%d",&x);
	printf("DFS of the given graph in the order the vertices are visited: \n");
	dfs(graph,x,visited);
    for(int i=0;i<graph->vertices;i++){
        if(visited[i]==0){
            printf("\n");
            dfs(graph,i,visited);
        }
    }
    printf("\n");
}

void dfs_iterative(struct Graph *graph,int visited[]){
    int x,i;
    printf("Enter the number of the node to start dfs:");
    scanf("%d",&x);
    struct stack *s=createstack();
    push(s,x);
    printf("DFS of the given graph in the order the vertices are visited:\n");
    printf("%d ",top(s));
    struct node *temp;
    int cnt=0;
    while(!isempty(s)){
        i=top(s);
        visited[i]=1;
        temp=graph->adj[i];
        cnt=0;
        while(temp!=NULL){
            if(visited[temp->vertex]==0){
                printf("%d ",temp->vertex);
                push(s,temp->vertex);
                cnt=1;
                break;
            }
            else
                cnt=0;
            temp=temp->next;
        }
        if(cnt==0){
            pop(s);
        }
    }
    for(int j=0;j<graph->vertices;j++){
        if(visited[j]==0){
            printf("\n");
            x=j;
            push(s,x);
            printf("%d ",top(s));
            while(!isempty(s)){
                cnt=0;
                i=top(s);
                visited[i]=1;
                temp=graph->adj[i];
                while(temp!=NULL){
                    if(visited[temp->vertex]==0){
                        printf("%d ",temp->vertex);
                        push(s,temp->vertex);
                        cnt=1;
                        break;
                    }
                    else
                        cnt=0;
                    temp=temp->next;
                }
                if(cnt==0){
                    pop(s);
                }
            }
        }
    }
    printf("\n");
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
    int u=0;
    char s[20];
    printf("Enter directed or undirected:");
    scanf("%s",s);
    if(!strcmp(s,"undirected")) u=1;
	n=vertices;
	printf("Enter no. of edges present:");
	scanf("%d",&n);
	int x,y;
	for(int i=0;i<n;i++)
	{
		printf("Enter source and destination (u,v) of edge respectively (for undirected graph both edges will be added (u,v),(v,u) automatically if undirected is selected.):"); //for undirected graph just enter the edge(u,v)
		scanf("%d%d",&x,&y);
		addedge(graph,x,y);
        if(u==1){
            addedge(graph,y,x);//for undirected graph.
        }
	}
	printf("================================================================\n");
	printf("Printing the graph (a->b represents a directed edge from a to b)\n");
	printgraph(graph);
    printf("================================================================\n");
    printf("Dfs recursively\n");
    dfs_recursive(graph,visited);// If the dfs graph is printed in multiple lines then from the given vertex the 
								//graph is not traversible completely and hence dfs is triggered for the unvisited components of graph separately.
    printf("================================================================\n");
    printf("Dfs iteratively\n");
    for(int i=0;i<graph->vertices;i++) visited[i]=0;
    dfs_iterative(graph,visited);
    printf("================================================================\n");
	return 0;
}
