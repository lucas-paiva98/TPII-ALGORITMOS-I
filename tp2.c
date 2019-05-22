#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "utils.h"
#include "distance.h"
#include <time.h>

int findMinVertex(int minWeight[], int notInMBST[], int vertex) { 
	int min = INT_MAX;
	int minIndex; 

	for (int v = 0; v < vertex; v++) {
		if (notInMBST[v] == 0 && minWeight[v] < min) {
      min = minWeight[v];
      minIndex = v;
		} 
	} 
	 	 
	return minIndex; 
} 

void primMBST(int **graph, int vertex) { 
  // Key values used to pick minimum weight edge in cut 
  int minWeight[vertex];  
  // To represent set of vertex not yet included in MST 
  int notInMBST[vertex];
	int maxEdge = 0;

    // Initialize all minWeights as INFINITE 
    for (int i = 0; i < vertex; i++) 
        minWeight[i] = INT_MAX, notInMBST[i] = 0; 
  
    // Always include first 1st vertex in MST. 
    // Make minWeight 0 so that this vertex is picked as first vertex. 
    minWeight[0] = 0;      
    // MBST[0] = -1; // First node is always root of MST  
  
    // The MST will have V vertex 
    for (int i = 0; i < vertex; i++) { 
        // Pick the minimum minWeight vertex from the  
        // set of vertex not yet included in MST 
        int minVertex = findMinVertex(minWeight, notInMBST, vertex); 
        // Add the picked vertex to the MST Set 
        notInMBST[minVertex] = 1; 
  			
  			if (maxEdge < minWeight[minVertex]) {
  				maxEdge = minWeight[minVertex];
  			}

        // Update minWeight value and MBST index of  
        // the adjacent vertex of the picked vertex.  
        // Consider only those vertex which are not  
        // yet included in MST 
      for (int v = 0; v < vertex; v++) {
				// graph[minVertex][v] is non zero only for adjacent vertex of m 
				// notInMBST[v] is false for vertex not yet included in MST 
				// Update the minWeight only if graph[minVertex][v] is smaller than minWeight[v] 
				if (graph[minVertex][v] && notInMBST[v] == 0 && graph[minVertex][v] < minWeight[v]) {
					minWeight[v] = graph[minVertex][v];
				}
		}      
  } 
  
  printf("%d\n", maxEdge);
} 

int main(int argc, char const *argv[]) {
	FILE *fileCities;
	int citiesQuantity = 0;
	double **citiesMatrix;
	double citiesAux = 0;
	
	double total_time;
	clock_t start, end;
	
	start = clock();

	fileCities = fopen(argv[1], "r");

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

  primMBST(graph, citiesQuantity);
  end = clock();
  total_time = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("\nTime is: %f\n", total_time);
	return 0;
}