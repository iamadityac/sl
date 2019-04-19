#include<stdio.h>
#define INFINITY 999

void accept(int array[10][10],int n) {
    int i,j;
    for(i=0;i<n;i++) {
        printf("\t");
        for(j=0;j<n;j++) {
            scanf("%d",&array[i][j]);
        }
    }
    return;
}
void display(int array[10][10],int n) {
    int i,j;
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            printf("\t%d",array[i][j]);
        }
        printf("\n");
    }
    return;
}
void transform(int array[10][10],int n,int row,int column) {
    int i,j;
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            if(i==row || j==column || (i==column && j==0))
                array[i][j]=INFINITY;
        }
    }
    return;
}
void copy(int array[10][10],int n,int temp[10][10]) {
    int i,j;
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            temp[i][j]=array[i][j];
        }
    }
    return;
}

void rowreduction(int array[10][10],int n,int *cost) {
    int i,j,min;

    for(i=0;i<n;i++) 
    {
        min=array[i][0];
        for(j=1;j<n;j++) 
        {
            if(array[i][j]<min)
                min=array[i][j];
        }
        
        for(j=0;j<n;j++) 
        {
            if(array[i][j]!=INFINITY)
                array[i][j]-=min;
        }
        if(min!=INFINITY)
            *cost+=min;
    }
}
void colreduction(int array[10][10],int n,int *cost) {
    int i,j,min;

    for(i=0;i<n;i++) {
        min=array[0][i];
        for(j=1;j<n;j++) {
            if(array[j][i]<min)
                min=array[j][i];
        }
        
        for(j=0;j<n;j++) {
            if(array[j][i]!=INFINITY)
                array[j][i]-=min;
        }
        if(min!=INFINITY)
            *cost+=min;
    }
}

//  //  //  //  //

int main() {

    int n,array[10][10],cost=0,visit[10]={0},vcount=0;
    int temp[10][10],intercost,tempcost,flag=0,i,j,k;

    printf("\n\tEnter the number of vertices >>");
    scanf("%d",&n);

    printf("\n\tEnter the distance matrix >>\n");
    accept(array,n);
    printf("\n\tDistance Matrix :\n");
    display(array,n);
    
    rowreduction(array,n,&cost);
    colreduction(array,n,&cost);
    printf("\n1st red:\n");
    display(array,n);
    
    visit[vcount++]=0;
    for(i=1;i<n;i++) 
    {
        intercost=INFINITY;
        for(j=0;j<n;j++) 
        {
        
            flag=0;
            for(k=0;k<vcount;k++) 
            {
                if(visit[k]==j)
                    flag=1;
            }
            if(flag==0) 
            {
                tempcost=0;
                copy(array,n,temp);
                tempcost+=array[visit[vcount-1]][j];
                transform(temp,n,visit[vcount-1],j);
                rowreduction(temp,n,&tempcost);
                colreduction(temp,n,&tempcost);
                if(tempcost<intercost) 
                {
                    intercost=tempcost;
                    visit[vcount]=j;
                }
            }
        }
        vcount++;
        cost+=array[visit[vcount-2]][visit[vcount-1]];
        transform(array,n,visit[vcount-2],visit[vcount-1]);
        rowreduction(array,n,&cost);
        colreduction(array,n,&cost);
        display(array,n);
        printf("\n");
    }
    
    printf("\n\tReduced distance matrix >>\n");
    display(array,n);
    printf("\n\tMin.Cost of TSP >> %d",cost);
    printf("\n\tPath >> ");
    for(k=0;k<n;k++)
        printf("%d --> ",visit[k]);
    printf("0\n");
    return 0;
}
