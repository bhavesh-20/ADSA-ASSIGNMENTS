#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

//average runtime for bogo sort for 100 runtimes is 2363.070068 and its standard deviation is 23485.480469
//average runtime for quicksort for 100 runtimes is 2.890000 and its standard deviation is 0.657951

int generaterandom(int n){
    return rand()%n;
}

void swap(int *p,int *q)
{
    int temp=*p;
    *p=*q;
    *q=temp;
}
void shuffle(int n,int a[])
{
    int i,x,temp;
    for(i=0;i<n;i++)
    {
        x=generaterandom(n);
        temp=a[i];
        a[i]=a[x];
        a[x]=temp;
    }
}

int issorted(int n,int a[])
{
    int i;
    for(i=0;i<n-1;i++)
    if(a[i]>a[i+1])
    return 0;
    return 1;
}

int bogosort(int n,int a[])
{
    srand((unsigned int)(getpid()));
    int cnt=0;
    while(!issorted(n,a))
        shuffle(n,a);
}

int partition(int n,int a[],int l,int r,int p)
{
    swap(&a[p],&a[r]);
    int cnt1=l-1,cnt2=l;
    int i,x=a[r];
    for(i=l;i<r;i++)
    {
        if(a[i]<x)
        {
            cnt1++;
            swap(&a[i],&a[cnt1]);
            cnt2++;
        }
        else
        cnt2++;
    }
    swap(&a[r],&a[cnt1+1]);
    return cnt1+1;
}

int _pivot(int n,int a[],int l,int r)
{
    srand((unsigned int)(getpid()));
    int pivot=rand()%(r-l)+l;
    return partition(n,a,l,r,pivot);
}

void quicksort(int n,int a[],int l,int r)
{
    if(l<r){
    int p=_pivot(n,a,l,r);
    quicksort(n,a,l,p-1);
    quicksort(n,a,p+1,r);
    }
}

void main()
{
    double total_time;
	clock_t start, end,sp,tp;
    int n,choice;
    printf("Enter n:");
    scanf("%d",&n);
    int a[n],i;
    printf("Enter array elements:");
    for(i=0;i<n;i++)
    scanf("%d",&a[i]);
    printf("Select ur choice:\n1.bogo sort\n2.randomized quicksort\n");
    scanf("%d",&choice);
    int c;
    switch(choice)
    {
        case 1:
                start=clock();
                c=bogosort(n,a);          
                end=clock();
                printf("printing array\n");
                for(i=0;i<n;i++)
                    printf("%d ",a[i]);
                printf("\n");
                total_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Time taken to execute bogo sort is %lf\n",total_time);
                break;
        case 2:
                start=clock();
                quicksort(n,a,0,n-1);
                end=clock();
                printf("printing array\n");
                for(i=0;i<n;i++)
                    printf("%d ",a[i]);
                printf("\n");
                total_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                printf("Time taken to execute quicksort is %lf\n",total_time);
                break;
        default:printf("Invalid choice\n");
    }
}

//code used to calculate the avg and standard deviation of 100 trials generated randomly
/*
void msd(){
	srand(time(NULL));
	double total_time;
	clock_t start, end,sp,tp,start1,end1;
	int t=100;
	float f1[100],f2[100];
	for(int q=0;q<t;q++){
	    int n=1+rand()%10;
	    int a[n],i,b[n];
		    for(i=0;i<n;i++){
			    a[i]=1+rand()%100;
			    b[i]=a[i];
		       }
		        int c;
               	 start1=clock();
               	 c=bogosort(n,a);          
               	 end1=clock();
               	 total_time = ((double) (end1 - start1)) / _SC_CLK_TCK;
           	 f1[q]=total_time;
                 start=clock();
                 quicksort(n,b,0,n-1);
                 end=clock();
                 total_time = ((double) (end - start)) / _SC_CLK_TCK;
                 f2[q]=total_time;
	}
	float mean1=0,mean2=0;
	for(int i=0;i<100;i++)
	mean1+=f1[i];
	for(int i=0;i<100;i++)
	mean2+=f2[i];
	mean1/=100;
	mean2/=100;
	float sd1=0,sd2=0;
	for(int i=0;i<100;i++)
	sd1=sd1+(mean1-f1[i])*(mean1-f1[i]);
	sd1=sd1/100;
	sd1=sqrt(sd1);
	for(int i=0;i<100;i++)
	sd2=sd2+(mean2-f2[i])*(mean2-f2[i]);
	sd2/=100;
	sd2=sqrt(sd2);
	printf("mean1=%lf,mean2=%lf,sd1=%lf,sd2=%lf\n",mean1,mean2,sd1,sd2);
}

*/



