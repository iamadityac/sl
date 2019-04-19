#include<stdio.h>
#include<math.h>

int board[10],count;

void print(int n)
{
	int i,j;
	printf("\nSolution %d ::\n",++count);
	for(i=1;i<=n;i++)
		printf("\t%d",i);
	for(i=1;i<=n;i++)
	{
		printf("\n%d",i);
		for(j=1;j<=n;j++)
		{
			if(board[i]==j)
				printf("\tQ");
			else
				printf("\t-");
		}
	}
	printf("\n\n");
}

int place(int row,int column)
{
	int i;
	for(i=1;i<=row-1;i++)
	{
		if(board[i]==column || abs(board[i]-column)==abs(i-row))
			return 0;
	}
	return 1;
}

void queen(int row,int n)
{
	int column;
	for(column=1;column<=n;column++)
	{
		if(place(row,column))
		{
			board[row]=column;
			if(row==n)
				print(n);
			else
				queen(row+1,n);
		}
	}
}

//	//	//	//	//

int main()
{
	int n;

	printf("\n\tEnter the no. of queens >>");
	scanf("%d",&n);
	if(n==2 || n==3)
		printf("\n\tNo Feasible Solution\n");
	else
		queen(1,n);
		
	printf("\n");
	return 0;
}
/*
	Enter the no. of queens >>4

Solution 1 ::
	1	2	3	4
1	-	Q	-	-
2	-	-	-	Q
3	Q	-	-	-
4	-	-	Q	-


Solution 2 ::
	1	2	3	4
1	-	-	Q	-
2	Q	-	-	-
3	-	-	-	Q
4	-	Q	-	-



*/
