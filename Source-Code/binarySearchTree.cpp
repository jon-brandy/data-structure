#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//BST - INSERT, UPDATE, SEARCH
// DELETE -> successor, predesessor, DELETE ALL
// JENIS JENIS BINARY TREE
// Full Binary Tree -> tree yg mempunyai 0 atau 2 nodes
// Complete Binary Tree -> terpenuhi smua, namun boleh ada pengecualian, yakni level terdalam yang hanya pny satu node gpp.
// Perfect Binary Tree -> pny dua anak smua (0 atau 2), tapi smuanya 0 atau semuanya 2
// Balanced Binary Tree -> selisih tinggi yg kanan dan yg kiri maks satu selisihnya, bisa kurang tp gaboleh lebih


struct Node
{
    char name[50];
    int key; // bakal insert, delete, sesuai si key
    Node *left, *right;
};

Node *root;

Node *createNode(char *name, int key)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode -> name, name);
    newNode -> key = key;
    newNode -> left = newNode -> right = NULL;
    return newNode;
}

Node *insertNode(Node *root, char *name, int key)
{
    Node *newNode = createNode(name, key);
    if(root == NULL)
    {
        return newNode; // masukin newNode jadi root
    }
    else if(newNode -> key < root -> key)
    {
        root -> left = insertNode(root -> left, name, key);
    }
    else
    {
        root -> right = insertNode(root -> right, name , key);
    }
    return root;
}

Node *popNode(Node *root, int key)
{
    //base case -> buat berentiin loop
    if(root == NULL) // jika ngga ketemu
    {
        return NULL; // return null
    }
    else if(root -> key == key)// kalau ketemu
    {
        //kondisi jika root merupakan anak terakhir
        if(root -> left == NULL && root -> right == NULL)
        {
            free(root);
            root = NULL;
        }
        // kondisi ketika anaknya di bagian kiri aja, di left aja
        else if(root -> left != NULL && root -> right == NULL)
        {
            Node *temp = root -> left; // tampung anak yg mau kita hapus
            *root = *temp; // value root dan temp sama, jadi kita hapus si temp
            free(temp);
            temp = NULL;
        }
        // kondisi ketika anaknya di bagian kanan aja
        else if(root -> left == NULL && root -> right != NULL)
        {
            Node *temp = root -> right;
            *root = *temp;
            free(temp);
            temp = NULL;
        }
        // kondisi ketika anaknya di bagian right sm left
        else if(root -> left != NULL && root -> right != NULL)
        {
            //predecessor
            // 1. arahin ke kiri
            // 2. loop sampe ke pojok kanan (ke anak yang di pjok kanan)
            // 3. timpa value anak pengganti 
            // 4. Hapus node asli anak pengganti
            Node *temp = root -> left; // langkah 1
            while(temp -> right != NULL) // langkah 2
            {
                temp = temp -> right;
            }
            // langkah ke 3
            root -> key = temp -> key; // root pny value skg make curr value
            strcpy(root -> name, temp -> name); // root pny string, make curr pny string
            // langkah ke 4
            root -> left = popNode(root -> left, temp -> key);
        }
        return root; // jangan lupa return root
    }
    //buat loop
    if(key < root -> key)
    {
        root -> left = popNode(root -> left, key);
    }
    else
    {
        root -> right = popNode(root -> right, key);
    }
}

Node *popAll(Node *root)
{
    if(root != NULL)
    {
        popAll(root -> left);
        popAll(root -> right);
        root -> left = root -> right = NULL;
        free(root);
        root = NULL;
        
    }
    return root; // root yg dah NULL
    
}

void printInOrder(Node *root)
{
    if(root == NULL) // jika gada
    {
        return; // gada yg di print
    }
    else // jika ada nih
    {
        printInOrder(root -> left);
        printf("%s %d\n", root -> name, root -> key);
        printInOrder(root -> right);
    }
}

int main(void)
{
    root = insertNode(root, "holy", 7);
    //root = insertNode(root, "echa", 15);
    root = insertNode(root, "gratia", 4);
    //root = insertNode(root,"estha", 2);
    root = insertNode(root, "tia", 9);
    root = insertNode(root, "tia", 3);
    root = insertNode(root, "holy", 10);
    //root = insertNode(root, "holy", 5);
    printInOrder(root);
    puts("");
    root = popNode(root, 9);
    printInOrder(root);
    puts("");
    printf("ROOT IS NULL");
    /*
    root = popAll(root);
    printPreOrder(root);
    */
    return 0;
}