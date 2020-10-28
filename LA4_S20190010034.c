#include <stdio.h>
#include <stdlib.h>

#define red 0
#define black 1

typedef struct node
{
    int data;
    struct node *parent, *left, *right;
    int color;
} node;

node *root, *NILL;
node NILL_node;

node *search(int key);
node *new_node(int key);
void inorder(node *t);
void insert(int key);
void insert_fix(node *z);
void left_rotate(node *temp);
void right_rotate(node *temp);
void delete(int data);

void main()
{
    NILL_node.parent = NILL_node.left = NILL_node.right = NULL;
    NILL_node.color = black;
    NILL = &NILL_node;
    root = NILL;
    int key, ch;
    while (1)
    {
        printf("==================================\n");
        printf("Menu - Red Black trees Operations\n");
        printf("1.Insert\n2.Delete\n3.Search\n4.Print\n5.exit\n");
        printf("==================================\n");
        printf("Enter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter the key value to insert:");
            scanf("%d", &key);
            insert(key);
            break;
        case 2:
            printf("Enter the key value to delete:");
            scanf("%d", &key);
            delete(key);
            break;
        case 3:
            printf("Enter the key value to search:");
            scanf("%d", &key);
            node *t = search(key);
            if (t != NILL)
                printf("Found\n");
            else
                printf("Not Found\n");
            break;
        case 4:
            inorder(root);
            printf("\n");
            break;
        case 5:
            exit(1);
        default:
            printf("Invalid choice Try Again\n");
        }
    }
}

node *search(int key)
{
    node *temp = root;
    while (temp != NILL)
    {
        if (temp->data > key)
            temp = temp->left;
        else if (temp->data < key)
            temp = temp->right;
        else
            return temp;
    }
    return NILL;
}

node *new_node(int key)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = key;
    temp->left = NILL;
    temp->right = NILL;
    temp->color = red;
    return temp;
}

void inorder(node *t)
{
    if (t != NILL)
    {
        inorder(t->left);
        printf("%d ", t->data);
        inorder(t->right);
    }
}

