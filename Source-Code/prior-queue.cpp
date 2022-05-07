#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int number;
    char prior[1001];
    int price;
    Node *next, *prev;
};

int totalQueue = 0;
int totalIncome = 0;

Node *head, *tail;

Node *createNode(int number, char *prior, int price)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode -> number = number;
    strcpy(newNode -> prior, prior);
    newNode -> price = price;
    newNode -> next = newNode -> prev = NULL;
    return newNode;
}

void insert(int number, char *prior, int price)
{
    Node *newNode = createNode(number, prior, price);
    if(!head)
    {
        head = tail = newNode;
    }
    else if(strcmp(prior, "vip") == 0)
    {
        newNode ->  next = head;
        head -> prev = newNode;
        head = newNode;
    }
    else if(strcmp(prior, "regular") == 0)
    {
        tail -> next = newNode;
        newNode -> prev = tail;
        tail = newNode;
    }
}

void insertMenu()
{
    system("cls");
    int plateNumber;
    int typePrior;
    char prior[1001];
    int price = 0;
    do
    {
        printf("Insert Plate [Number between 3000-6999] : ");
        scanf("%d", &plateNumber);
        getchar();
    } while (plateNumber < 3000 || plateNumber > 6999);
    do
    {
        printf("Insert Type [0: regular, 1: vip] : ");
        scanf("%d", &typePrior);
        getchar();
    } while (typePrior != 0 && typePrior != 1);
    if(typePrior == 1)
    {
        price += 15000;
        strcpy(prior, "vip");
    }
    else if(typePrior == 0)
    {
        price += 10000;
        strcpy(prior, "regular");
    }
    insert(plateNumber, prior, price);
    totalQueue++;
    system("pause");
}

void remove()
{
    if(!head)
    {
        return;
    }
    else if(head == tail)
    {
        free(head);
        head = tail = NULL;
    }
    else
    {
        Node *newNode = head -> next;
        head -> next = newNode -> prev = NULL;
        free(head);
        head = newNode;
    }
}

void removeMenu()
{
    Node *curr = head;
    if(curr)
    {
        remove();
        printf("%s motorcyle is washed. %d is paid\n", curr -> number, curr -> price);
        totalIncome += curr -> price;
        totalQueue--;
    }

    /*
    Node *curr = head;
    remove();
    printf("%s motorcyle is washed. %d is paid\n", curr -> number, curr -> price);
    totalIncome += curr -> price;
    totalQueue--;
    */
}

Node *searchNode(int number)
{
    if(!head)
    {
        return NULL;
    }
    else if(head -> number == number)
    {
        return head;
    }
    else if(tail -> number == number)
    {
        return tail;
    }
    else
    {
        Node *curr = head;
        while(curr && curr -> number != number)
        {
            curr = curr -> next;
        }
        return curr;
    }
}

void cancelWash()
{
    int plateNumber;
    do
    {
        system("cls");
        printf("Insert Plate [Number between 3000 - 6999] : ");
        scanf("%d", &plateNumber);
        getchar();
    } while (plateNumber < 3000 || plateNumber > 6999);
    
    Node *curr = searchNode(plateNumber);
    if(curr)
    {
        if(curr == head && head == tail)
        {
            free(head);
            head = tail = NULL;
        }
        else if(curr == head)
        {
            Node *newNode = head -> next;
            head -> next = newNode -> prev = NULL;
            free(head);
            head = newNode;
        }
        else if(curr == tail)
        {
            Node *newNode = tail -> prev;
            newNode -> next = tail -> prev = NULL;
            free(tail);
            tail = newNode;
        }
        else 
        {
            while(curr && curr -> number != plateNumber)
            {
                curr = curr -> next;
            }
            curr -> next -> prev = curr -> prev;
            curr -> prev -> next = curr -> next;
            curr -> prev = curr -> next = NULL;
            free(curr);
            curr = NULL;   
        }
        printf("%s motorcyle %d is canceled", curr -> prior, plateNumber);
        totalQueue--;
        if(strcmp(curr -> prior, "vip") == 0)
        {
            curr -> price -= 15000;
        }
        else if(strcmp(curr -> prior , "regular") == 0)
        {
            curr -> price -= 10000;
        }
    }
    else
    {
        return;
    }
}


void view()
{
    system("cls");
    if(!head)
    {
        puts("No Motorcycle");
    }
    else
    {
        Node *curr = head;
        int i = 1;
        while(curr)
        {
            printf("%d. %s : %d\n", i, curr -> prior, curr -> number);
            curr = curr -> next;
            i++;
        }
    }
}

int main(void)
{
    int choice;
    do
    {
        system("cls");
        view();
        printf("Total Queue\t : %d\n", totalQueue);
        printf("Total Income\t : %d\n", totalIncome);
        puts("Washing Queue");
        puts("=============");
        puts("1. Add reguler / vip motorcycle to washing queue");
        puts("2. Wash motorcycle from washing queue (priority : VIP first)");
        puts("3. Cancel specific motorcycle from washing queue");
        puts("0. Wash All, Exit");
        printf("Pilih\t: ");
        scanf("%d", &choice);
        getchar();
        switch(choice)
        {
            case 1:
                insertMenu();
                break;
            case 2:
                removeMenu();
                break;
            case 3:
                cancelWash();
                break;
        }

    } while (choice != 0);
    

    return 0;
}