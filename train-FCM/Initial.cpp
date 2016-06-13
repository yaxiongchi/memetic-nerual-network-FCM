#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "head.h"

int Initial(pgenGA pind[])
{
	int icount;
	int i;
	int res;
	for(icount =  0; icount < SIZEGROUP; icount++)
	{
		for(res = 0; res < RESPONSE; res++)
		{
			for(i = 0; i < (TIME - 1); i++)
			{
				pind[icount]->error[res][i] = 0;
			}
		}
		
		pind[icount]->fitness = 0;
	}

	return 0;
}