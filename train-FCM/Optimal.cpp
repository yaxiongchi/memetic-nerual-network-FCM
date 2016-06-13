#include <stdlib.h>
#include <stdio.h>
#include "head.h"

int Optimal(pgenGA pind[], int elite[], double *eliteFitness, int populationMirror[][GENENUM], double genWighMean[], double eliteWeight[])
{
	int icount = 1;
	int k = 0;
	int gencount = 0;

	for(icount = 1; icount < SIZEGROUP; icount++)
	{
		if(pind[icount]->fitness > pind[k]->fitness)
		{
			k = icount;
		}
	}

	double weight[SIZEGROUP][GENENUM] = {0};
	FILE *fp;
	fp = fopen("weight.txt", "r + t");
	icount = 0;

	for(icount = 0; icount < SIZEGROUP; icount++)
	{
		for(gencount = 0; gencount < GENENUM; gencount++)
		{
			fscanf(fp, "%lf", &weight[icount][gencount]);
		}
	}
	fclose(fp);

	for(gencount = 0; gencount < GENENUM; gencount++)
	{
		genWighMean[gencount] = weight[k][gencount];
	}

	if(pind[k]->fitness > (*eliteFitness))
	{
		for(gencount = 0; gencount < GENENUM; gencount++)
		{
			elite[gencount] = populationMirror[k][gencount];
			eliteWeight[gencount] = genWighMean[gencount];
		}
		(*eliteFitness) = pind[k]->fitness;
	}

	remove("weight.txt");
	
	return 0;

}