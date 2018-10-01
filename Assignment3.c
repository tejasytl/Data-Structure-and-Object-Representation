//NAME		:TEJAS NITIN LAD
//ROLL NO. 	:14EC35025

//															HEADER INCLUDES

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100	//Defined Max Size for the Stack/Queue
#define INT_MIN -100 // Score value if the oppponent wins
#define INT_MAX 100 // Score value if the oppponent loses

// 									STRUCTURE DEFINITIONS -> board, STATE, STACK, QUEUE <- STRUCTURE DEFINITIONS

// Tic Tac Toe board
typedef char board[3][3]; 

//Structure Definition for State
//Stores the entire state of the game.
typedef struct node
{
	board b; // Tic Tac Toe board
	char turn; // 'x' or 'o'
	struct node *child[9]; // Child nodes
	int score; // Score as per the definition
	int comp; // =1 if it is the turn of computer, 0 otherwise
	int d; // Current Depth of the state
	int change; // What change was brought from earlier state to arrive at this state. i -> [i/3][i%3]
	int children; // number of child nodes for this state
}STATE;

//Structure Definition for Stack
typedef struct 
{
	int top;				//Index of top element of Stack
	STATE *item[MAXSIZE]; 	//Array of Tree Nodes

}STACK;

//Structure Definition for Queue
typedef struct
{
	int front; //Index of front element of Stack
	int end; //Index of end element of Stack
	STATE *item[MAXSIZE]; //Array of States
}QUEUE;

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
STATE* Top(STACK *s)
{
	if(IsEmpty(s) == 0) return s->item[s->top];
	return NULL;
}

//Push an element onto the stack
void Push(STACK *s, STATE *node)
{
	//Check if the stack is already full. If it is return without pushing.
	if(IsFull(s) == 1) return;

	//Increment top element and add element to it
	s->top = s->top + 1;
	s->item[s->top] = node; 
	return;
}

//Pop an element from the stack. Returns the popped element. Returns NULL if empty.
STATE *Pop(STACK *s)
{
	//Check if the stack is empty. Return NULL.
	if(IsEmpty(s) == 1) return NULL;

	//Returns the top most element and Decrements the top.
	s->top = s->top - 1;
	return s->item[s->top + 1];
}

// 							QUEUE FUNCTIONS -> QCreateQueue, QIsFull, QIsEmpty, QTop, QInsert, QDelete <- QUEUE FUNCTIONS

//Creates an empty queue
QUEUE *QCreateQueue()
{
	QUEUE *q = (QUEUE *)malloc(sizeof(QUEUE)); // Allocate space
	q->front = q->end = -1;
	return q;
}

//Returns 1 if the queue is full. Else returns 0.
int QIsEmpty(QUEUE *q)
{
	if(q->front == -1) return 1;
	return 0;
}

//Returns 1 if the queue is full. Else returns 0.
int QISFull(QUEUE *q)
{
	if(q->front == MAXSIZE - 1) return 1;
	return 0;
}

//Insert an element in the queue
void QInsert(QUEUE *q, STATE *node)
{
	//Check if the queue is already full. If it is return without pushing.
	if(QISFull(q)) return;

	if(QIsEmpty(q) == 1)
	{
		q->front = q->end = 0;
		q->item[0] = node;
		return;
	}

	q->item[++q->front] = node;
	return;
}

//Returns the top element of queue. Returns NULL if the stack is empty
STATE* QTop(QUEUE *q)
{
	//Check if the queue is empty. If it is return NULL.
	if(QIsEmpty(q) == 1) return NULL;
	return q->item[q->end];
}

//Deletes an element from the queue
void QDelete(QUEUE *q)
{
	//Check if the queue is empty. If it is return without deleting
	if(QIsEmpty(q) == 1) return;

	q->end++;
	if(q->front < q->end)
	{
		q->front = q->end = -1;
	}
	return;
}

// 							GAME FUNCTIONS -> IsGameOver, copy, CalculateScore, GetNextMove, UpdateBoard <- GAME FUNCTIONS


//Checks if the game is over
//Returns 1 if x has won
//Returns 2 if o has won
//Returns 3 if draw
//Else returns 0
int IsGameOver(board b)
{
	for(int i = 0; i < 3; i++)
	{
		if(b[i][0] == 'x' && b[i][1] == 'x' && b[i][2] == 'x') return 1; // x has won
		if(b[i][0] == 'o' && b[i][1] == 'o' && b[i][2] == 'o') return 2; // o has won
		if(b[0][i] == 'x' && b[1][i] == 'x' && b[2][i] == 'x') return 1; // x has won
		if(b[0][i] == 'o' && b[1][i] == 'o' && b[2][i] == 'o') return 2; // o has won
	}

	if(b[0][0] == 'x' && b[1][1] == 'x' && b[2][2] == 'x') return 1; // x has won
	if(b[0][0] == 'o' && b[1][1] == 'o' && b[2][2] == 'o') return 2; // o has won
	if(b[2][0] == 'x' && b[1][1] == 'x' && b[0][2] == 'x') return 1; // x has won
	if(b[2][0] == 'o' && b[1][1] == 'o' && b[0][2] == 'o') return 2; // o has won

	int count = 0;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(b[i][j] == 'x' || b[i][j] == 'o') count++;
		}
	}

	if(count == 9) return 3; // Entire board is filled. Hence Draw

	return 0; //Game is not over yet
}

