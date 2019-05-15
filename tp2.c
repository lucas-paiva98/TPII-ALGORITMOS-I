#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "utils.h"
#include "distance.h"


int minKey(int key[], int mstSet[], int vertices) { 
	// Initialize min value 
	int min = INT_MAX, min_index; 

	for (int v = 0; v < vertices; v++) 
	 	if (mstSet[v] == 0 && key[v] < min) 
      min = key[v], min_index = v; 
		
	return min_index; 
} 

int printMST(int parent[], int n, double **graph, int vertices) { 
printf("Edge \tWeight\n"); 
for (int i = 1; i < vertices; i++) 
    printf("%d - %d \t%lf \n", parent[i], i, graph[i][parent[i]]); 
} 

void primMST(double **graph, int vertices) { 
    // Array to store constructed MST 
    int parent[vertices];  
    // Key values used to pick minimum weight edge in cut 
    int key[vertices];  
    // To represent set of vertices not yet included in MST 
    int mstSet[vertices];  
  
    // Initialize all keys as INFINITE 
    for (int i = 0; i < vertices; i++) 
        key[i] = INT_MAX, mstSet[i] = 0; 
  
    // Always include first 1st vertex in MST. 
    // Make key 0 so that this vertex is picked as first vertex. 
    key[0] = 0;      
    parent[0] = -1; // First node is always root of MST  
  
    // The MST will have V vertices 
    for (int count = 0; count < vertices-1; count++) 
    { 
        // Pick the minimum key vertex from the  
        // set of vertices not yet included in MST 
        int u = minKey(key, mstSet, vertices); 
  
        // Add the picked vertex to the MST Set 
        mstSet[u] = 1; 
  
        // Update key value and parent index of  
        // the adjacent vertices of the picked vertex.  
        // Consider only those vertices which are not  
        // yet included in MST 
        for (int v = 0; v < vertices; v++) 
  
        // graph[u][v] is non zero only for adjacent vertices of m 
        // mstSet[v] is false for vertices not yet included in MST 
        // Update the key only if graph[u][v] is smaller than key[v] 
        if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) 
            parent[v] = u, key[v] = graph[u][v]; 
    } 
  
    // print the constructed MST 
    printMST(parent, vertices, graph, vertices); 
} 

int main(int argc, char const *argv[]) {
	FILE *fileCities;
	int citiesQuantity = 0;
	double **citiesMatrix;
	double citiesAux = 0;

	// fileCities = fopen(argv[1], "r");
	fileCities = fopen("cidades1.txt", "r");

	if (fileCities == NULL) {
    printf("Error! Cant't open the file.\n");
  	exit(1);
	}

	fscanf(fileCities, "%d", &citiesQuantity);

	citiesMatrix = allocateMatrix(citiesQuantity, 2);

	for (int i = 0; i < citiesQuantity; i++) {
		for (int j = 0; j < 2; j++) {
			fscanf(fileCities, "%lf", &citiesAux);
			citiesMatrix[i][j] = citiesAux;
		}
	}

	// Montar o grafo
	double **graph;
	double lat = 0;
	double lon = 0;
	double distance = 0;
	int citiesQuantityCol = 1;

	graph = allocateMatrix(citiesQuantity, citiesQuantity);
	
	
	for (int i = 0; i < citiesQuantity; i++) {
		lat = citiesMatrix[i][0];
		lon = citiesMatrix[i][1];
		for (int j = citiesQuantityCol; j < citiesQuantity; j++) {
			distance = distanceEarthKm(lat, lon, citiesMatrix[j][0], citiesMatrix[j][1]);
			graph[i][j] = distance;
			graph[j][i] = distance;
		}
		citiesQuantityCol++;
	}

		printf("\n");
		printf("\n");

	for (int i = 0; i < citiesQuantity; i++) {
		for (int j = 0; j < citiesQuantity; j++) {
			printf("%lf ", graph[i][j]);
		}
		printf("\n");
	}

  primMST(graph, citiesQuantity);

	return 0;
}