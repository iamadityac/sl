#include<iostream>
using namespace std;

#define INT_MAX 999999

int n=4;
int dist[10][10] = {
        {0,9,8,8},
        {12,0,13,6},
        {10,9,0,5},
        {20,15,10,0}
};
int VISITED_ALL = (1<<n) -1;

int dp[16][4];


int  tsp(int mask,int pos){
	
	if(mask==VISITED_ALL){
		return dist[pos][0];
	}
	if(dp[mask][pos]!=-1){
	   return dp[mask][pos];
	}

	//Now from current node, we will try to go to every other node and take the min ans
	int ans = INT_MAX;

	//Visit all the unvisited cities and take the best route
	for(int city=0;city<n;city++){

		if((mask&(1<<city))==0){

			int newAns = dist[pos][city] + tsp( mask|(1<<city), city);
			ans = min(ans, newAns);
		}

	}
	
	return dp[mask][pos] = ans;
} 

int main(){
    /* init the dp array */
    for(int i=0;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            dp[i][j] = -1;
        }
    }
	cout<<"Travelling Saleman Distance is "<<tsp(1,0);

return 0;
}

/*
	
				**OUTPUT**
				
	aakash@Aakash:~$ gcc 41.c
aakash@Aakash:~$ ./a.out

		**Travelling Salesman Problem using Dynamic Programming**

	Enter the no. of cities : 4

	Enter the Cost Matrix :

	Enter Elements of Row 1 : 0 20 42 25

	Enter Elements of Row 2 : 20 0 30 34

	Enter Elements of Row 3 : 42 30 0 10

	Enter Elements of Row 4 : 25 34 10 0

	The cost matrix is :
	0	20	42	25	
	20	0	30	34	
	42	30	0	10	
	25	34	10	0
		
	Minimum cost is 85



	aakash@Aakash:~$ ./a.out

		**Travelling Salesman Problem using Dynamic Programming**

	Enter the no. of cities : 4

	Enter the Cost Matrix :

	Enter Elements of Row 1 : 0 10 15 20

	Enter Elements of Row 2 : 10 0 35 25

	Enter Elements of Row 3 : 15 35 0 30

	Enter Elements of Row 4 : 20 25 30 0

	The cost matrix is :
	0	10	15	20	
	10	0	35	25	
	15	35	0	30	
	20	25	30	0	
	
	Minimum cost is 80

*/



