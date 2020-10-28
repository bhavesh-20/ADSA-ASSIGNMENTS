#include<stdio.h>

void swap(int* p,int* q){
    int temp=*p;
    *p=*q;
    *q=temp;
}

void question_1(){
    int n,i;
    printf("Enter the size of array:");
    scanf("%d",&n);
    int a[n];
    printf("Enter array elements:");
    for(i=0;i<n;i++)scanf("%d",&a[i]);

    for(i=0;i<n;i++){
        int min_index=i;
        for(int j=i+1;j<n;j++){
            if(a[j]<a[min_index]) min_index=j;
        }
        swap(&a[i],&a[min_index]);
    }
    printf("Array after sorting:");
    for(i=0;i<n;i++) printf("%d ",a[i]);
    printf("\n");
}

//question 2 part 1
/*O(n^2) solution*/

void question_2_1(){
    int n;//numbber of guests visiting
    printf("Enter the number of guests visiting:");
    scanf("%d",&n);
    int entry[n],exit[n];//arrays to record the entry and exit
    int i,j;
    for(i=0;i<n;i++){
        printf("Enter the entry time and exit time of guest %d:",i+1);
        scanf("%d%d",&entry[i],&exit[i]);//scanning the enntry and exit of the guest
    }
    int cnt=0;//count of distinct pairs
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++){
            if((entry[j]<=entry[i] && exit[j]>=entry[i]) || (entry[j]>=entry[i] && entry[j]<=exit[i])){
                cnt++;
                //printf("i=%d %d j=%d %d cnt=%d   %d\n",entry[i],exit[i],entry[j],exit[j],cnt,(entry[j]<=entry[i] && exit[j]>=entry[i]));
            }
        }
    }
    printf("Number of distinct pairs of guests who are at same time same place:%d\n",cnt);
}   

//question 2 part 2
/* O(nlog(n))  solution*/ 

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

void question_2_2(){
    int n;//numbber of guests visiting
    printf("Enter the number of guests visiting:");
    scanf("%d",&n);
    int entry[n],exit[n];//arrays to record the entry and exit
    int i,j;
    for(i=0;i<n;i++){
        printf("Enter the entry time and exit time of guest %d:",i+1);
        scanf("%d%d",&entry[i],&exit[i]);//scanning the enntry and exit of the guest
    }
    mergesort(entry,0,n-1);
    mergesort(exit,0,n-1);
    int cnt=0;//count of distinct pairs
    int guest=1;
    i=1,j=0;
    while(i<n && j<n){
        if(entry[i]<=exit[j]){
            guest++;
            i++;
        }
        else{
            guest--;
            cnt+=guest;
            j++;
        }
    }
    while(j<n){
        guest--;
        cnt+=guest;
        j++;
    }
    printf("Number of distinct pairs of guests who are at same time same place:%d\n",cnt);
}

//question 3 part 1

void question_3_1(){
    int n;
    printf("Enter the size of array:");
    scanf("%d",&n);
    int a[n],i;
    printf("Enter the array elements:");
    for(i=0;i<n;i++) scanf("%d",&a[i]);
    int min=a[0];
    for(i=1;i<n;i++) min=(min<a[i]?min:a[i]);
    printf("Minimum element of the given array is %d\n",min);
}

//question 3 part 2

int findminimum(int a[],int l,int r){
    if(l==r) return a[l];
    if(l<r){
        int mid=(l+r)/2;
        int m1=findminimum(a,l,mid);
        int m2=findminimum(a,mid+1,r);
        return (m1>m2?m2:m1);
    }
}

void question_3_2(){
    int n;
    printf("Enter the size of array:");
    scanf("%d",&n);
    int a[n],i;
    printf("Enter the array elements:");
    for(i=0;i<n;i++) scanf("%d",&a[i]);
    int m=findminimum(a,0,n-1);
    printf("Minimum element of the given array is %d\n",m);
}

/* question 4 part 1 */ 
/* local minimum of a 1d array recursive solution */ 

int recursive_solve(int a[],int l,int r,int n){
    if(l<r){
        int mid=(l+r)/2;
        if(mid-1>=0 && a[mid-1]<a[mid])
        return recursive_solve(a,l,mid-1,n);
        else if(mid+1<n && a[mid+1]<a[mid])
        return recursive_solve(a,mid+1,r,n);
        else return mid;
    }
}

void question_4_1(){
    int n;
    printf("Enter the size of the array:");
    scanf("%d",&n);
    int i,a[n];
    printf("Enter the array elements:");
    for(i=0;i<n;i++) scanf("%d",&a[i]);
    int ans=recursive_solve(a,0,n-1,n);
    printf("Local minimum is at index %d and has value %d\n",ans,a[ans]);
}

/* Question 4 part 2*/ 

/* O(n) implementation of local minima of 2-d array*/ 

int find_min_col_index(int a[],int n){
    int min=0;
    for(int i=1;i<n;i++){
        min=(a[min]<a[i]?min:i);
    }
    return min;
}

int find_min_row_index(int n,int a[][n],int c,int row){
    int min=row;
    if(row-1>=0)
     min=(a[min][c]<a[row-1][c]?min:(row-1));
    if(row+1<n)
     min=(a[min][c]<a[row+1][c]?min:(row+1));
    return min;
}


int local_min_grid(int n,int a[][n],int l,int r){
    if(l<=r){
        int min_row,min_column;
        int mid=(l+r)/2;
        min_column=find_min_col_index(a[mid],n);
        min_row=find_min_row_index(n,a,min_column,mid);
        if(min_row==mid) return a[min_row][min_column];
        else if(min_row<mid) return local_min_grid(n,a,l,mid-1);
        else if(min_row>mid) return local_min_grid(n,a,mid+1,r);
    }
}

void question_4_2(){
    int n;
    printf("Enter the number of rows or columns in a n*n grid:");
    scanf("%d",&n);
    int i,j,a[n][n];
    for(i=0;i<n;i++){
        printf("Enter row %d elements:",i+1);
        for(j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    int ans=local_min_grid(n,a,0,n-1);
    printf("The local minima in the given array is %d\n",ans);
}

void main(){
    printf("Question 1: Selection sort implementation in c\n");
    question_1();
    printf("Question 2: O(n*n) implementation of the second question\n");
    question_2_1();
    printf("Question 2: O(nlogn) implementation of the second question\n");
    question_2_2();
    printf("Question 3: linear time implementation of algorithm to find minimum of array elements:\n");
    question_3_1();
    printf("Question 3: Recursive divide and conquer approach implementation to find minimum of array elements\n");
    question_3_2();
    printf("Question 4: O(logn) solution for solving local minimum in a 1-d array\n");
    question_4_1();
    printf("Question 4: O(n) implementation for solving local minimum of a 2-d array\n");
    question_4_2();
}