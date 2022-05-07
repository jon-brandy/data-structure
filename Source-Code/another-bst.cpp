#include <stdio.h> // NULL, I/O
#include <stdlib.h> // malloc

int NUMOFLEAF;
int NUMOFINTERNALNODE;
int DEPTH;

struct Data
{
	int value;
	struct Data *left, *right, *parent;
}*root; 

struct Data * find (struct Data * curr, int x); // recursion
struct Data * find2 (int x); // iteration
struct Data * newNode(struct Data *curr, int x); // malloc memory to be stored by curr
void push(struct Data *curr, int x); // push data x, to BST
void popAll(struct Data *curr); // popall -> inorder 
void InOrder(struct Data *curr);
void PreOrder(struct Data *curr);
void PostOrder(struct Data *curr);
void inprepost();  // display inorder, preorder, postorder
void menu(); // display menu
void menu1(); 
void menu2();
void menu3();
int isLeaf(struct Data * curr);
int numofLeaf(struct Data *curr);
int numofInternalNode(struct Data *curr);
int numofDegree(struct Data * curr);
int levelofNode(struct Data * curr);
int depthofTree(struct Data * curr);

void menu4()
{
	// breakpoint here for debugging 
	depthofTree(root);
}

int main()
{
	int pilih;
	
	do
	{
		system("cls");
		NUMOFLEAF = 0;
		NUMOFLEAF = numofLeaf(root);
		
		NUMOFINTERNALNODE = 0;
		numofInternalNode(root);
		
		// HEIGHT / DEPTH of a tree is defined as the length of the path from the root node to the deepest node in the tree.
		DEPTH = 0;
		DEPTH = depthofTree(root);

		printf("*num of Nodes : %d\n", NUMOFLEAF + NUMOFINTERNALNODE);
		printf("*num of Leaf : %d\n", NUMOFLEAF);
		printf("*num of InternalNode : %d\n", NUMOFINTERNALNODE);

		// add here
		printf("*Num of Edges : %d\n", (NUMOFLEAF + NUMOFINTERNALNODE - 1)<0?0:(NUMOFLEAF + NUMOFINTERNALNODE - 1));
		printf("*Depth of Tree : %d\n", DEPTH);
		inprepost();
		menu();
		scanf("%d", &pilih);
		fflush(stdin);

		switch(pilih)
		{
			case 1 : menu1(); break;
			case 2 : menu2(); break;			
			case 3 : menu3(); break;
			case 4 : menu4(); break;

		}

	} while(pilih!=0);
	popAll(root);
	return 0;
}
// INI DISURU BKIN
int depthofTree(struct Data * curr)
{
	int left, right, depth;
	if(!curr)
	{
		return 0;
	}
	else
	{
		left = depthofTree(curr -> left);
		right = depthofTree(curr -> right);
		if(depth = (left > right))
		{
			return left;
		}
		else
		{
			return right;
		}
		return depth + 1;
	}
	return 0;
}

