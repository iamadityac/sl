#include<stdio.h>
#include<stdlib.h>
#define INT_MAX 999

struct Edge {
	int src, dest, weight; 
}; 
struct Graph { 

	int V, E; 
	struct Edge* edge; 
}; 

void BellmanFord(struct Graph* graph, int src) {
	
	int i,j;
	int dist[graph->V];

	for ( i = 0; i < graph->V; i++) 
		dist[i] = INT_MAX; 
	dist[src] = 0; 

	for ( i = 0; i < graph->V-1; i++) {
		for ( j = 0; j < graph->E; j++) {
			if (dist[graph->edge[j].src] != INT_MAX && dist[graph->edge[j].src] + graph->edge[j].weight < dist[graph->edge[j].dest]) 
				dist[graph->edge[j].dest] = dist[graph->edge[j].src] + graph->edge[j].weight; 
		}
	}

	printf("Vertex Distance from Source\n"); 
	for ( i = 0; i < graph->V; ++i) 
		printf("%d \t\t %d\n", i, dist[i]); 

	return; 
}

int main() {
	int i;
	struct Graph *graph;
	
	graph = (struct Graph *)malloc(sizeof(struct Graph));

	printf("\n\tEnter number of Vertices >>");
	scanf("%d",&graph->V);
	printf("\n\tEnter number of Edges >>");
	scanf("%d",&graph->E);
	graph->edge = (struct Edge *)malloc(graph->E*sizeof(struct Edge));

	for(i=0;i<graph->E;i++) {
		printf("\n\tEnter (source,destination,weight) >>");
		scanf("%d%d%d",&graph->edge[i].src,&graph->edge[i].dest,&graph->edge[i].weight);
	}

	BellmanFord(graph, 0); 

	return 0; 
}
