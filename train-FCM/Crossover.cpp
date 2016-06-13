#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "head.h"

int Crossover(pgenGA pind[], pgrpGA pgrp, int populationMirror[][GENENUM])
{
	int icount;
	int tSize;
	int n;
	int t;
	double temp;
	int populationTemp[GENENUM] = {0};

	//随机打乱样本顺序
	for(icount = SIZEGROUP - 1; icount > 0; icount--)
	{
		temp = rand() / (double)(RAND_MAX);
		n = (int)(temp * (icount - 1));
		IndivSwap(pind, icount, n);
		
		//n号gene和icount号基因互换
		for(t = 0; t < GENENUM; t++)
		{
			populationTemp[t] = populationMirror[icount][t];
			populationMirror[icount][t] = populationMirror[n][t];
			populationMirror[n][t] = populationTemp[t];
		}
	}
	
	//开始两两配对
	int dot;
	int j;
	int hammal;

	tSize = SIZEGROUP / 2;
	for(icount = 0; icount < tSize; icount++)
	{
		temp = rand() / (double)(RAND_MAX);
		if(temp < pgrp->probCross)
		{
			//casual = rand() / (double)(RAND_MAX);
			//dot = (int)(casual * (GENENUM - 1));
			dot = rand() % (GENENUM - 1);

			for(j = 0; j <= dot; j++)
			{
				hammal = populationMirror[icount][j];
				populationMirror[icount][j] = populationMirror[icount + tSize][j];
				populationMirror[icount + tSize][j] = hammal;
			}
		}
	}

	return 0;
}