void insert(int key)
{
    node *x, *y, *z;
    z = new_node(key);
    x = root;
    y = NILL;
    while (x != NILL)
    {
        y = x;
        if (x->data > key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NILL)
        root = z;
    if (y->data > z->data)
        y->left = z;
    else
        y->right = z;
    insert_fix(z);
}

void insert_fix(node *z)
{
    node *parent = NILL, *grand_parent = NILL, *uncle = NILL;
    while (z != root && z->color != black && z->parent->color == red)
    {
        parent = z->parent;
        grand_parent = z->parent->parent;
        if (z->parent == z->parent->parent->left)
        {
            uncle = grand_parent->right;
            if (uncle != NILL && uncle->color == red)
            {
                uncle->color = black;
                grand_parent->color = red;
                parent->color = black;
                z = grand_parent;
            }
            else
            {
                if (z == parent->right)
                {
                    left_rotate(parent);
                    z = parent;
                    parent = z->parent;
                }
                right_rotate(grand_parent);
                parent->color = black;
                grand_parent->color = red;
                z = parent;
            }
        }
        else
        {
            uncle = grand_parent->left;
            if (uncle != NILL && uncle->color == red)
            {
                uncle->color = black;
                grand_parent->color = red;
                parent->color = black;
                z = grand_parent;
            }
            else
            {
                if (parent->left == z)
                {
                    right_rotate(parent);
                    z = parent;
                    parent = z->parent;
                }
                left_rotate(grand_parent);
                parent->color = black;
                grand_parent->color = red;
                z = parent;
            }
        }
    }
    root->color = black;
}

void left_rotate(node *temp)
{
    node *temp2 = temp->right;
    temp->right = temp2->left;
    if (temp2->left != NILL)
        temp2->left->parent = temp;
    temp2->parent = temp->parent;
    if (temp->parent == NILL)
        root = temp2;
    else if (temp == temp->parent->left)
        temp->parent->left = temp2;
    else
        temp->parent->right = temp2;
    temp2->left = temp;
    temp->parent = temp2;
}

void right_rotate(node *temp)
{
    node *temp2;
    temp2 = temp->left;
    temp->left = temp2->right;
    if (temp2->right != NILL)
        temp2->right->parent = temp;
    temp2->parent = temp->parent;
    if (temp->parent == NILL)
        root = temp2;
    else if (temp == temp->parent->left)
        temp->parent->left = temp2;
    else
        temp->parent->right = temp2;
    temp2->right = temp;
    temp->parent = temp2;
}

void delete(int data)
{
    node *st[100];
    node *ptr, *x_pointer, *y_pointer;
    node *p_pointer, *q_pointer;
    node *right_pointer;

    if (search(data) == NILL)
    {
        printf("No node with given key found\n");
        return;
    }
    int d[100];
    int cnt = 0, difference;
    int color, i;

    ptr = root;

    while (ptr != NILL)
    {
        if ((data - ptr->data) == 0)
            break;
        difference = (data - ptr->data) > 0 ? 1 : 0;
        st[cnt] = ptr;
        d[cnt++] = difference;
        if (difference == 0)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    if (ptr->right == NILL)
    {
        if ((ptr == root) && (ptr->left == NILL))
        {
            free(ptr);
            root = NILL;
        }
        else if (ptr == root)
        {
            root = ptr->left;
            free(ptr);
        }
        else
        {
            if (d[cnt - 1] == 0)
                st[cnt - 1]->left = ptr->left;
            else
                st[cnt - 1]->right = ptr->left;
        }
    }
    else
    {
        x_pointer = ptr->right;
        if (x_pointer->left == NILL)
        {
            x_pointer->left = ptr->left;
            color = x_pointer->color;
            x_pointer->color = ptr->color;
            ptr->color = color;
            if (ptr == root)
            {
                root = x_pointer;
            }
            else
            {
                if (d[cnt - 1] == 0)
                    st[cnt - 1]->left = x_pointer;
                else
                    st[cnt - 1]->right = x_pointer;
            }
            d[cnt] = 1;
            st[cnt++] = x_pointer;
        }
        else
        {
            i = cnt++;
            while (1)
            {
                d[cnt] = 0;
                st[cnt++] = x_pointer;
                y_pointer = x_pointer->left;
                if (y_pointer->left == NILL)
                    break;
                x_pointer = y_pointer;
            }
            d[i] = 1;
            st[i] = y_pointer;
            if (i > 0)
            {
                if (d[i - 1] == 0)
                    st[i - 1]->left = y_pointer;
                else
                    st[i - 1]->right = y_pointer;
            }
            y_pointer->left = ptr->left;
            x_pointer->left = y_pointer->right;
            y_pointer->right = ptr->right;
            if (ptr == root)
            {
                root = y_pointer;
            }
            color = y_pointer->color;
            y_pointer->color = ptr->color;
            ptr->color = color;
        }
    }

    if (cnt < 1)
        return;

    if (ptr->color == black)
    {
        while (1)
        {
            if (d[cnt - 1] == 0)
                p_pointer = st[cnt - 1]->left;
            else
                p_pointer = st[cnt - 1]->right;
            if (p_pointer != NILL && p_pointer->color == red)
            {
                p_pointer->color = black;
                break;
            }
            if (cnt < 2)
                break;
            if (d[cnt - 2] == 0)
            {
                right_pointer = st[cnt - 1]->right;

                if (right_pointer == NILL)
                    break;

                if (right_pointer->color == red)
                {
                    st[cnt - 1]->color = red;
                    right_pointer->color = black;
                    st[cnt - 1]->right = right_pointer->left;
                    right_pointer->left = st[cnt - 1];

                    if (st[cnt - 1] == root)
                    {
                        root = right_pointer;
                    }
                    else
                    {
                        if (d[cnt - 2] == 0)
                            st[cnt - 2]->left = right_pointer;
                        else
                            st[cnt - 2]->right = right_pointer;
                    }
                    d[cnt] = 0;
                    st[cnt] = st[cnt - 1];
                    st[cnt - 1] = right_pointer;
                    cnt++;

                    right_pointer = st[cnt - 1]->right;
                }

                if ((right_pointer->left == NILL || right_pointer->left->color == black) &&
                    (right_pointer->right == NILL || right_pointer->right->color == black))
                {
                    right_pointer->color = red;
                }
                else
                {
                    if (right_pointer->right == NILL || right_pointer->right->color == black)
                    {
                        q_pointer = right_pointer->left;
                        right_pointer->color = red;
                        q_pointer->color = black;
                        right_pointer->left = q_pointer->right;
                        q_pointer->right = right_pointer;
                        right_pointer = st[cnt - 1]->right = q_pointer;
                    }
                    right_pointer->color = st[cnt - 1]->color;
                    st[cnt - 1]->color = black;
                    right_pointer->right->color = black;
                    st[cnt - 1]->right = right_pointer->left;
                    right_pointer->left = st[cnt - 1];
                    if (st[cnt - 1] == root)
                    {
                        root = right_pointer;
                    }
                    else
                    {
                        if (d[cnt - 2] == 0)
                            st[cnt - 2]->left = right_pointer;
                        else
                            st[cnt - 2]->right = right_pointer;
                    }
                    break;
                }
            }
            else
            {
                right_pointer = st[cnt - 1]->left;
                if (right_pointer == NILL)
                    break;
                if (right_pointer->color == red)
                {
                    st[cnt - 1]->color = red;
                    right_pointer->color = black;
                    st[cnt - 1]->left = right_pointer->right;
                    right_pointer->right = st[cnt - 1];

                    if (st[cnt - 1] == root)
                    {
                        root = right_pointer;
                    }
                    else
                    {
                        if (d[cnt - 2] == 0)
                            st[cnt - 2]->left = right_pointer;
                        else
                            st[cnt - 2]->right = right_pointer;
                    }
                    d[cnt] = 1;
                    st[cnt] = st[cnt - 1];
                    st[cnt - 1] = right_pointer;
                    cnt++;

                    right_pointer = st[cnt - 1]->left;
                }
                if ((right_pointer->left == NILL || right_pointer->left->color == black) &&
                    (right_pointer->right == NILL || right_pointer->right->color == black))
                {
                    right_pointer->color = red;
                }
                else
                {
                    if (right_pointer->left == NILL || right_pointer->left->color == black)
                    {
                        q_pointer = right_pointer->right;
                        right_pointer->color = red;
                        q_pointer->color = black;
                        right_pointer->right = q_pointer->left;
                        q_pointer->left = right_pointer;
                        right_pointer = st[cnt - 1]->left = q_pointer;
                    }
                    right_pointer->color = st[cnt - 1]->color;
                    st[cnt - 1]->color = black;
                    right_pointer->left->color = black;
                    st[cnt - 1]->left = right_pointer->right;
                    right_pointer->right = st[cnt - 1];
                    if (st[cnt - 1] == root)
                    {
                        root = right_pointer;
                    }
                    else
                    {
                        if (d[cnt - 2] == 0)
                            st[cnt - 2]->left = right_pointer;
                        else
                            st[cnt - 2]->right = right_pointer;
                    }
                    break;
                }
            }
            --cnt;
        }
    }
}