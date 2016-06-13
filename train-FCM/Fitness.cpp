#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "head.h"

int Fitness(pgenGA pind[])
{
	int i;
	int icount;
	int res;
	double sum;
	for(icount = 0; icount < SIZEGROUP; icount++)
	{
		sum = 0;
		for(res = 0; res < RESPONSE; res++)
		{
		    for(i = 0; i < (TIME - 1); i++)
		    {
				sum = sum + (pind[icount]->error[res][i]) * (pind[icount]->error[res][i]);
		    }
		}
		sum = sum / (TIME - 1);
		sum = sum / RESPONSE;
		//sum = sigmoidF(sum);
		pind[icount]->fitness = 1 / sum;
			
	}

	return 0;
}