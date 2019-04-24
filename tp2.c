#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	FILE *fileCities;
	int citiesQuantity = 0;

	fileCities = fopen(argv[1], "r");

	if (fileCities == NULL) {
    printf("Error! Cant't open the file.\n");
  	exit(1);
	}

	fscanf(fileCities, "%d", &citiesQuantity);


	return 0;
}