//INI DISURU BKIN
int isLeaf(struct Data * curr)
{
	if(curr)
	{
		if(numofDegree(curr) == 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

//INI DISURU BKIN
int numofLeaf(struct Data *curr)
{
	if(curr == NULL)
	{
		return 0;
	}
	else if(isLeaf(curr) != NULL)
	{
		return 1; // leaf
	}
	else
	{
		return numofLeaf(curr -> left) + numofLeaf(curr -> right);
	}
}

//INI DISURU BKIN - TEMPLATE BGT
int numofInternalNode(struct Data *curr)
{
	if(curr)
	{
		numofInternalNode(curr -> left);
		numofInternalNode(curr -> right);
		if(isLeaf(curr) == NULL)
		{
			NUMOFINTERNALNODE++;
		}
	}
}

/*
DELETION ALGORITHM
There are 3 cases which should be considered:
If the key is in a leaf, just delete that node
If the key is in a node which has one child, delete that node and connect its child to its parent
If the key is in a node which has two children, find the right most child of its left sub tree (node P), replace its key with P’s key and remove P recursively. (or alternately you can choose the left most child of its right sub tree)


*/

void pop(struct Data *curr, int x) // curr = merupakan pointer ke Struct Data. menyimpan alamat dari node yang ingin dicari data x dan dihapus
{
	struct Data *temp; 

	// jika node yang ingin dihapus mempunya 2 child / subtree
	// temp merupakan node pengganti utk node yang dihapus 

	if(curr) 
	{
// There are 3 cases which should be considered:
//If the key is in a leaf, just delete that node
//If the key is in a node which has one child, delete that node and connect its child to its parent
//If the key is in a node which has two children, find the right most child of its left sub tree (node P), replace its key with P’s key and remove P recursively. (or alternately you can choose the left most child of its right sub tree)

		if(curr->value == x) // nilai yang dicari ditemukan
		{
			if(curr->left == NULL && curr->right == NULL) // node yang ingin dihapus merupakan leaf
			{
				//If the key is in a leaf, just delete that node

				if(curr == root) // root sekaligus leaf
				{
					root = NULL;
				}
				else if(curr->parent->left == curr) // leaf dan merupakan anak kiri
				{
					curr->parent->left = NULL;
				}
				else if(curr->parent->right == curr) // leaf dan merupakan anak kanan
				{
					curr->parent->right = NULL;
				}
				free(curr);
			}
			else if (curr->left != NULL && curr->right != NULL ) // node yang ingin dihapus mempunya 2 child / subtree
			{
				// If the key is in a node which has two children, 
				// find the right most child of its left sub tree (node P), 
				
				temp = curr->left;
				while(temp->right) // mencari child paling kanan dari subtree kiri
				{
					temp = temp->right;
				}

				// replace its key with P’s key 
				curr->value = temp->value; // node yang dihapus digantikan nilainya dengan node pengganti dari child paling kanan dari subtree kiri
				
				// remove P recursively.

				pop(curr->left, temp->value);
				
				// menghapus node pengganti dan restrukturisasi
				// pop(&(*node)->left, newChild->x); 
			}
			else // node yang ingin dihapus hanya mempunyai 1 child / subtree
			{
				//If the key is in a node which has one child, delete that node and connect its child to its parent

				if(curr->left) // jika node yang dihapus memiliki subtree / child kiri, temp menunjuk child kiri node tsb
				{
					temp = curr->left;
				}
				else // jika node yang dihapus memiliki subtree / child kanan, temp menunjuk child kanan node tsb
				{
					temp = curr->right;
				}

				// sama jika diganti 
				//temp = (curr->left)?curr->left:curr->right;

				// menghubungkan subtree (ki/kn) ke parent dari node yg dihapus
				temp->parent = curr->parent;

				if(curr == root) root = temp; // node yang akan dihapus merupakan root
				else if(curr->parent->left == curr) curr->parent->left = temp; // node yang dihapus merupakan anak kiri, parent dari node yang dihapus diset agar anak kiri yang barunya adalah temp
				else if(curr->parent->right == curr) curr->parent->right = temp; // node yang dihapus merupakan anak kanan, parent dari node yang dihapus diset agar anak kanan yang barunya adalah temp
				free(curr);
			}
			return;
		}
		
		else if(x < curr->value) pop(curr->left, x);// nilai yang dicari < dari curr->value, ada di subtree kiri
		else if(x > curr->value) pop(curr->right, x);// nilai yang dicari > dari curr->value, ada di subtree kanan
	}
}

void menu()
{
	printf("\n BST");
	printf("\n ===\n");
	printf("\n 1. Add New Number");
	printf("\n 2. Remove Number");
	printf("\n 3. Search Number");
	printf("\n 0. Exit and Popall");
	printf("\n Input : ");
}


void menu1()
{
	int x;
	printf("\n\n\n");
	do
	{
		printf("Add: Input Number [0..99]: ");
		scanf("%d", &x);
		fflush(stdin);
	}while(x<0 || x>99);
	push(root, x);
}

void menu2()
{
	int x;
	printf("\n\n\n");
	do
	{
		printf("Remove: Input Number [0..99]: ");
		scanf("%d", &x);
		fflush(stdin);
	}while(x<0 || x>99);
	pop(root, x);
}

// INI YG DISURU BKIN
int numofDegree(struct Data * curr)
{
	int degree = 0;
	if(curr -> left != NULL)
	{
		degree++;
	}
	if(curr -> right != NULL)
	{
		degree++;
	}
	return degree;
}

//INI JG DISURU BKIN
int levelofNode(struct Data * curr)
{
	int level = -1; // dibkin min1 karna levlny mw dimulai dari 0
	while(curr)
	{
		curr = curr -> parent;
		level++;
	}
	return level;
}

void menu3()
{
	struct Data *curr;
	int x;

	printf("\n\n\n");
	do
	{
		printf("Find: Input Number [0..99]: ");
		scanf("%d", &x);
		fflush(stdin);
	}while(x<0 || x>99);

	curr = find(root, x);
	if(curr)
	{
		if(curr == root)
		{
			printf("%d is found. It's root and have no parent\n", curr->value);		
		}
		else
		{
			printf("%d is found.\n", curr->value);			
		}
		if(curr->left) printf("Its left child is %d\n", curr->left->value);
		if(curr->right) printf("Its right child is %d\n", curr->right->value);
		// add here
		printf ("\n");
		
		// level : root = 0, child = parent + 1 
		printf("*Level : %d\n", levelofNode(curr) );
		// degree : num of children that node has
		printf("*Degree : %d\n", numofDegree(curr) );
		// isLeaf : node has no child
		printf("*isLeaf : %d\n", isLeaf(curr) );
	}
	else
	{
		printf("%d is not found.\n", x);
	}
	printf("Press Enter to Continue ... \n");
	getchar();
}


void inprepost()
{
	if(root)
	{
		printf("\n Preorder  : ");
		PreOrder(root);
		printf("\n Inorder   : ");
		InOrder(root);
		printf("\n Postorder : ");
		PostOrder(root);
		printf("\n\n\n");
	}
}


void popAll(struct Data *curr)
{
	if(curr)
	{
		popAll(curr->left);
		popAll(curr->right);
		free(curr);
	}
}

void InOrder(struct Data *curr)
{
	if(curr)
	{
		InOrder(curr->left);
		printf("%d ",curr->value);
		InOrder(curr->right);
	}
}

void PreOrder(struct Data *curr)
{
	if(curr)
	{
		printf("%d ",curr->value);
		PreOrder(curr->left);		
		PreOrder(curr->right);
	}
}

void PostOrder(struct Data *curr)
{
	if(curr)
	{
		PostOrder(curr->left);
		PostOrder(curr->right);
		printf("%d ",curr->value);
	}
}

/*
INSERTION ALGORITHM

Let the new node’s key be X,
- Begin at root
- If X is less than node’s key then insert X into left sub tree, otherwise insert X into right sub tree
- Repeat until we found an empty node to put X (X will always be a new leaf)

*/

//Let the new node’s key be X,
struct Data * newNode(struct Data *curr, int x) 
{
	struct Data *node = (struct Data *)malloc(sizeof(struct Data));
	node->value = x;
	node->left = node->right = NULL;
	node->parent = curr;
	return node;
}

void push(struct Data *curr, int x)
{
//- Begin at root
	if(root == NULL)
	{
		root = newNode(NULL, x);
	}
	else 
	{		
		//DISURU BKIN YG INI JG NI
		//- If X is less than node’s key then insert X into left sub tree, otherwise insert X into right sub tree
		if(x < curr->value)
		{
			if(curr -> left == NULL)
			{
				curr -> left = newNode(curr, x);
			}
			else
			{
				push(curr -> left, x);
			}
		}
		else if(x > curr->value)
		{
			if(curr -> right == NULL)
			{
				curr -> right = newNode(curr, x);
			}
			else
			{
				push(curr -> right, x);
			}
		}
	}
}


struct Data * find (struct Data * curr, int x) // recursion
{ 
	if ( curr == NULL ) return NULL;

	// x is found
	else if ( x == curr->value ) return curr;
	else if ( x  < curr->value ) return find(curr->left, x); // x is located in left sub tree
	else return find(curr->right, x); // x is located in right sub tree
}

struct Data * find2 (int x) // iteration
{
	struct Data *temp;
	temp = root;
	while(temp)
	{
		if( x < temp->value) temp = temp->left;
		else if( x > temp->value) temp = temp->right;
		else break;
	}
	return temp;
}


