#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    struct node *children[26];
    int EOW;
    int occurences;
}node;

node* createnode();
void insert(node *root,char *string);
int search(node *root,char *string);
void printtrie(node* root,char *string,int k);
int isnotprefix(node *root);
node* delete(node* root,char *string,int d);

void main(){
        node *root=createnode();
        char s[1024];
        char s1[1024];
        int ch,c;
        while(1){
            printf("======================================\n");
            printf("Trie Operations\n");
            printf("1.Insert\n2.Search\n3.Delete\n4.print trie\n5.exit\n");
            printf("======================================\n");
            printf("Enter your choice:");
            scanf("%d",&ch);
            switch(ch){
                case 1:
                    printf("===============\n");
                    printf("1.Input through user\n2.Input through a file\n");
                    printf("===============\n");
                    printf("Enter your choice:");
                    scanf("%d",&c);
                    if(c==1){
                        printf("Enter the string to insert:");
                        scanf("%s",s);
                        insert(root,s);
                    }
                    else if(c==2){
                        printf("Enter filename:");
                        scanf("%s",s);
                        FILE *fp=fopen(s,"r");
                        if(fp==NULL) printf("Please Enter valid filename, make sure file exist\n");
                        else{
                            while(fscanf(fp,"%s",s1)!=EOF) insert(root,s1);
                            fclose(fp);
                        }
                    }
                    else printf("Invalid choice please try again\n");
                    break;
                case 2:
                    printf("Enter the string to search:");
                    scanf("%s",s);
                    if(search(root,s)) printf("Found\n");
                    else printf("Not Found\n");
                    break;
                case 3:
                    printf("Enter the string to delete:");
                    scanf("%s",s);
                    if(search(root,s)){
                        root=delete(root,s,0);
                    }
                    else printf("Given string is not there in the trie\n");
                    if(root==NULL) root=createnode();
                    break;
                case 4:
                    printf("Printing the trie in lexicographical order\n");
                    printtrie(root,s1,0);
                    printf("\n");
                    break;
                case 5: exit(1);
                default:printf("Invalid choice Please try again\n");
            }
        }
}

node* createnode(){
    node* temp=(node *)malloc(sizeof(node));
    int i;
    for(i=0;i<26;i++){
        temp->children[i]=NULL;
    }
    temp->EOW=0;
    temp->occurences=0;
    return temp;
}

void insert(node *root,char *string){
    int i,n=strlen(string),ind;
    node *temp=root;
    for(i=0;i<n;i++){
        ind=string[i]-'a';
        if(temp->children[ind]==NULL){
            temp->children[ind]=createnode();
        }
        temp=temp->children[ind];
    }
    temp->EOW=1;
    temp->occurences+=1;
}

int search(node *root,char *string){
    int i,n=strlen(string),ind;
    node* temp=root;
    if(temp==NULL) return 0;
    for(i=0;i<n;i++){
        ind=string[i]-'a';
        if(temp->children[ind]==NULL) return 0;
        temp=temp->children[ind];
    }
    if(temp!=NULL && temp->EOW==1)
        return 1;
    else
        return 0;
}

void printtrie(node* root,char *string,int k){
    int i;
    node* temp=root;
    for(i=0;i<26;i++){
        if(temp->children[i]!=NULL){
            //printf("%c",'a'+i);
            string[k++]='a'+i;
            printtrie(temp->children[i],string,k);
            if(temp->children[i]->EOW==1){
                int j=0;
                string[k]='\0';
                for(j=0;j<temp->children[i]->occurences;j++) printf("%s  ",string);
            }//printf("            number of occurences=%d\n",temp->children[i]->occurences);
            k--;
        }
    }
}

node *delete(node* root,char *string,int d){
        if(d==strlen(string)){
            if(root->occurences>1) root->occurences-=1;
            else{
                root->EOW=0;
                root->occurences=0;
                if(isnotprefix(root)){
                    free(root);
                    root=NULL;
                }
            }
            return root;
        }
        int ind=string[d++]-'a';
        root->children[ind]=delete(root->children[ind],string,d);
        if(isnotprefix(root) && root->EOW==0){
            free(root);
            root=NULL;
        }
        return root;
}

int isnotprefix(node *root){
    int i;
    for(i=0;i<26;i++){
        if(root->children[i]!=NULL) return 0;
    }
    return 1;
}
