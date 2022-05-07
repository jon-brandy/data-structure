#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

struct Student
{
    char name[1001];
    int age;
    Student *prev, *next;
};

Student *tableHead[SIZE], *tableTail[SIZE];

int hash(char *name)
{   
    int keyHash = 0;
    for(int i = 0; i < strlen(name); i++)
    {
        keyHash = keyHash + name[i];
    }
    return keyHash % SIZE;
}

Student *createStudent(char *name, int age)
{
    Student *newStudent = (Student*)malloc(sizeof(Student));
    strcpy(newStudent -> name, name);
    newStudent -> age = age;
    newStudent -> prev = newStudent -> next = NULL;
    return newStudent;
}

void insert(char *string, int age)
{
    int index = hash(string);
    Student *newStudent = createStudent(string, age);
    if(tableHead[index] == NULL)
    {
        tableHead[index] = tableTail[index] = newStudent;
    }
    else
    {
        if(newStudent -> age < tableHead[index] -> age)
        {
            newStudent -> next = tableHead[index];
            tableHead[index] -> prev = newStudent;
            tableHead[index] = newStudent;
        }
        else if(newStudent -> age > tableTail[index] -> age)
        {
            newStudent -> prev = tableTail[index];
            tableTail[index] -> next = newStudent;
            tableTail[index] = newStudent;
        }
        else
        {
            Student *curr = tableHead[index];
            while(curr != NULL && curr -> age < newStudent -> age)
            {
                curr = curr -> next;
            }
            curr -> prev -> next = newStudent;
            curr -> prev = newStudent -> prev;
            newStudent -> next = curr;
            curr -> prev = newStudent;
        }
    }
}

void removes(char *name, int age)
{
    int index = hash(name);
    if(tableHead[index] == NULL)
    {
        free(tableHead[index]);
        return;
    }
    else
    {
        if(tableHead[index] -> age == tableTail[index] -> age)
        {
            free(tableHead[index]);
            tableHead[index] = NULL;
        }
        else if(tableHead[index] -> age == age)
        {
            tableHead[index] = tableHead[index] -> next;
            free(tableHead[index] -> prev);
            tableHead[index] -> prev = NULL;
        }
        else if(tableTail[index] -> age == age)
        {
            tableTail[index] = tableTail[index] -> prev;
            free(tableTail[index] -> next);
            tableTail[index] -> next = NULL;
        }
        else
        {
            Student *curr = tableHead[index];
            while(curr != NULL && curr -> age != age)
            {
                curr = curr -> next;
            }
            curr -> prev -> next = curr -> next;
            curr -> next -> prev = curr -> prev;
            free(curr);
            curr = NULL;
        }
    }
}

void print()
{
    for(int i = 0; i < SIZE; i++)
    {
        printf("%d\n", i);
        if(tableHead[i] != NULL)
        {
            //print isinya , karena chaining pasti ada yg nempel kesamping
            Student *curr = tableHead[i];
            while(curr != NULL)
            {
                printf("%s\n", curr -> name);
                curr = curr -> next;
            }
        }
    }
}



int main(void)
{
    insert("Anthony",19);
    insert("Miles",20);
    insert("Testing",21);
    insert("Tina",18);
    insert("Rey",17);
    //removes("Anthony", 19);
    print();

    return 0;
}