#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	long long int i,j, tempi, tempj, r,c;
	const long long int C_MAX = 25;
	const long long int R_MAX = 10;

	long long int **A = (long long int**)malloc(R_MAX*sizeof(long long int*));
	for(i = 0; i < R_MAX; i++)
	{
		A[i] = (long long int*)malloc(C_MAX*sizeof(long long int));
		for(j = 0; j < C_MAX; j++) A[i][j] = -1;
	}

	for(i = 0; i < R_MAX; i++)
	{
		for(j = 0; j < C_MAX; j++)
		{
			tempi = i + 1;
			tempj = j + 1;

			if(tempi == 1 && tempj == 1) A[i][j] = 2;
			else if(tempi == 1) A[i][j] = A[i][j-1]*2;
			else if(tempj == 1)
			{
				if(A[i-1][1] != -1) A[i][j] = A[i-1][1];
				else break;
			}
			else if(A[i][j-1] != -1 && A[i][j-1] < C_MAX && A[i-1][A[i][j-1] - 1] != -1) A[i][j] = A[i-1][A[i][j-1] - 1];
			else break;

		}
	}


	printf("\t");
	for(j = 0; j < 3; j++) printf("j = %lld\t", j+1);
	printf("\n");
	for(i = 0; i < 2; i++)
	{
		printf("i = %lld\t", i+1);
		for(j = 0; j < 3; j++)
		{
			if(A[i][j] != -1) printf("%lld\t", A[i][j]);
			//printf("%lld\t", A[i][j]);
		}
		printf("\n");
	}

	printf("\n\n");
	while(i = -1 && j != -1)
	{
		printf("Enter i. i should be between 1 and 3 both included. Enter -1 to exit:");
		scanf("%lld", &r);

		if(r == -1) break;
		if(r < 1 || r > 3 )
		{
			printf("i should be between 1 and 3 both included\n");
		}
		else if(r == 1)
		{
			printf("Enter j. j should be between 1 and %lld both included. Enter -1 to exit:", C_MAX-2);
			scanf("%lld", &c);
			if(c == -1) break;
			if(c < 1 || c > C_MAX-2)
			{
				printf("j should be between 1 and %lld both included\n", C_MAX-2);
			}
			else printf("A(%lld,%lld) = %lld\n", r,c,A[r-1][c-1]);
		}
		else if(r == 2)
		{
			printf("Enter j. j should be between 1 and 3 both included. Enter -1 to exit:");
			scanf("%lld", &c);
			if(c == -1) break;
			if(c < 1 || c > 3)
			{
				printf("j should be between 1 and 3 both included\n");
			}
			else printf("A(%lld,%lld) = %lld\n", r,c,A[r-1][c-1]);
		}
		else if(r == 3)
		{
			printf("Only j = 1 is possible. Others overflow.\n");
			printf("A(3,1) = %lld\n", A[2][0]);
		}
	}


	return 0;
}