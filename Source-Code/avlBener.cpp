#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
	int height, value, bf;
	char string[1001];
	Node *left, *right;
};

Node *rootSS;

Node *createNode(int value, char *string)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode -> value = value;
	strcpy(newNode -> string, string);
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

int setBalanceFactor(Node *root)
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
	return (a > b) ? a : b;
}

int setHeight(Node *root)
{
	return max(getHeight(root -> left), getHeight(root -> right)) + 1;
}

Node *updateNode(Node *root)
{
	root -> height = setHeight(root);
	root -> bf = setBalanceFactor(root);
	return root;
}

Node *rightRotate(Node *root)
{
	Node *pivot = root -> left;
	Node *pivotChild = pivot -> right;

	pivot -> right = root;
	root -> left = pivotChild;

	root = updateNode(root);
	pivot = updateNode(pivot);

	return pivot;
}

Node *leftRotate(Node *root)
{
	Node *pivot = root -> right;
	Node *pivotChild = pivot -> left;

	pivot -> left = root;
	root -> right = pivotChild;

	root = updateNode(root);
	pivot = updateNode(pivot);
	
	printf("PIVOT = %d, ROOT = %d\n", pivot->value, root->value);
	
	return pivot;
}

Node *rotation(Node *root)
{
	
	if (!root) return NULL;
	
	if(root -> bf > 1 && root -> left -> bf >= 0)
	{
		printf("LL\n");
		return rightRotate(root);
	}
	else if(root -> bf > 1 && root -> left -> bf < 0)
	{
		printf("LR");
		root -> left = leftRotate(root->left);
		return rightRotate(root);
	}
	else if(root -> bf < -1 && root -> right -> bf <= 0)
	{
		printf("RR");
		return leftRotate(root);
	}
	else if(root -> bf < -1 && root -> right -> bf > 0)
	{
		printf("RL");
		root -> right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}

Node *insertNode(Node *root, int value, char *string)
{
	if(!root)
	{
		printf("Proses input %s %d, -> data masuk\n", string, value);
		return createNode(value, string);
	}
	else if(value > root -> value)
	{
		printf("Proses input %s %d, -> data ke kanan\n", string, value);
		root -> right = insertNode(root -> right, value, string);
	}
	else if(value < root -> value)
	{
		printf("Proses input %s %d, -> data ke kiri\n", string, value);
		root -> left = insertNode(root -> left, value, string);
	}
	
	printf("Proses rebalancing %s %d -> ", root->string, root->value);
	
	root = updateNode(root);
	
	printf("Height = %d, BF = %d, height left = %d, height right = %d\n", root->height, root->bf, getHeight(root->left), getHeight(root->right));
	
	return rotation(root);
}

Node *predecessor(Node *root)
{
	Node *curr = root -> left;
	while(curr && curr -> right)
	{
		curr = curr -> right;
	}
	return curr;
}

Node *deleteNode(Node *root, int value)
{
	if(!root)
	{
		return NULL;
	}
	else if(value < root -> value)
	{
		root -> left = deleteNode(root -> left, value);
	}
	else if(value > root -> value)
	{
		root -> right = deleteNode(root -> right, value);
	}
	else
	{
		if(!root -> left || !root -> right)
		{
			Node *newRoot;
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
		Node *inOrder = predecessor(root);
		root -> value = inOrder -> value;
		root -> left = deleteNode(root -> left, inOrder -> value);
	}
	return rotation(updateNode(root));
}

void search(Node *root, int value)
{
	if(!root) // jika gada root
	{
		return; // return kosong aja
	}
	else if(root -> value == value)
	{
		printf("Found! Name : %s, key: %d, Height : %d\n", root -> string, root -> value, root -> height);
	}
	else if(value > root -> value)
	{
		return search(root -> right, value);
	}
	else if(value < root -> value)
	{
		return search(root -> left, value);
	}
}

void printInOrder(Node *root)
{
	if(root)
	{
		printInOrder(root -> left);
		printf("%d %s (h = %d)\n", root -> value, root -> string, root -> height);
		printInOrder(root -> right);
	}
}


int main(void)
{
	rootSS = insertNode(rootSS, 12, "Alpha");
	printf("12 Alpha masuk\n");
	rootSS = insertNode(rootSS, 15, "Beta");
	printf("15 Beta masuk\n");
	
	rootSS = insertNode(rootSS, 18, "Gamma");
	printf("18 Gamma masuk\n");
	
	printf("ROOT = %d\n", rootSS->value);
	
	rootSS = insertNode(rootSS, 20, "Gamma");
	printf("20 Gamma masuk\n");
	
	printf("\nINORDER=\n");
	printInOrder(rootSS);
	
	return 0;
}