//Copies game from one board to another.
void copy(board from, board to)
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++) to[i][j]  = from[i][j];
	}
	return;
}


//Calcuates the score of the current state.
int CalculateScore(STATE *cur)
{
	board b;
	copy(cur->b, b);

	int x = 0, o = 0;
	for(int i = 0; i < 3; i++)
	{
		if(b[i][0] != 'o' && b[i][1] != 'o' && b[i][2] != 'o') x++; // Row open for x to win
		if(b[i][0] != 'x' && b[i][1] != 'x' && b[i][2] != 'x') o++; // Row open for o to win
		if(b[0][i] != 'x' && b[1][i] != 'x' && b[2][i] != 'x') o++; // Column open for o to win
		if(b[0][i] != 'o' && b[1][i] != 'o' && b[2][i] != 'o') x++; // Column open for x to win
	}

	if(b[0][0] != 'o' && b[1][1] != 'o' && b[2][2] != 'o') x++; // Diagonal open for x to win
	if(b[0][0] != 'x' && b[1][1] != 'x' && b[2][2] != 'x') o++; // Diagonal open for o to win
	if(b[2][0] != 'o' && b[1][1] != 'o' && b[0][2] != 'o') x++; // Diagonal open for x to win
	if(b[2][0] != 'x' && b[1][1] != 'x' && b[0][2] != 'x') o++; // Diagonal open for o to win

	if(cur->comp == 1 && cur->turn== 'x') return x - o; // The computer is x, hence x - o
	else if(cur->comp == 1) return o - x; // The computer is o. Hence o - x
	else if(cur->turn == 'o') return x -o; // The computer is x. Hence x - o
	else return o - x; // The computer is o. Hence o - x.
}

//Returns next move from current step. i -> [i/3][i%3]
int GetNextMove(STATE *cur, int depth)
{
	QUEUE *q = QCreateQueue();
	STACK *s = CreateStack();
	
	QInsert(q, cur);
	while(QIsEmpty(q) == 0)
	{
		STATE *temp = QTop(q);
		QDelete(q);

		int g = IsGameOver(temp->b);

		if(g != 0 && g != 3 && temp->comp == 1) temp->score = INT_MIN;
		else if(g != 0 && g != 3) temp->score = INT_MAX;  
		else if(temp->d == depth || g == 3) temp->score = CalculateScore(temp);
		else
		{
			Push(s, temp);
			board b;
			copy(temp->b, b);

			for(int i = 0; i < 9; i++)
			{
				if(b[i/3][i%3] == '-')
				{
					STATE *news = (STATE *)malloc(sizeof(STATE));
					news->children = 0;

					b[i/3][i%3] = temp->turn;
					copy(b,news->b);
					b[i/3][i%3] = '-';

					if(temp->turn == 'x') news->turn = 'o';
					else news->turn = 'x';

					news->comp = 1 - temp->comp;
					news->change = i;
					news->d = temp->d + 1;

					temp->child[temp->children++] = news;
					QInsert(q, news); 
				}
			}
		}
	}

	STATE *curt = NULL;
	int best_turn;
	while(IsEmpty(s) == 0)
	{
		curt = Top(s);
		Pop(s);

		if(curt->comp == 1)
		{
			curt->score = INT_MIN;
			for(int i = 0; i < curt->children; i++)
			{
				if(curt->child[i]->score >= curt->score)
				{
					curt->score = curt->child[i]->score;
					best_turn = curt->child[i]->change;
				}
			}
		}
		else
		{
			curt->score = INT_MAX;
			for(int i = 0; i < curt->children; i++)
			{
				if(curt->child[i]->score <= curt->score)
				{
					curt->score = curt->child[i]->score;
					best_turn = curt->child[i]->change;
				}
			}
		}
	}

	return best_turn;
}

//Updates Board fron next move
STATE* UpdateBoard(STATE *cur, int depth)
{
	int next = GetNextMove(cur, depth);
	cur->b[next/3][next%3] = cur->turn;
	return cur;
}

//Pretty prints the board
void PrintBoard(board b)
{
	printf("\n\n");
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(b[i][j] == '-') printf("   ");
			else printf(" %c ", b[i][j]);

			if(j == 2) printf("\n");
			else printf("|");
		}

		if(i != 2)
		{
			printf("-----------\n");
		}
	}
	printf("\n\n");
}

// 										PLAY GAME FUNCTIONS -> Game1, Game2 -< PLAY GAME FUNCTIONS

