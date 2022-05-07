#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
STACK (LAST IN FIRST OUT -> LIFO)
3 -> TOP
5
7
*/

//Kali ini menggunakan string, agar bervariasi, biar nnti semisal ada soal make string, bisa ngerjain
/*
struct Node
{
    char *name; // ini klw mw make strcpy aja
    Node *next; 
};
*/

struct Node
{
    const char *name; // Node's value, biar lebih fleksibel, bisa ada space buat yg laen
    Node *next; // Element's below
};

Node *top; // topmost element

Node *createNode(const char *name)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    // strcpy(newNode -> name, name); // kalau string kek gni, beda sm int
    newNode -> name = name; // kek gni jg bisa, tp di struct nodenya harus const char
    newNode -> next = NULL;
    return newNode;
}

void cls()
{
    for(int i = 0; i < 30; i++)
    {
        puts("");
    }
}

void printStack()
{
    Node *curr = top;
    printf("%s(TOP)\n  |\n  v   \n", curr -> name);
    curr = curr -> next;
    while(curr != NULL)
    {
        printf("%s\n  |\n  v   \n", curr -> name);
        curr = curr -> next;
    }
    printf(" NULL\n\n");
    printf("Press enter to continue...");
    getchar();
    cls();

}

void pushHead(const char *name)
{
    Node *newNode = createNode(name);
    if(!top) //empy stack
    {
        top = newNode;
    }
    else // not empty
    {
        newNode -> next = top;
        top = newNode;
    }

    printf("Insert %s to the stack...\n\n", newNode -> name);
    printStack();
}

void popHead()
{
    if(!top) // empty stack
    {
        return;
    }
    else if(top -> next == NULL) // only one node in stack
    {
        printf("Remove %s from the stack...\n\n", top -> name);
        free(top); // free allocated memory
        top = NULL;
    }
    else
    {
        printf("Remove %s from the stack...\n\n", top -> name);
        Node *newTop = top -> next;
        top -> next = NULL;
        free(top);
        top = newTop;
    }
    printStack();
}

int main(void)
{
    pushHead("Abdul");
    pushHead("Budi");
    pushHead("Cecep");
    popHead();
    pushHead("Dody");
    pushHead("David");
    pushHead("Bima");
    popHead();
    popHead();
    popHead();
    popHead();


    return 0;
}