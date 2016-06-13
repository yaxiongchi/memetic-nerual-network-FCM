#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "head.h"

double sigmoidF(double x)
{
	return(1.0 / (1.0 + exp(-5 * x)));
}

int Termination(pgrpGA pgrp)
{
	//printf("%d generation completed.\n", pgrp->generationCount);
	if (pgrp->generationCount < pgrp->generationMax)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int IndivCopy(pgenGA pindS, pgenGA pindD)
{
	int i;
	int res;
	for(res = 0; res < RESPONSE; res++)
	{
		for(i = 0; i < (TIME - 1); i++)
		{
			pindD->error[res][i] = pindS->error[res][i];
		}
	}
	pindD->fitness = pindS->fitness;

	return 0;
}

int IndivSwap(pgenGA pind[], int x, int y)
{
	genGA indTemp;
	pgenGA pindTemp = &indTemp;
	IndivCopy(pind[x], pindTemp);
	IndivCopy(pind[y], pind[x]);
	IndivCopy(pindTemp, pind[y]);

	return 0;
}