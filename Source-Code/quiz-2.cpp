#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 2540120603 - Nicolas Saputra Gunawan - FINAL EXAM LAB

struct Node
{
    char treatMent[1001];
    int treatPrice;
    char treatCategory[1001];
    char avail[1001];
    int height, bf;
    Node *left, *right;
};

Node *root = NULL;

Node *createNode(char *treatMent, int treatPrice, char *treatCategory, char *avail)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode -> treatMent, treatMent);
    newNode -> treatPrice = treatPrice;
    strcpy(newNode -> treatCategory, treatCategory);
    strcpy(newNode -> avail, avail);
    newNode -> height = 1;
    newNode -> left = newNode -> right = NULL;
    return newNode;
}

int getHeight(Node *root)
{
    if(root)
    {
        return root -> height;
    }
    else
    {
        return 0;
    }
}

int setbf(Node *root)
{
    if(root)
    {
        return getHeight(root -> left) - getHeight(root -> right);
    }
    else
    {
        return 0;
    }
}

int max(int a, int b)
{
    if(a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int setHeight(Node *root)
{
    return max(getHeight(root -> left), getHeight(root -> right)) + 1;
}

Node *updateNode(Node *root)
{
    root -> height = setHeight(root);
    root -> bf = setbf(root);

    return root;
}

Node *rightRotate(Node *root)
{
    Node *pivot = root -> left;
    Node *pvc = pivot -> right;

    pivot -> right = root;
    root -> left = pvc;

    root = updateNode(root);
    pivot = updateNode(pivot);

    return pivot;
}

Node *leftRotate(Node *root)
{
    Node *pivot = root -> right;
    Node *pvc = pivot -> left;

    pivot -> left = root;
    root -> right = pvc;

    root = updateNode(root);
    pivot = updateNode(pivot);

    return pivot;
}

Node *rotation(Node *root)
{
    if(root -> bf > 1 && root -> left -> bf >= 0)
    {
        return rightRotate(root);
    }
    else if(root -> bf > 1 && root -> left -> bf < 0)
    {
        root -> left = leftRotate(root -> left);
        return rightRotate(root);
    }
    else if(root -> bf < -1 && root -> right -> bf <= 0)
    {
        return leftRotate(root);
    }
    else if(root -> bf < -1 && root -> right -> bf > 0)
    {
        root -> right = rightRotate(root -> right);
        return leftRotate(root);
    }

    return root;
}

Node *insertNode(Node *root, char *treatMent, int treatPrice, char *treatCategory, char *avail)
{
    Node *newNode = createNode(treatMent, treatPrice, treatCategory, avail);
    if(!root)
    {
        return newNode;
    }
    else if(strcmp(treatMent, root -> treatMent) < 0)
    {
        root -> left = insertNode(root -> left, treatMent, treatPrice,  treatCategory, avail);
    }
    else if(strcmp(treatMent, root -> treatMent) > 0)
    {
        root -> right = insertNode(root -> right, treatMent, treatPrice, treatCategory, avail);
    }

    return rotation(updateNode(root));
}

void insertMenu()
{
    system("cls");
    char treatmentName[1001];
    char treatmentPrice[1001];
    char treatmentCategory[1001];
    char avail[1001];
    int price;
    puts("INSERT NEW TREATMENT");
    int count = 0;
    do
    {
        printf("Input new treatment name: ");
        scanf("%[^\n]", treatmentName);
        getchar();
    } while (strlen(treatmentName) < 5 || strlen(treatmentName) > 20 || strncmp(treatmentName, "Sally ", 6) != 0);
    do
    {
        printf("Input treatment price[50000 - 1000000]: ");
        scanf("%d", &price);
        getchar();
    } while (price < 50000 || price > 1000000);
    snprintf(treatmentPrice, sizeof(treatmentPrice), "RP%d", price);
    do
    {
        printf("Input treatment category [Hair Care | Nail Care | Body Care]: ");
        scanf("%[^\n]", treatmentCategory);
        getchar();
    } while (strcmp(treatmentCategory, "Hair Care") != 0 && strcmp(treatmentCategory, "Nail Care") != 0 && strcmp(treatmentCategory, "Body Care") != 0);
    do
    {
        printf("Input treatment availability for home service [Available | Unavailable]: ");
        scanf("%s", avail);
        getchar();
    } while (strcmp(avail, "Available") != 0 && strcmp(avail, "Unavailable") != 0);
    
    root = insertNode(root, treatmentName, price, treatmentCategory, avail);

    puts("[New Treatment is succesfully inserted]");
    system("pause");
    
}

void in(Node *root)
{
    if(root)
    {
        in(root -> left);
        printf("%s - %s - %d - %s\n", root -> treatMent, root -> treatCategory, root -> treatPrice, root -> avail);
        in(root -> right);
    }
}

void pre(Node *root)
{
    if(root)
    {
        printf("%s - %s - %d - %s\n", root -> treatMent, root -> treatCategory, root -> treatPrice, root -> avail);
        pre(root -> left);
        pre(root -> right);
    }
}

void post(Node *root)
{
    if(root)
    {
        post(root -> left);
        post(root -> right);
        printf("%s - %s - %d - %s\n", root -> treatMent, root -> treatCategory, root -> treatPrice, root -> avail);
    }
}

void viewMenu()
{
    system("cls");
    char order[1001];
    if(root)
    {
        printf("Input view order [pre | in | post]: ");
        scanf("%s", order);
        getchar();
        if(strcmp(order, "pre") == 0)
        {
            pre(root);
        }
        else if(strcmp(order, "in") == 0)
        {
            in(root);
        }
        else if(strcmp(order, "post") == 0)
        {
            post(root);
        }
    }
    else
    {
        puts("no data");
    }
    system("pause");
}

Node *prede(Node *root)
{
    Node *curr = root -> left;
    while(curr && curr -> right)
    {
        curr = curr -> right;
    }
    return curr;
}

Node *deleteNode(Node *root, char *treatMent)
{
    if(!root)
    {
        return NULL;
    }
    else if(strcmp(treatMent, root -> treatMent) < 0)
    {
        root -> left = deleteNode(root -> left, treatMent);
    }
    else if(strcmp(treatMent, root -> treatMent) > 0)
    {
        root -> right = deleteNode(root -> right, treatMent);
    }
    else
    {
        Node *newRoot;
        if(!root -> left || !root -> right)
        {
            if(root -> left)
            {
                newRoot = root -> left;
            }
            else
            {
                newRoot = root -> right;
            }
            root -> left = root -> right = NULL;
            free(root);
            root = NULL;
            return newRoot;
        }
        Node *inOrder = prede(root);
        strcpy(root -> treatMent, inOrder -> treatMent);
        root -> left = deleteNode(root -> left, inOrder -> treatMent);
    }
    return rotation(updateNode(root));
}

Node *searchNode(Node *root, char *treatMent)
{
    if(!root)
    {
        return NULL;
    }
    else if(strcmp(treatMent, root -> treatMent) < 0)
    {
        return searchNode(root -> left, treatMent);
    }
    else if(strcmp(treatMent, root -> treatMent) > 0)
    {
        return searchNode(root -> right, treatMent);
    }
    else
    {
        return root;
    }
}

void deleteMenu()
{
    system("cls");
    char treatmentName[1001];
    if(root)
    {
        in(root);
        puts("DELETE TREATMENT");
        printf("Input treatment name to be deleted: ");
        scanf("%[^\n]", treatmentName);
        getchar();
        Node *curr = searchNode(root, treatmentName);
        if(curr)
        {
            puts("[Delete Successfully]");
            root = deleteNode(root, treatmentName);
        }
        else
        {
            puts("Data not found");
        }
    }
    else
    {
        puts("no data");
    }
    system("pause");
}


int main(void)
{
    int choice;
    do
    {
        system("cls");
        puts("Sally Salon");
        puts("Menu: ");
        puts("1. View Available Treatement");
        puts("2. Insert New Treatment");
        puts("3. Delete Treatment");
        puts("4. Exit");
        printf("[1-4]\n");
        printf(">> ");
        scanf("%d", &choice);
        getchar();
        switch(choice)
        {
            case 1:
                viewMenu();
                break;
            case 2:
                insertMenu();
                break;
            case 3:
                deleteMenu();
                break;
        }
    } while (choice != 4);
    

    return 0;
}