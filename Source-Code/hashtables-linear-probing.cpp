#include <stdio.h>
#include <string.h>

//HASH TABLES LINEAR PROBING -> biasany ngga make malloc, cmn make array, tp bisa aja make tergantung dosen
const int MAX_ELEMENT = 5; // amount of strings that can be sorted
const int MAX_LENGTH = 10; // max length of each string
char HASHTABLES[MAX_ELEMENT][MAX_LENGTH]; // 5 strings, each max of 10 characters
//Convert string into idx of an array
// abdul -> 1
int hash(const char *str)
{
    //sebenerny bebas ini algoritmany mw gmn
    //if it's greater than MAX_ELEMENT, it will get modulo
    // harus dimodulo, biar ngga out of index (biar muat di arraynya)
    return (str[0] - 'a') % MAX_ELEMENT; // first character of the string will be the index ('a' -> 0, 'b' -> 1 dst)
}

void linearProbing(int idx, char const *str)
{
    // loop from idx + 1 to idx - 1, to find an empty slot
    for(int i  = (idx + 1) % MAX_ELEMENT; i != idx; i = (i + 1) % MAX_ELEMENT)
    {
        if(!HASHTABLES[i][0]) // if empty
        {
            strcpy(HASHTABLES[i], str); // insert he element
            return; // split looping
        }
    }
    puts("TABLE IS FULL"); // if it has finished the loop and hasn't quit looping
}

void insert(const char *str)
{
    int index = hash(str); // first, convert the string into an index

    if(!HASHTABLES[index][0]) // if the current index is empty
    {
        strcpy(HASHTABLES[index], str); // copy the string to the index
    }
    else // else if the current index is not empty
    {
        linearProbing(index, str); // do linear probing to find the next empty slot
    }
}

void view()
{
    for(int i = 0; i < MAX_ELEMENT; i++) // loop the whole hashtable
    {
        printf("%d -> %s\n", i, HASHTABLES[i]); // print the index and the string stored
    }
}

int main(void)
{
    insert("abdul"); // 0
    insert("cecep"); // 2
    insert("dody"); // 3
    insert("anto"); // 1 -> karena 0 udah diisi, dia ngecek sebelahnya
    insert("aseng"); //4 ->  karena 0 udah diisi cek sebelah terus sampe dpt 4
    insert("bobo"); // TABLE UDAH PENUUH, JADI OUTPUTNY TABLE IS FULL
    view();
    return 0;
}