#include<stdio.h>
int n, sum=0, psum=0;
int array[10];
int RT[10];
int F,t,j,i;

void sort()
{
	int i, j, temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(array[j]>array[j+1])
			{
				temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
			}
		}
	}
}
int main()
{
	int k=0, i;
	printf("\n\t***ost***\n\tEnter the no. of programs: ");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("\n\tProgram no %d size: ",i+1);
		scanf("%d",&array[i]);
	}
	sort();
	printf("\n\tSorted program length: ->");
	for(i=0;i<n;i++)
	{
		printf("%d\t",array[i]);
	}
	for(i=0;i<n;i++)
	{
		sum=0;
		for(j=0;j<=i;j++)
		{
			sum=sum+array[j];
		}
		RT[i]=sum;
	}
	F=0;
	for(i=0;i<n;i++)
	F=F+RT[i];
	
	printf("\n\n\tMean-retrieval time: -> %d\n", F/n);
    return 0;	
}
