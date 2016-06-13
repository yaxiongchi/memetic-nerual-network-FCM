#include <stdlib.h>
#include <stdio.h>
#include "head.h"

int ResultOutput(pgenGA pind[], int elite[], pgrpGA pgrp, double eliteWeight[])
{
	int i;
	FILE *fp;
	FILE *fp1;
	fp = fopen("solution.txt", "a");
	fp1 = fopen("NetworkPredict.txt", "a");

	for(i = 0; i < GENENUM; i++)
	{
		fprintf(fp, "%d ", elite[i]);
		fprintf(fp1, "%lf ", eliteWeight[i]);
	}
	fprintf(fp, "\n");
	fprintf(fp1, "\n");
	fclose(fp);
	fclose(fp1);
	//printf("Complete Node %d", pgrp->generationCount);
	pgrp->generationCount = 0;
	return 0;
}