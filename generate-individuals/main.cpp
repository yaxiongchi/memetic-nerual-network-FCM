#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

#define GENENUM 5
#define SIZEGROUP 100

int main()
{
	int i;
	int icount;
	int value;
	double temp;
	srand((unsigned)time(NULL));
	FILE *fp;
	fp = fopen("Individuals.txt","w");

	for(icount = 0; icount < SIZEGROUP; icount++){
		for(i = 0; i < GENENUM; i++){
			temp = rand() / (double)RAND_MAX;
			if(temp < 0.8)
				value = 1;
			else
				value = 0;
			printf("%d ", value);
			fprintf(fp, "%d ", value);
		}
		fprintf(fp, "\n");
		printf("\n");
	}

	return 0;
}