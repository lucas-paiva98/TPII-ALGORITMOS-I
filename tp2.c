#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "utils.h"
#include "distance.h"


int findMinVertex(int key[], int mstSet[], int vertex) { 
	// Initialize min value 
	int min = INT_MAX, min_index; 

	for (int v = 0; v < vertex; v++) 
	 	if (mstSet[v] == 0 && key[v] < min) 
      min = key[v], min_index = v; 

	return min_index; 
} 

void primMST(int **graph, int vertex) { 
  // Array to store constructed MST 
  int MBST[vertex];
  // Key values used to pick minimum weight edge in cut 
  int key[vertex];  
  // To represent set of vertex not yet included in MST 
  int mstSet[vertex];
	int largestEdge = 0;

    // Initialize all keys as INFINITE 
    for (int i = 0; i < vertex; i++) 
        key[i] = INT_MAX, mstSet[i] = 0; 
  
    // Always include first 1st vertex in MST. 
    // Make key 0 so that this vertex is picked as first vertex. 
    key[0] = 0;      
    MBST[0] = -1; // First node is always root of MST  
  
    // The MST will have V vertex 
    for (int i = 0; i < vertex; i++) { 
        // Pick the minimum key vertex from the  
        // set of vertex not yet included in MST 
        int minVertex = findMinVertex(key, mstSet, vertex); 
        // Add the picked vertex to the MST Set 
        mstSet[minVertex] = 1; 
  			
  			if (largestEdge < key[minVertex]) {
  				largestEdge = key[minVertex];
  			}

        // Update key value and MBST index of  
        // the adjacent vertex of the picked vertex.  
        // Consider only those vertex which are not  
        // yet included in MST 
      for (int v = 0; v < vertex; v++) {
				// graph[minVertex][v] is non zero only for adjacent vertex of m 
				// mstSet[v] is false for vertex not yet included in MST 
				// Update the key only if graph[minVertex][v] is smaller than key[v] 
				if (graph[minVertex][v] && mstSet[v] == 0 && graph[minVertex][v] < key[v]) {
					MBST[v] = minVertex;
					key[v] = graph[minVertex][v];
				}
		}      
  } 
  
  printf("%d\n", largestEdge);
} 

int main(int argc, char const *argv[]) {
	FILE *fileCities;
	int citiesQuantity = 0;
	double **citiesMatrix;
	double citiesAux = 0;

	fileCities = fopen(argv[1], "r");
	// fileCities = fopen("t1.txt", "r");

	if (fileCities == NULL) {
    printf("Error! Cant't open the file.\n");
  	exit(1);
	}

	fscanf(fileCities, "%d", &citiesQuantity);

	citiesMatrix = allocateMatrixDouble(citiesQuantity, 2);

	for (int i = 0; i < citiesQuantity; i++) {
		for (int j = 0; j < 2; j++) {
			fscanf(fileCities, "%lf", &citiesAux);
			citiesMatrix[i][j] = citiesAux;
		}
	}

	int **graph;
	double lat = 0;
	double lon = 0;
	int distance = 0;
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

  primMST(graph, citiesQuantity);

	return 0;
}