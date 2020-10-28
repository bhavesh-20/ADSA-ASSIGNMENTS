/*	Name:C bhavesh kumar               
*	Roll no.:S20190010034
*	Adsa Assignment 3
							*/

//Input considers middlename and last name, c bhavesh kumar is considered as a single name rather than c,bhavesh,kumar being three different strings
//Two strings are differentiated by \n rather than space to provide a chance to enter full name with spaces.
//Input is space sensitive "bhavesh" is different from "bhavesh "
//Please consider these before giving input.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    char name[101];
    int level;
    struct node *parent;  //pointer to the boss
    struct node *list;    //pointer for the list of employees working directly under the employee
    struct node *next;    //pointer for coworkers
    struct node *prev;    //pointer for coworkers
}node;

/*                Queue for level order traversal                                  */ 
typedef struct queue{
    node *employee;
    struct queue *next;
}queue;
//globally declared
queue *head=NULL;
queue *tail=NULL;

queue *newqueue(node *emp){
    queue *temp=(queue *)malloc(sizeof(queue));
    temp->employee=emp;
    temp->next=NULL;
    return temp;
}

void push(node *emp){
    queue *new=newqueue(emp);
    if(head==NULL && tail==NULL){
        head=new;
        tail=new;
    }
    else{
        tail->next=new;
        tail=new;
    }
}

node* pop(){
    if(head==tail){
        node *t=head->employee;
        head=NULL;
        tail=NULL;
        return t;
    }
    else{
        node *t=head->employee;
        head=head->next;
        return t;
    }
}

int isempty(){
    if(head==tail && head==NULL) return 1;
    return 0;
}

void print(char *string);//function defined below.Prints a given string + '\n'

node* newnode(char *name){
    node *temp=(node *)malloc(sizeof(node));
    strcpy(temp->name,name);
    temp->parent=NULL;
    temp->list=NULL;
    temp->next=NULL;
    temp->prev=NULL;
    temp->level=0;
    return temp;
}

node *search(node *root,char *name);

node* searchlist(node *root,char *name);

int insert(node *root,char *name1,char *name2);

void delete(node *root,char *name1,char *name2);

node* lowestcommonboss(node* root,char *name1,char *name2);

void print_employee(node *root);

void main(void){
    print("====================================");
    print("Start of the program:");
    print("Name:C Bhavesh Kumar");
    print("Roll No:S20190010034");
    print("====================================");
    char s[101];
    node *boss;
    printf("Enter the name of CEO or the person at level 1:");
    scanf("%[^\n]s",s);
    boss=newnode(s);
    boss->level=1;
    while(1){
        int ch;
        char name1[101],name2[101];
        print("====================================");
        print("Company hierarchial operations");
        print("1.Add employee");
        print("2.Delete employee");
        print("3.Lowest common boss");
        print("4.Print employees");
        print("5.Exit");
        print("====================================");
        printf("Enter your choice:");
        scanf("%d",&ch);
        node *t;
        switch(ch){
            case 1:
                printf("Enter the name of employee to be added:");
                getchar();
                scanf("%[^\n]s",name1);
                printf("Enter the name of boss of the given employee:");
                getchar();
                scanf("%[^\n]s",name2);
                if(!strcmp(name1,name2)){
                    print("Error:Both names are same");
                    break;
                }
                int success=insert(boss,name1,name2);
                if(success){
                    print("Employee successfully Added!");
                }
                else{
                    print("Could not find the boss with given name,please try again");
                }
                break;
            case 2:
                printf("Enter the name of employee to be deleted:");
                getchar();
                scanf("%[^\n]s",name1);
                getchar();
                printf("Enter the name of employee who now has employees working under him who used to work under deleted employee:");
                scanf("%[^\n]s",name2);
                if(!strcmp(name1,name2)){
                    print("Error:Both names are same");
                    break;
                }
                if(!strcmp(boss->name,name1)){
                    print("Error:Boss cannot be delted");
                }
                delete(boss,name1,name2);
                break;
            case 3:
                printf("Enter the name of employee1:");
                getchar();
                scanf("%[^\n]s",name1);
                getchar();
                printf("Enter the name of employee2:");
                scanf("%[^\n]s",name2);
                t=lowestcommonboss(boss,name1,name2);
                if(t!=NULL){
                    printf("Lowest common boss:%s\n",t->name);
                }
                break;
            case 4:
                print_employee(boss);
                break;
            case 5: exit(0);
            default: print("Invalid Choice");
        }
    }
}

