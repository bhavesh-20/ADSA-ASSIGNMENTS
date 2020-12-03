#include<stdio.h>
#include<limits.h>

/*
Name:C Bhavesh Kumar
Roll number:S20190010034
Assignment 6
*/

/*
Input format for question1

n,number of coin denomination
next n lines, n coin denominations,in increasing order.
m,number of test case,
next m lines,a number x which is supposed to be paid in give denomination with minimum coins.

example input:

4
1
4
5
9
2
7
10

here 4 is number of coin denominations and 1,4,5,9 are denominations
and 2 is number of test cases which contain 7,10 as the queries.
*/

/*
Output format:
for each test case a line is printed which contains the coins that are used to pay given query amount
for above input, output printed is
1 1 5
1 9

where 1+1+5=7
and 1+9=10 the query amounts with minimum coins paid.
*/

//function to fill dp array,where dp[i] contains minimum coins to pay 'i' currency with given denomination.
int min_coins(int dp[],int a[],int n,int x){
    dp[0]=0;//0 can be made with 0 coins.
    int i=0,j;
    for(i=1;i<=x;i++){
        dp[i]=INT_MAX;//initializing with maximum number possible.
    }
    for(i=1;i<=x;i++){
        for(j=0;j<n;j++){
            if(a[j]<=i){
                int y=dp[i-a[j]];
                if(y!=INT_MAX && y+1<dp[i]){
                    dp[i]=y+1;
                }
            }
        }
    }
    return dp[x];
}

//function to find the denomination of the coins used to pay 'i' currency with dp[i] coins.
void find_denomination(int dp[],int a[],int n,int x){
    int count=dp[x];
    int denomination_array[count];
    int k=0;//used for maintaining denomination array

    while(x>0){
        for(int i=0;i<n;i++){
            if(x-a[i]>=0 && dp[x-a[i]]+1==dp[x]){ 
                denomination_array[k++]=a[i];
                x-=a[i];
                break;
            }
        }
    }
    for(int i=0;i<count;i++){
        printf("%d ",denomination_array[i]);
    }
    printf("\n");
}

//Function which answers question1
void question_1(){
    char s[100];
    printf("Question 1:Coin Denominations\nEnter the input file name:");
    scanf("%s",s);
    FILE *fp=fopen(s,"r");
    if(fp!=NULL){
        int n,i;
        fscanf(fp,"%d",&n);//scanning into variables
        int a[n];//to store types of coins.
        for(i=0;i<n;i++){
            fscanf(fp,"%d",&a[i]);//scanning into variables
        }
        int t;
        fscanf(fp,"%d",&t);//scanning into variables
        while(t--){
            int x;
            fscanf(fp,"%d",&x);//scanning into variables
            int dp[x+1];
            int ans=min_coins(dp,a,n,x);//solution
            if(ans==INT_MAX){
                printf("-1\n");
            }
            else{
                //printf("minimum number of coins=%d\n",ans);
                //printf("Denomination:");
                find_denomination(dp,a,n,x);//finding the denominations for the solution found out.
            }
        }
        fclose(fp);
    }
    else{
        printf("File didnt open,please check whether file exists or if it is in present working directory\n");
    }
}

//utility function for finding square of a number.
int power_2(int x){
    return x*x;
}


//utility function to find the hotels stopped by.
void hotel_path(int parent[],int i){
    if(parent[i]==-1){
        printf("%d ",i+1);
        return;
    } 
    hotel_path(parent,parent[i]);
    printf("%d ",i+1);
}

void planner(int a[],int n){
    int penalty[n],parent[n];//penalty is dp array,parent is used for printing the visited hotels.
    for(int i=0;i<n;i++){
        penalty[i]=power_2((20-a[i]));//initialising the array with a direct path from 0 to the hotels.
        parent[i]=-1;//all hotels are reached from 0 which for avoiding confusion has been taken -1.
    }
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(penalty[j]>penalty[i]+power_2((20-(a[j]-a[i])))){
                penalty[j]=penalty[i]+power_2((20-(a[j]-a[i])));//updating dp array with minimum penalty, when possible
                parent[j]=i;//updating that i is reached from j.
            }
        }
    }
    hotel_path(parent,n-1);//finding hotels passed by.
    printf("\n%d\n",penalty[n-1]);//total penalty to reach nth hotel,the destination.
}

/*
input format:
integer n,which is number of hotels present in our route
next n lines contains integers which are distances from source to hotel i,if line number is i.The distances are increasing in order.

Example input:
4
10
20
40
60

*/

/*
Output format:
two lines are printed.
first line contains the list of hotels visited.
second line contains total penalty

for above given example input output printed is

2 3 4
0

where 2,3,4 are the hotels visited 
and 0 is the total penalty
*/



//function which answer question2
void question_2(){
    char s[100];//file name variable
    printf("Question 2:Travel and stay planner\nEnter the input file name:");
    scanf("%s",s);
    FILE *fp=fopen(s,"r");
    if(fp!=NULL){
        int n;
        fscanf(fp,"%d",&n);//scanning into variables
        int a[n];
        for(int i=0;i<n;i++)
            fscanf(fp,"%d",&a[i]);//scanning into variables
        planner(a,n);//solution to question 2
        fclose(fp);
    }
    else{
        printf("File didnt open,please check whether file exists or if it is in present working directory\n");
    }
}

int main(void){
    //Problem 1
    question_1();
    //Problem 2
    question_2();
    return 0;
}


