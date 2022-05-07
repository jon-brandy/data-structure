//2540120603 - Nicolas Saputra Gunawan
// LA07 - QUIZ 1 DS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 50
#include <time.h>

struct Node
{
    char id[1001];
    char name[1001];
    char type[1001];
    char size[1001];
    char popular[1001];
    int quant;
    Node *next, *prev;
};

Node *head[SIZE], *tail[SIZE];

int total = 0;

Node *createNode(char *name, char *type, char *size, char *popular, int quant, char *id)
{  
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode -> name, name);
    strcpy(newNode -> type , type);
    strcpy(newNode -> size, size);
    strcpy(newNode -> popular, popular);
    newNode -> quant = quant;
    strcpy(newNode -> id, id);
    newNode -> prev = newNode -> next = NULL;
    return newNode;
}

int hash(char *name, int quant)
{
    int keyHash = 0;
    for(int i = 0; i < strlen(name); i++)
    {
        keyHash = keyHash + name[i];
    }
    return (keyHash + quant) % SIZE;
}

void mainMenu()
{
    puts("BlueJack Zoo");
    puts("=============");
    puts("1. Add Animal");
    puts("2. Show Animals");
    puts("3. Remove Animal");
    puts("4. Exit");
    printf(">> ");
}

void view()
{
    system("cls");
    int count = 1;
    for(int i = 0; i < SIZE; i++)
    {
        if(head[i])
        {
            count = 0;
        }
        Node *curr = head[i];
        while(curr)
        {
            int index = hash(curr -> name, curr -> quant);
            printf("index %d: ", index);
            puts("Animal Information");
            puts("=======================================");
            printf("Animal ID\t: %s\n", curr -> id);
            printf("Animal Name\t: %s\n", curr -> name);
            printf("Animal Type\t: %s\n", curr -> type);
            printf("Animal Size\t: %s\n", curr -> size);
            printf("Animal Quantity\t: %d\n", curr -> quant);
            puts("=======================================");
            curr = curr -> next;
        }
    }
    if(count)
    {
        return;
    }
    system("pause");
}

void insert(char *name, char *type, char *size, char *popular, int quant, char *id)
{
    Node *newNode = createNode(name, type, size, popular, quant, id);
    int index = hash(name, quant);
    if(!tail[index])
    {
        head[index] = tail[index] = newNode;
    }
    else
    {
        tail[index] -> next = newNode;
        newNode -> prev = tail[index];
        tail[index] = newNode;
    }
}

int randNum()
{
    int num = rand() % 10 + 1;
    return num;
}

void insertMenu()
{
    system("cls");
    char name[1001];
    char type[1001];
    char size[1001];
    char popular[1001];
    int quant;
    do
    {
        printf("Input New Animal Nam [Min. 6 word] : ");
        scanf("%[^\n]", name);
        getchar();
    } while (strlen(name) < 6);
    do
    {
        printf("Input New Animal Type [land | Water | Amphibious] : ");
        scanf("%s", type);
        getchar();
    } while (strcmp(type, "Land") != 0 && strcmp(type, "Water") != 0 && strcmp(type, "Amphibious") != 0);
    do
    {
        printf("Input new Animal Size [Small | Medium | Big] : ");
        scanf("%s", size);
        getchar();
    } while (strcmp(size, "Small") != 0 && strcmp(size, "Medium") != 0 && strcmp(size, "Big") != 0);
    do
    {
        printf("Input new Animal Popularity [Normal | Popular | Very Popular] : ");
        scanf("%[^\n]", popular);
        getchar();
    } while (strcmp(popular, "Normal") != 0 && strcmp(popular, "Popular") != 0 && strcmp(popular, "Very Popular") != 0);
    do
    {
        printf("Input new Animal Quantity [More than 2] : ");
        scanf("%d", &quant);
        getchar();
    } while (quant <= 2);
    char id[1001];
    if(strcmp(popular, "Very Popular") == 0)
    {
        int num = randNum();
        if(num <= 5)
        {
            int panjang = strlen(name);
            quant = quant + panjang;   
        }
        puts("The animal is Super Popular, We decided to add more to the quantity of animals");
    }
    
    if(strcmp(type, "Land") == 0)
    {
        snprintf(id, sizeof(id), "LA%03d", ++total);
    }
    else if(strcmp(type, "Water") == 0)
    {
        snprintf(id, sizeof(id), "WA%03d", ++total);
    }
    else if(strcmp(type, "Amphibious") == 0)
    {
        snprintf(id, sizeof(id), "AM%03d", ++total);
    }
    insert(name, type, size, popular, quant, id);

    system("pause");
}

Node *searchNode(char *id)
{
    for(int i = 0; i < SIZE; i++)
    {
        if(head[i])
        {
            Node *curr = head[i];
            while(curr)
            {
                if(strcmp(curr -> id, id) == 0)
                {
                    return curr;
                }
                curr = curr -> next;
            }
        }
    }
    return NULL;
}

void removeNode()
{
    system("cls");
    char id[1001];
    printf("Input Animal ID [0 to exit] : ");
    scanf("%s", id);
    getchar();
    if(strcmp(id, "0") == 0)
    {
        return;
    }
    Node *curr = searchNode(id);
    if(curr)
    {
        int index = hash(curr -> name , curr -> quant);
        if(curr == head[index] && head[index] == tail[index])
        {
            free(head[index]);
            head[index] = tail[index] = NULL;
        }
        else if(curr == head[index])
        {
            head[index] = head[index] -> next;
            free(head[index] -> prev);
            head[index] -> prev = NULL;
        }
        else if(curr == tail[index])
        {
            tail[index] = tail[index] -> prev;
            free(tail[index] -> next);
            tail[index] -> next = NULL;
        }
        else
        {
            curr -> prev -> next = curr -> next;
            curr -> next -> prev  = curr -> prev;
            free(curr);
            curr = NULL;
        }
        puts("Animal has been successfully removed");
    }
    else
    {
        return;
    }
    system("pause");
    
}

int main(void)
{
    srand(time(NULL));
    int choice;
    do
    {
        system("cls");
        mainMenu();
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
            case 1:
                insertMenu();
                break;
            case 2:
                view();
                break;
            case 3:
                removeNode();
                break;
        }
    } while (choice != 4);
    

    return 0;
}