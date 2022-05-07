#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    int value; //store the node's value
    Node *next; // points to the next node in the LL
};

Node *head; //global first node
Node *tail; //global last node

Node *createNode(int value)
{
    Node *newNode = (Node*)malloc(sizeof(Node)); //allocate memory sizeof Node to newNode
    newNode->value = value; // initialize the node's value
    newNode->next = NULL; //node's next is null by default
    return newNode; // return the newly created node
}

//termasuk yang paling gampang = push head , push tail
void pushHead(int value) // nisert node at the beginning of the LL
{
    Node *newNode = createNode(value); //create the new node
    if(!head) // if LL is empty
    {
        head = tail = newNode; // newnode will be the first and the last node in LL
    }
    else // otherwise, A(newNode) -> NULL | B (head) -> C -> D (tail) -> NULL
    {
        newNode -> next = head; // A(newNode) -> B(HEAD) -> C -> D (tail) -> NULL
        head = newNode; // A(head) -> B -> C -> D (tail) -> NULL
    }
}

void pushTail(int value) // Insert a node at the end of the LL
{
    Node *newNode = createNode(value); //Create the newNode
    if(!head) // if LL is empty
    {
        head = tail = newNode; // newnode will be the first and the last node in LL
    }
    else // otherwise, A(newNode) -> NULL | B (head) -> C -> D (tail)
    {
        tail -> next = newNode; // B(HEAD) -> C -> D (tail) -> A(newNode) -> NULL
        tail = newNode; // B(HEAD) -> C -> D  -> A(tail) -> NULL
    }
}

void popHead() // remove the first node of the LL
{
    if(!head) // If the LL is empty, do nothing
    {
        return;
    }
    else if(head == tail) // if there is only one node
    {
        free(head); // free the node, this is the same as free(tail)
        head = tail = NULL; //set head pointer and tail pointer to NULL
    }
    else // if there is more than one node | A(Head) -> B -> C(tail) -> NULL
    {
        Node *newHead = head -> next; // the head's next node will be the new Head A(Head) -> B (newHead) -> C(tail) -> NULL
        head -> next = NULL; // old head points to NULL | A(head) -> NULL, B (newHead) -> C (tail) -> NULL
        free(head); // B(newHead) -> C(tail) -> NULL
        head = newHead; // B(Head) -> C (tail) -> NULL
    }
}

void popTail() // remove the last node of the LL
{
    if(!head) // if LL is empty do nothing
    {
        return;
    }
    else if(head == tail) // if there is only one node
    {
        free(head); // free the heads, this is the same as free(tail)
        head = tail = NULL; // set the head and tail pointer to NULL;
    }
    else // if there is more than one node | A (head) -> B -> C (tail) -> NULL
    {
        Node *newTail = head; // set the new tail points to the head (temporary)
        //we will set the node before tail will become the new tail
        while(newTail -> next != tail) // while the next node is not tail
        {
            newTail = newTail -> next; // move forward
        }
        // A(head) -> B -> C -> D (newTail) -> E (tail) -> NULL
        newTail -> next = NULL; // A (head) -> B -> C -> D (newTail) -> NULL | E (tail) -> NULL
        free(tail); // A (head) -> B -> C -> D (tail) -> NULL 
        tail = newTail;
    }
}

void printLL() // basically a linear search that goes through every node in the LL
{
    Node *curr = head; // set current node to head(first node in LL)
    while(curr) // selama curr ngga NULL
    {
        printf("%d -> ", curr -> value); // print the value of the current node
        curr = curr -> next; //iterate through the whole LL (one step forward)
    }
    puts(" NULL"); // we have reached the end of the LL
}

int main(void)
{
    pushTail(5); // 5 (head, tail)
    pushHead(3); // 3 (head) -> 5 (tail) -> NULL
    pushTail(9); // 3 (head) -> 5 -> 9 (tail) -> NULL
    pushHead(8); // 8 (head) -> 3 - > 5 -> 9 (tail) -> NULL
    pushHead(10); // 10 (head) -> 8 -> 3 -> 5 -> 9 (tail) -> NULL
    popHead(); // 8 (head) -> 3 -> 5 -> 9 (tail) -> NULL
    popTail(); // 8 (head) -> 3 -> 5(tail) -> NULL
    printLL();
    return 0;
}