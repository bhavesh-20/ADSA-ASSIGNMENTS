#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 10

typedef struct hash{
    int data;
    struct hash *head;
}hash;


int x,y;

//if isuniversal is 1 then universal hash function is used else lsb is used as hash function.

int hashfunction(int key,int isuniversal){
    if(isuniversal){
        int p=53;
        int m=37;
        return ((x*key+y)%p)%m;
    }
    return key%MAX;
}


void insert(hash a[],int data,int isuniversal){
    int index=hashfunction(data,isuniversal);
    if(a[index].data==-1) a[index].data=data;
    else{
        hash *new=(hash *)malloc(sizeof(hash));
        new->data=data;
        new->head=NULL;
        hash *temp=a[index].head;
        if(temp==NULL) a[index].head=new;
        else{
            while(temp->head!=NULL) temp=temp->head;
            temp->head=new;
        }
    }
}

void display(hash a[],int m){
    for(int i=0;i<m;i++){
        
        if(a[i].data!=-1){
            printf("Key value = %d :",i);
            printf("%d ",a[i].data);
            hash *temp=a[i].head;
            while(temp!=NULL){
                printf("%d ",temp->data);
                temp=temp->head;
            }
            printf("\n");
        }
    }
}

int search(hash a[],int data,int isuniversal){
    int index=hashfunction(data,isuniversal);
    if(a[index].data!=-1){
        if(a[index].data==data) return 1;
        else{
            hash *temp=a[index].head;
            while(temp!=NULL){
                if(temp->data==data) return 1;
                temp=temp->head;
            }
            return 0;
        }
    }
    else return 0;
}

void main(){
    hash a[MAX];
    
    int i;
    
    for(i=0;i<MAX;i++){
        a[i].head=NULL;
        a[i].data=-1;
    }
    srand(time(NULL));
    /*
    for(i=0;i<20;i++) insert(a,i,0);
    display(a,MAX);
    for(i=0;i<30;i++) printf("%d\n",search(a,i,0));
    /*
     * NORMAL HASHING 
     * 
     * The hash funtion used is LSB.
     * 
     *
    */ 
    //Question 1:Hashing and analysis for 100 searches while varying n.
    {
        int n;
        clock_t start,end;
        printf("\n\n\nNORMAL HASHING\n\n\n");
        double total_time;
        for(i=4;i<500;i+=5){
            n=i+1;
            for(int j=0;j<n;j++){
                int ins = rand() % 100007 ;
                insert(a,ins,0);
            }
            start=clock();
            for(int j=0;j<100;j++){
                int r = rand() % 100007 ;
                search(a,r,0);
            }
            end=clock();
            total_time=((double) (end - start)) / CLOCKS_PER_SEC;
            total_time/=100;
            printf("Avg time taken for search when %3d numbers are inserted is:%f\n",n,total_time);
        }
    }
    /*
     * UNIVERSAL HASHING.
     * HASH FUNCTION USED IS ((key*x+y)%p)%m where m=37 and p=53, x and y are randomly generated.
     * 
    */
    //Question 2: Universal hashing. Hashing with hash function ((key*x+y)%p)%m where m=37 and p=53, x and y are randomly generated.
    //AND analysis for 100 searches while varying n.
    
    {
        int m=37;
        hash a[m];
        for(i=0;i<m;i++){
            a[i].head=NULL;
            a[i].data=-1;
        }
        int p=53;
        x=rand()%p;
        while(x==0)
            x=rand()%p;
        y=rand()%p;
        /*
        for(i=0;i<34;i++) insert(a,i,1);
        display(a,m); 
        for(i=0;i<45;i++) printf("%d\n",search(a,i,1));
        */
        printf("\n\n\nUNIVERSAL HASHING \n\n\n");
        int n;
        clock_t start,end;
        double total_time;
        for(i=4;i<500;i+=5){
            n=i+1;
            for(int j=0;j<n;j++){
                int ins = rand() % 100007 ;
                insert(a,ins,1); //notice that in the parameters 1 is given meaning universal hashfunction is used.
            }
            start=clock();
            for(int j=0;j<100;j++){
                int r = rand() % 100007 ;
                search(a,r,1);
            }
            end=clock();
            total_time=((double) (end - start)) / CLOCKS_PER_SEC;
            total_time/=100;
            printf("Avg time taken when %3d numbers are inserted is:%f\n",n,total_time);
        }
    }
}

