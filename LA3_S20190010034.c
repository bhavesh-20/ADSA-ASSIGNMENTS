#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct block{
	int value;
	struct block *next;
};

typedef struct node{
	int value;
	struct node *left,*right;	
}node;

node* createnode(int data)
{
	node* new=(node *)malloc(sizeof(node));
	new->left=NULL;
	new->right=NULL;
	new->value=data;
	return new;
}

int search(node* root,int key)
{
	if(root==NULL)
		return 0;
	else{
		if(key<root->value)
			return search(root->left,key);
		else if(key>root->value)
			return search(root->right,key);
		else
			return 1;
	}
}

node* insert(node *root,int data)
{
	if(root==NULL)
		return createnode(data);
	else{
		if(data<root->value)
			root->left=insert(root->left,data);
		else
			root->right=insert(root->right,data);
	}
	return root;
}

node* findsuccessor(node *root)
{
	if(root->left==NULL)
		return root;
	else
		return findsuccessor(root->left);
	return root;
}

node* delete(node *root,int data)
{
	if(root==NULL)
		return root;
	else{
		if(data<root->value)
			root->left=delete(root->left,data);
		else if(data>root->value)
			root->right=delete(root->right,data);
		else{
			if(root->left==NULL)
			{
				node *t=root->right;
				free(root);
				return t;
			}
			else if(root->right==NULL)
			{
				node *t=root->left;
				free(root);
				return t;
			}
			else{
				node *t=findsuccessor(root->right);
				root->value=t->value;
				root->right=delete(root->right,t->value);
			}
		}
	}
	return root;
}


int* counting_sort(int *a,int n,int x,int base){
	struct block *count[base];
	int i,j;
	i=0;
	while(i<base){
		count[i]=NULL;
		i++;
	}
	for(i=0;i<n;i++)
	{
		int r=(a[i]/x)%base;
		struct block *bucket=(struct block *)malloc(sizeof(struct block));
		bucket->value=a[i];
		bucket->next=NULL;
		if(count[r]==NULL)
			count[r]=bucket;
		else{
			struct block *temp=count[r];
			while(temp->next!=NULL)	
				temp=temp->next;
			temp->next=bucket;
		}
	}
	i=0;
	for(j=0;j<base;j++)
	{
		if(count[j]!=NULL){
			struct block *temp=count[j];
			while(temp!=NULL)
			{
				a[i]=temp->value;
				temp=temp->next;
				i++;
			}
		}
	}
	return a;
}

//running time of radix sort on average is 2.5timeunits when (_sc_CLK_TCK) is used.
//as the base increases the running time decreases and is its smallest when base=n.
//running time of radix sort on average in 0.000007s when (CLOCK_PER_SEC) is used.

int* radix_sort(int *a,int n,int base){
	int m=0;
	for(int i=0;i<n;i++)
		m=m>a[i]?m:a[i];
	int x=1;
	while(m!=0)
	{
		counting_sort(a,n,x,base);
		m/=base;
		x=x*base;
	}
	return a;
}

void print_array(int *a,int n);

void printinorder(node* root);

void main()
{
	//question 1
	//radix sort
	int n,base;
	printf("Enter number of elements in the array:");
	scanf("%d",&n);
	printf("Enter the array elements:");
	int *a=(int *)calloc(n,sizeof(int));
	int i;
	clock_t begin,end;
	double total_time;
	for(i=0;i<n;i++)
		scanf("%d",&a[i]);
	printf("Enter the base using which radix sort needs to be performed:");
	scanf("%d",&base);
	begin=clock();
	a=radix_sort(a,n,base);
	end=clock();
	printf("printing array elements after sorting\n");
	total_time=((double)(end-begin))/CLOCKS_PER_SEC;
	print_array(a,n);
	printf("Time taken for radix sort is %lf\n",total_time);
	free(a);
	//question 2:
	//binary search tree:search,insert,delete operations,print inordertraversal
	node* root=NULL;
	int ch,element;
	while(1){
	printf("=========================\n");
	printf("Binary search tree operations\n");
	printf("1.Insert\n2.Search\n3.Delete\n4.Inorder traversal\n5.exit\n");
	printf("=========================\n");
	printf("Enter your choice:");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:printf("Enter element to be inserted:");
		       scanf("%d",&element);
		       root=insert(root,element);
		       printf("Successfully inserted\n");
		       break;
		case 2:
		       printf("Enter element to be searched:");
		       scanf("%d",&element);
		       int f=search(root,element);
		       if(f==0)
			       printf("Not found\n");
		       else
			       printf("Found\n");
		       break;
		case 3:printf("Enter element to be deleted:");
		       scanf("%d",&element);
		       root=delete(root,element);
		       printf("Successfully deleted\n");
		       break;
		case 4:printinorder(root);printf("\n");break;
		case 5:exit(0);
		default:printf("Invalid choice\n");
	}
	}
}

void printinorder(node *root)
{
	if(root!=NULL)
	{
		printinorder(root->left);
		printf("%d ",root->value);
		printinorder(root->right);
	}
}

void print_array(int *a,int n)
{
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
}