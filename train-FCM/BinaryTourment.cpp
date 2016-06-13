#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "head.h"

int BinaryTourment(pgenGA pind[], pgrpGA pgrp, int populationMirror[][GENENUM])
{
	int populationMirrorTemp[SIZEGROUP][GENENUM] = {0};
	int icount;
	int gencount;
	double temp1;
	double temp2;
	int n;
	int m;
	
	genGA indTemp[SIZEGROUP];
	pgenGA pindTemp[SIZEGROUP];
	for(icount  = 0; icount < SIZEGROUP; icount++)
	{
		pindTemp[icount] = &indTemp[icount];
	}

	/*随机抽取两个个体，比较适应度大小*/
	for(icount = 0; icount < SIZEGROUP; icount++)
	{
		temp1 = rand() / (double)(RAND_MAX);
		temp2 = rand() / (double)(RAND_MAX);

		n = (int)( temp1 * (SIZEGROUP - 1) );
		m = (int)( temp2 * (SIZEGROUP - 1) );

		if( pind[n]->fitness > pind[m]->fitness)
		{
			IndivCopy( pind[n], pindTemp[icount]);
			for(gencount = 0; gencount < GENENUM; gencount++)
			{
				populationMirrorTemp[icount][gencount] = populationMirror[n][gencount];
			}
		}
		else
		{
			IndivCopy( pind[m], pindTemp[icount]);  
			for(gencount = 0; gencount < GENENUM; gencount++)
			{
				populationMirrorTemp[icount][gencount] = populationMirror[m][gencount];
			}
		}
	}

	/*Temp返还给真实的种群*/
	for( icount = 0; icount < SIZEGROUP; icount++)
	{
		IndivCopy(pindTemp[icount], pind[icount]);
		for(gencount = 0; gencount < GENENUM; gencount++)
		{
			populationMirror[icount][gencount] = populationMirrorTemp[icount][gencount];
		}
	}
	
	pgrp->generationCount++;
	return 0;
}