void print(char *string){
    printf("%s\n",string);
}
/* Recursive total search for whole tree datastructure*/ 
node *search(node *root,char *name){
    if(root!=NULL){
        if(!strcmp(root->name,name)) return root;
        node *temp1=search(root->list,name);
        if(temp1!=NULL) return temp1;
        node *temp2=search(root->next,name);
        return temp2;
    }
}

/*efficient search for finding S' in delete*/

node* searchlist(node *root,char *name){
    if(root!=NULL){
        if(!strcmp(root->name,name)){
            return root;
        }
        return searchlist(root->next,name);
    }
    return NULL;
}

/* Insert using linked list implementation and tree implementation*/ 

int insert(node *root,char *name1,char *name2){
    node *insertplace=search(root,name2);
    if(insertplace==NULL) 
        return 0;
    node *insertnode=newnode(name1);
    insertnode->level=insertplace->level+1;
    insertnode->parent=insertplace;
    if(insertplace->list==NULL){
        insertplace->list=insertnode;
    }
    else{
        insertnode->next=insertplace->list;
        insertplace->list->prev=insertnode;
        insertplace->list=insertnode;
    }
    return 1;
}

void delete(node *root,char *name1,char *name2){
    node *tobedeleted=search(root,name1);
    if(tobedeleted==NULL){
        printf("Employee to be deleted not found\n");
        return;
    }
    if(tobedeleted->prev==NULL && tobedeleted->next==NULL){
        printf("The given employee cannot be deleted as there is no one to take his responsibility\n");
        return;
    }
    node *copynode=searchlist(tobedeleted->parent->list,name2);
    if(copynode==NULL){
        printf("Employee who should have employees working under the deleted employee not found\n");
        printf("The two employees may not be on same level or has different bosses\nPlease try again\n");
        return;
    }
    if(copynode->level!=tobedeleted->level){
        printf("Given employees are in different levels\n");
        return;
    }
    //Copying data before delete
    node *temp=tobedeleted->list;
    node *t=copynode->list;
    if(copynode->list==NULL){
        copynode->list=temp;
    }
    else{
        while(t->next!=NULL) t=t->next;
        if(temp!=NULL){
            t->next=temp;
            temp->prev=t;
        }
    }
    while(temp!=NULL){
        temp->parent=copynode;
        temp=temp->next;
    }
    tobedeleted->list=NULL;
    /*Deleting*/
    if(tobedeleted->prev==NULL){
        tobedeleted->parent->list=tobedeleted->next;
        tobedeleted->next->prev=NULL;
        tobedeleted->next=NULL;
        free(tobedeleted);
    }
    else if(tobedeleted->next==NULL){
        tobedeleted->prev->next=NULL;
        tobedeleted->prev=NULL;
        free(tobedeleted);
    }
    else{
        node *t=tobedeleted->prev;
        t->next=tobedeleted->next;
        tobedeleted->next->prev=t;
        free(tobedeleted);
    }
    print("Successfully Deleted");
}

node* lowestcommonboss(node *root,char *name1,char *name2){
    node *t1=search(root,name1);
    node *t2=search(root,name2);
    if(t1==NULL){
        printf("%s not found\n",name1);
        return NULL;
    }
    if(t2==NULL){
        printf("%s not found\n",name2);
        return NULL;
    }
    if(t1->level==1 || t2->level==1){
        printf("One of the given names is boss or ceo\n");
        return NULL;
    }
    while(t1->level!=t2->level){
        if(t1->level>t2->level){
            t1=t1->parent;
        }
        else if(t1->level<t2->level){
            t2=t2->parent;
        }
    }
    while(strcmp(t1->parent->name,t2->parent->name)){
        t1=t1->parent;
        t2=t2->parent;
    }
    return t1->parent;
}
/*Printing employees level wise using queue*/
void print_employee(node *root){
    push(root);
    int level=0;
    while(!isempty()){
        node *t=pop();
        if(level!=t->level){
            level=t->level;
            printf("\nLevel %d: %s",level,t->name);
        }
        else
        printf(", %s",t->name);
        node *temp=t->list;
        while(temp!=NULL){
            push(temp);
            temp=temp->next;
        }
    }
    printf("\n");
}   