#include<stdio.h>

void merge(int *array,int x,int y)
{
    int mid=((x+y)/2),temp[20]={0};

    int l=x,r=y,m=mid+1,k=x;    

    if(y>x)
    {
        merge(array,x,mid);
        merge(array,mid+1,y);

        while( l<=mid && m<=r )
        {
            if(array[l]<=array[m])
            {
                temp[k++]=array[l++];
            }
            else
            {
                temp[k++]=array[m++];
            }
        }

        while( l<=mid )
            temp[k++]=array[l++];

        while( m<=r )
            temp[k++]=array[m++];

        for(k=x;k<=y;k++)
        {
            array[k]=temp[k];
        }
    }
}

//  //  //  //  //
int main()
{
    int n,i,array[20];

    printf("\n\tEnter the size >>");
    scanf("%d",&n);

    printf("\n\tEnter the array elemenets >>");
    for(i=0;i<n;i++)
    {
        scanf("%d",&array[i]);
    }

    printf("\n\tArray >>");
    for(i=0;i<n;i++)
    {
        printf("%d",array[i]);
    }

    printf("\n\t//  //  // ");
    sleep(5);

    merge(array,0,n-1);

    printf("\n\tSorted Array >>");
    for(i=0;i<n;i++)
    {
        printf("%d",array[i]);
    }

    printf("\n");
    return 0;
}