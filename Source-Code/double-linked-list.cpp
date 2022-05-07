#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

struct Node // initialize a node for double LL
{
    int value; // store the current node's value
    Node *next, *prev; // store the current next and previous node
};

Node *head, *tail; // global head(first node in LL), global tail(last node in LL)

Node *createNode(int value)
{
    Node *newNode = (Node*)malloc(sizeof(Node)); // allocate memory sizeof(Node) and cast to Node*
    newNode -> value = value; // (*newNode).value = value
    newNode -> next = newNode -> prev = NULL; // set both pointers to NULL, NULL <- newNode -> NULL
    return newNode; // return the node's pointer
}
//INGAT -> NULL itu hanya satu arah saja, karena dia tidak punya pointer
void pushHead(int value) // insert new element at the beginning of the LL
{
    Node *newNode = createNode(value);
    if(!head) // if there's no head (empty LL)
    {
        head = tail = newNode;
    }
    else // if there's more than one node, NULL <- 5 (head) <-> 8 <-> 10(tail) -> NULL
    {
        head -> prev = newNode; // NULL <- newNode <- 5 (head) <-> 8 <-> 10(tail) -> NULL
        newNode -> next = head; // NULL <- newNode <-> 5 (head) <-> 8 <-> 10(tail) -> NULL
        head = newNode; // the newNode will be the first node in the LL
    }
}


void pushTail(int value) // insert new element at the end of the LL
{
    Node *newNode = createNode(value);
    if(!head) // If there's no head 
    {
        head = tail = newNode;
    }
    else // if there's more than one head
    {
        tail -> next = newNode; // NULL <- 5 (head) <-> 8 <-> 10(tail) -> newNode -> NULL
        newNode -> prev = tail; // NULL <- 5 (head) <-> 8 <-> 10(tail) <-> newNode -> NULL
        tail = newNode; // the new node will be the last node in the LL (tail)
    }
}

void pushMid(int value) // insert new element at the middle of the LL, in order for the LL to be sorted
{
    Node *newNode = createNode(value);
    if(!head) // if there's no head
    {
        head = tail = newNode;
    }
    else if(value < head -> value) // if the value is lower than the first node.
    {
        pushHead(value); // the newNode will be the first node (pushHead)
    }
    else if(value > tail -> value) // if the value is higher than the last node
    {
        pushTail(value); // the newNode will be the end of the LL (pushTail)
    }
    else // insert at the middle of the LL
    {
        //find the element bigger than the node's value
        Node *currentNode = head;
        while(currentNode -> value < value)
        {
            currentNode = currentNode -> next;
        }
        // insert newNode before the currentNode
        //order matters in double LL, solve dlu yg gada labels
        currentNode -> prev -> next = newNode;
        newNode -> prev = currentNode -> prev;
        //atas dulu, baru ini, ordernya dah template
        currentNode -> prev = newNode; 
        newNode -> next = currentNode;
        
    }
}

void popHead() // remove the first element
{
    if(!head) // empty LL
    {
        return;
    }
    else if(head == tail) // only one node in LL
    {
        free(head);
        head = tail = NULL;
    }
    else // there's more than one node in LL
    {
        Node *newHead = head -> next; // NULL <- 7(head) <-> 8 (newHead) <-> ...
        head -> next = newHead -> prev = NULL; //NULL <- 7(head) -> NULL | NULL <- 8(newHead) <-> ....
        free(head); // NULL <- 8(newHead) <-> ....
        head = newHead; // NULL <- 8 (head) <-> ...
    }
}

void popTail() // remove the last element of the LL
{
    if(!head) // if empty
    {
        return;
    }
    if(head == tail) // if there's only one
    {
        free(head);
        head = tail = NULL;
    }
    else // if there's more than one node in the LL
    {
        Node *newTail = tail -> prev; // NULL <- 8 <-> 10(newTail) <-> 12 (tail) -> NULL
        tail -> prev = newTail -> next = NULL; // .. <-> 8 <-> 10(newTail) -> NULL | NULL <- 12 (tail) -> NULL
        free(tail);
        tail = newTail; // ...<- 8 <-> 10(Tail) -> NULL
    }
}

void popMid(int value)
{
    if(!head) // if empty list
    {
        return;
    }
    else if(head -> value == value) // value that need to be deleted is the first node in LL
    {
        popHead();
    }
    else if(tail -> value == value) // value that needs to be deleted is the first node in LL
    {
        popTail();
    }
    else //value that needs to be deleted is in the middle of the LL
    {
        Node *currentNode = head;
        // loop from the first node
        while(currentNode && currentNode -> value != value) // if node is NULL skip. Else compare it's value
        {
            currentNode = currentNode -> next;
        }
        // <- ... 3 <--> 8 <--> 10 (currentNode) <--> 12 <--> ...
        currentNode -> prev -> next = currentNode -> next; // 8 -> 12
        currentNode -> next -> prev = currentNode -> prev; // 8 <- 12
        //tahapan atas terlebih dahulu
        currentNode -> prev = currentNode -> next = NULL; // <- ... 3 <--> 8 <--> 12 <--> ...
        free(currentNode);
        currentNode = NULL; // <- ... 3 <--> 8 <--> 12 <--> ...
    }
}

void printLL() // basically a linear search algorithm
{
    Node *curr = head;
    while(curr != NULL) // atau bisa juga while(curr), linear search from head to the end of the LL
    {
        printf("%d -> ", curr -> value); // print the node's value
        curr = curr -> next; // one step forward
    }
    puts("NULL");

    //for(Node *i = head; i != NULL, i = i -> next)
    //{
    //    printf("%d -> ", i -> value);
    //}
}

int main(void)
{
    //kalau pushmid, dia sambil insert, smbil sorting, jdi ngga nunggu sua dlu baru dia sort.
    pushMid(3);
    pushMid(18);
    pushMid(2);
    pushMid(7);
    printLL();
    popMid(7);
    printLL();
    return 0;
}