#include<stdio.h>

void maxmin(int *array,int x,int y,int *max,int *min);

int main()
{
	int array[20],n,i,max,min;
	
	printf("\n\tEnter the array size :");
	scanf("%d",&n);
	
	printf("\n\tEnter the Elements ::");
	for(i=0;i<n;i++)
	{
		scanf("%d",&array[i]);
	}
	
	printf("\n\tArray is:");
	for(i=0;i<n;i++)
	{
		printf(" %d",array[i]);
	}
	
	//function
	max=array[0];
	min=array[0];
	maxmin(array,0,n-1,&max,&min);
	
	printf("\n\tMax is :%d\n\tMin is :%d",max,min);
	
	printf("\n");
	return 0;
}

int maxf(int x,int y)
{
	if(x>y)
		return x;
	else
		return y;
}
int minf(int x,int y)
{
	if(x<y)
		return x;
	else
		return y;
}
void maxmin(int *array,int x,int y,int *max,int *min)
{
	int lmax,lmin;
	if(y<=x+1)
	{
		lmax=maxf(array[x],array[y]);
		lmin=minf(array[x],array[y]);
		if(lmin<*min)
			*min=lmin;
		if(lmax>*max)
			*max=lmax;
		return;	
	}
	else
	{
		maxmin(array,x,((x+y)/2),max,min);
		maxmin(array,(((x+y)/2)+1),y,max,min);
		lmax=maxf(array[x],array[y]);
		lmin=minf(array[x],array[y]);
		if(lmin<*min)
			*min=lmin;
		if(lmax>*max)
			*max=lmax;
		return;	
	}
}
