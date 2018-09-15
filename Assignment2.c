//NAME		:TEJAS NITIN LAD
//ROLL NO. 	:14EC35025

//															HEADER INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 100	//Defined Max Size for the Stack

// 										STRUCTURE DEFINITIONS -> TREENODE, STACK <- STRUCTURE DEFINITIONS

//Structure Definition for Tree Node
typedef struct TreeNode
{
	int data; 				//Data Field
	struct TreeNode *left;	//Left Child
	struct TreeNode *right;	//Right Child
}TREENODE;

//Structure Definition for Stack
typedef struct 
{
	int top;				//Index of top element of Stack
	TREENODE *item[MAXSIZE]; //Array of Tree Nodes

}STACK;

// 								STACK FUNCTIONS -> CreateStack, IsFull, IsEmpty, Top, Push, Pop <- STACK FUNCTIONS

//Creates an empty stack
STACK *CreateStack()
{
	STACK *s = (STACK *)malloc(sizeof(STACK)); // Allocate space
	s->top = -1;	
	return s;
}

//Returns 1 if the stack is full. Else returns 0.
int IsFull(STACK *s)
{
	if(s->top == MAXSIZE - 1) return 1;
	return 0;
}

//Return 1 if the stack is empty. Else returns 0;
int IsEmpty(STACK *s)
{
	if(s->top == -1) return 1;
	return 0;
}

//Returns the top element of stack. Returns NULL if the stack is empty
TREENODE* Top(STACK *s)
{
	if(IsEmpty(s) == 0) return s->item[s->top];
	return NULL;
}

//Push an element onto the stack
void Push(STACK *s, TREENODE *node)
{
	//Check if the stack is already full. If it is return without pushing.
	if(IsFull(s) == 1) return;

	//Increment top element and add element to it
	s->top = s->top + 1;
	s->item[s->top] = node; 
	return;
}

//Pop an element from the stack. Returns the popped element. Returns NULL if empty.
TREENODE *Pop(STACK *s)
{
	//Check if the stack is empty. Return NULL.
	if(IsEmpty(s) == 1) return NULL;

	//Returns the top most element and Decrements the top.
	s->top = s->top - 1;
	return s->item[s->top + 1];
}

//						TREE FUNCTIONS -> MakeNode, MakeTree, Preorder, Inorder, Postorder <- TREE FUNCTIONS

//Makes a TREENODE with data in the data field
TREENODE *MakeNode(int data)
{
	TREENODE *node = (TREENODE *)malloc(sizeof(TREENODE)); 	//Allocate Space
	node->data = data;
	node->left = NULL;
	node->right = NULL;

	return node;
}

//Make a Random Tree Recursively of size count. Assigns cur_element to root node.  
TREENODE *MakeTree(int count, int cur_element)
{
	if(count == 0) return NULL;

	TREENODE *tree = MakeNode(cur_element++); 	//Creates root
	count--;

	if(count == 0) return tree;

	int left_count = rand()%count + 1; 	//Number of nodes in left subtree	
	int right_count = count - left_count;	//Number of nodes in right subtree
	
	tree->left = MakeTree(left_count, cur_element);	//Makes left subtree
	tree->right = MakeTree(right_count, cur_element + left_count);	//Make right subtree
	return tree;
}

//Prints Preoder Traversal of the tree
void Preorder(TREENODE *tree)
{
	STACK *s = CreateStack();
	TREENODE *p = tree;

	printf("\n\nPreorder Traversal\n");
	while(p != NULL || IsEmpty(s) == 0)
	{
		if(p == NULL)
		{
			p = Pop(s);
			p = p->right;
		}
		else
		{
			printf("%d, ", p->data);
			Push(s,p);
			p = p->left;
		}
	}
	printf("\n\n");

	free(s); 	//Frees Stack Pointer
	return;
}

//Prints Inoder Traversal of the tree
void Inorder(TREENODE *tree)
{
	STACK *s = CreateStack();
	TREENODE *p = tree;

	printf("\n\nInorder Traversal\n");
	while(p != NULL || IsEmpty(s) == 0)
	{
		if(p == NULL)
		{
			p = Pop(s);
			printf("%d, ", p->data);
			p = p->right;
		}
		else
		{
			Push(s,p);
			p = p->left;
		}
	}
	printf("\n\n");

	free(s); 	//Frees Stack Pointer
	return;
}

//Prints Postoder Traversal of the tree
void Postorder(TREENODE *tree)
{
	STACK *s = CreateStack();
	TREENODE *p = tree;

	printf("\n\nPostorder Traversal\n");
	while(p != NULL || IsEmpty(s) == 0)
	{
		if(p == NULL)
		{
			p = Pop(s);
			if(p->right != NULL && p->right == Top(s))
			{
				TREENODE *temp = Pop(s);
				Push(s,p);
				p = temp;
			}
			else
			{
				printf("%d, ", p->data);
				p = NULL;
			}
		}
		else
		{
			if(p->right != NULL) Push(s, p->right);
			Push(s,p);
			p = p->left;
		}
	}
	printf("\n\n");

	free(s);	//Frees Stack Pointer
	return;
}

// 									MISCELLANEOUS FUNCTIONS -> PrintName <- MISCELLANEOUS FUNCTIONS

void PrintName()
{
	printf("\n\nNAME\t\t:TEJAS NITIN LAD\n");
	printf("ROLL NO.\t:14EC35025\n\n\n");
}

//																MAIN FUNCTION

int main()
{
	srand(time(0));

	PrintName();

	int tree_size = 50;
	printf("Tree Creation Starts\n");
	TREENODE *tree = MakeTree(tree_size, 0);
	printf("Tree Creation Ends\n");
	printf("Number of Nodes in tree: %d\n\n", tree_size);

	Preorder(tree); 	//Print Preoder Traversal of the tree
	Inorder(tree);		//Print Inorder Traversal of the tree
	Postorder(tree);	//Print Postorder Traversal of the tree;

	return 0;
}