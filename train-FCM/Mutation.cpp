#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "head.h"

int Mutation(pgenGA pind[], pgrpGA pgrp, int populationMirror[][GENENUM])
{
	int icount;
	double temp;
	int m;
	int judge;

	for(icount = 0; icount < SIZEGROUP; icount++)
	{
		temp = rand() / (double)(RAND_MAX);
		if(temp < pgrp->probMutat)
		{
			m = rand() % GENENUM; 
			judge = populationMirror[icount][m];
			judge = !judge;
			populationMirror[icount][m] = judge;
		}
	}

	return 0;
}