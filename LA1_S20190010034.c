#include<stdio.h>

void insertion_sort(int a[],int n){
    int i,j,k;
    for(i=1;i<n;i++)
    {
        j=i-1;
        k=a[i];
        while(j>=0 && a[j]>k){
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=k;
    }
}

void merge(int a[],int l,int m,int r)
{
    int n1=m-l+1;
    int n2=r-m,i,j,k;
    int a1[n1],a2[n2];
    for(i=0;i<n1;i++)
        a1[i]=a[l+i];
    for(i=0;i<n2;i++)
        a2[i]=a[m+1+i];
    i=j=0;
    k=l;
    while(i<n1 && j<n2)
    {
        if(a1[i]<a2[j])
        {
            a[k]=a1[i];
            i++;
        }
        else
        {
            a[k]=a2[j];
            j++;
        }
        k++;
    }
    while(i<n1)
    {
        a[k]=a1[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        a[k]=a2[j];
        j++;
        k++;
    }
}

void mergesort(int a[],int l,int r)
{
    if(l<r){
        int m=l+r;
        m/=2;
        mergesort(a,l,m);
        mergesort(a,m+1,r);
        merge(a,l,m,r);
    }
}

void swap(int *p,int *q)
{
    int temp=*p;
    *p=*q;
    *q=temp;
}

void heapify(int a[],int n,int i)
{
    int large=i;
    int l=2*i+1;
    int r=2*i+2;
    if(l<n && a[l]>a[large])
        large=l;
    if(r<n && a[r]>a[large])
        large=r;
    if(large!=i)
    {
        swap(&a[i],&a[large]);
        heapify(a,n,large);
    }
}

void heapsort(int a[],int n)
{
    int i;
    for(i=n/2-1;i>=0;i--)
    heapify(a,n,i);
    for(i=n-1;i>=0;i--)
    {
        swap(&a[0],&a[i]);
        heapify(a,i,0);
    }
}

int partition(int a[],int p,int r)
{
    int x=a[r];
    int i=p-1;
    for(int j=p;j<r;j++)
    {
        if(a[j]<x)
        {
            ++i;
            swap(&a[i],&a[j]);
        }
    }
    swap(&a[i+1],&a[r]);
    return i+1;
}

void quicksort(int a[],int p,int r)
{
    if(p<r)
    {
        int q=partition(a,p,r);
        quicksort(a,p,q-1);
        quicksort(a,q+1,r);
    }
}

void print_array(int a[],int n)
{
    printf("Printing the array:");
    for(int i=0;i<n;i++)
        printf("%d ",a[i]);
}

void main()
{
    int n;
    printf("Enter the size of array:");
    scanf("%d",&n);
    int a[n],i;
    printf("Enter array elements:");
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    printf("=================================\n");
    printf("Menu\n");
    printf("1.insertion sort\n");
    printf("2.mergesort\n3.heapsort\n4.quicksort\n");
    printf("=================================\n");
    printf("Enter ur choice:");
    int s;
    scanf("%d",&s);
    switch(s)
    {
        case 1:insertion_sort(a,n); printf("After executing insertion sort\n"); print_array(a,n); break;
        case 2:mergesort(a,0,n-1); printf("After executing merge sort\n"); print_array(a,n); break;
        case 3:heapsort(a,n); printf("After executing heap sort\n"); print_array(a,n); break;
        case 4:quicksort(a,0,n-1); printf("After executing quick sort\n"); print_array(a,n); break;
        default:printf("invalid option\n");
    } 
}