void Game2()
{
	int depth;
	printf("\n\nPlease provide the lookahead depth.\n");
	printf("Enter a value betweeen 1 and 4, both included: ");
	scanf("%d", &depth);
	while(depth < 1 || depth > 5)
	{
		printf("Invalid Value.\n");
		printf("Enter a value betweeen 1 and 4, both included: ");
		scanf("%d", &depth);
	}

	printf("\n\n");
	printf("Please provide initial board configuration.\n");
	printf("Enter 'x' (without quotes) if a board position contains x.\n");
	printf("Enter 'o' (without quotes) if a board position contains o.\n");
	printf("Enter '-' (without quotes) if a board position is empty.\n");
	printf("\n\n");

	board b;
	int x = 0, o = 0;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			printf("Enter for position (%d,%d): ",i+1,j+1);
			fflush(stdin);
			scanf(" %c", &b[i][j]);
			while(b[i][j] != 'x' && b[i][j] != 'o' && b[i][j] != '-')
			{
				printf("Invalid input\n");
				printf("Enter for position (%d,%d): ",i+1,j+1);
				fflush(stdin);
				scanf(" %c", &b[i][j]);
			}

			if(b[i][j] == 'x') x++;
			else if(b[i][j] == 'o') o++;
		}
	}

	if(x > o + 1 || o > x || IsGameOver(b) != 0)
	{
		printf("Invalid Input.\n");
		printf("Lets Start Over\n\n");
		return;
	}

	STATE *cur = (STATE *)malloc(sizeof(STATE));
	cur->children = 0;
	copy(b,cur->b);
	if(x == o) cur->turn = 'x';
	else cur->turn = 'o';
	cur->comp = 1;
	cur->d = 0;

	cur = UpdateBoard(cur, depth);
	PrintBoard(cur->b);
	return;
}

void Game1()
{
	printf("\n\n\nLETS PLAY THE GAME\n\n");

	int depth;
	printf("Please provide the lookahead depth.\n");
	printf("Enter a value betweeen 1 and 4, both included: ");
	fflush(stdin);
	scanf("%d", &depth);
	while(depth < 1 || depth > 5)
	{
		printf("Invalid Value.\n");
		printf("Enter a value betweeen 1 and 4, both included: ");
		fflush(stdin);
		scanf("%d", &depth);
	}

	char user;
	printf("\n\nPlease select if you want to play 'x' or 'o'\n");
	printf("Enter 'x' or 'o': ");
	fflush(stdin);
	scanf(" %c", &user);
	while(user != 'x' && user != 'o') 
	{
		printf("Invalid Input\n");
		printf("Enter 'x' or 'o': ");
		fflush(stdin);
		scanf(" %c", &user);
	}

	board b;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++) b[i][j] = '-';
	}
	
	int comp = 1;
	if(user == 'x') comp = 0;

	while(IsGameOver(b) == 0)
	{
		printf("Current State\n");
		PrintBoard(b);

		if(comp == 1)
		{
			STATE *cur = (STATE *)malloc(sizeof(STATE));
			cur->children = 0;
			copy(b,cur->b);
			if(user == 'o') cur->turn = 'x';
			else cur->turn = 'o';
			cur->comp = 1;
			cur->d = 0;
			cur = UpdateBoard(cur, depth);
			copy(cur->b, b);
		}
		else
		{
			int row = -1, col = -1;
			int valid = 0;
			while(valid == 0)
			{
				row = -1, col = -1;
				while(row < 1 || row > 3)
				{
					printf("The row and column number should be betweeen 1 & 3, both included\n");
					printf("Please enter the row number: ");
					fflush(stdin);
					scanf("%d", &row);
				}
				while(col < 1 || col > 3)
				{
					printf("\nThe row and column number should be betweeen 1 & 3, both included\n");
					printf("Please enter the column number: ");
					fflush(stdin);
					scanf("%d", &col);
				}

				if(b[row-1][col-1] == '-') valid = 1;
				else printf("\n\n\nInvalid Input\n\n\n"); 
			}
			b[row-1][col-1] = user;
		}
		comp = 1- comp;

		printf("%d\n",IsGameOver(b));
	}

	PrintBoard(b);
	int g = IsGameOver(b);
	if(g == 3) printf("The Game is DRAW\n");
	else if(g == 1 && user == 'x') printf("CONGRATULATIONS!!! HURRAY!! YOU WIN\n");
	else if(g == 1) printf("YOU LOSE\n");
	else if(user == 'o') printf("CONGRATULATIONS!!! HURRAY!! YOU WIN\n");
	else printf("YOU LOSE\n");
 	
	return;

}

void PrintName()
{
	printf("\n\nNAME\t\t:TEJAS NITIN LAD\n");
	printf("ROLL NO.\t:14EC35025\n\n\n");
}

int main()
{
	PrintName();

	int game = 1;

	while(game == 1 || game == 2)
	{
		printf("\n\nPlease Enter the Game Number you wish to to play\n");
		printf("Enter 1 to play the entire Tic Tac Toe from scratch\n");
		printf("Enter 2 to provide a board position as input and the system will output the next step\n");
		printf("Enter anything else to end the program\n");
		printf("Enter Game Number: ");
		scanf("%d", &game);
		
		if(game == 1) Game1();
		else if(game == 2) Game2(); 
	}

	printf("\n\n\n");
	return 0;
}

