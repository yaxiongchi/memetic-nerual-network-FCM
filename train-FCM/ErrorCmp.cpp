#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "head.h"

int ErrorCmp(pgenGA pind[], double data[][GENENUM][TIME], int populationMirror[][GENENUM], double genTest[], double genWigh[][GENENUM], double genWighMean[], double genExpect, int *u)
{
	int icount = 0;
	int gencount;
	int temp;
	int i;
	int iter;
	int res;

	double genWighYesterday[RESPONSE][GENENUM] = {0};
	double genWighTemp[GENENUM] = {0};

	double value; //计算△w
	double out;
	double sum;

	double input[GENENUM] = {0};
	double target = 0;
	double output = 0;

	double summary = 0;
	double casual;


	
	int U;
	U = *u;

	for(icount = 0; icount < SIZEGROUP; icount++)
	{
		for(res = 0; res < 1; res++)
		{
			for(gencount = 0; gencount < GENENUM; gencount++) //对genWigh, genWighYesterday清0
			{
				genWigh[res][gencount] = 0;
			    genWighYesterday[res][gencount] = 0;
			}
			
			for(iter = 0; iter < EPOCHS; iter++)
			{
				for(gencount = 0; gencount < GENENUM; gencount++)
				{
					genWighTemp[gencount] = 0;
			    }
				
				for(i = 0; i < (TIME - 1); i++)
			    {
					for(gencount = 0; gencount < GENENUM; gencount++) 
					{
						temp = populationMirror[icount][gencount];
					    if(temp == 1)
					    {
							genTest[gencount] = data[res][gencount][i];
						}
					    else
					    {
							genTest[gencount] = 0.0;
					    }
					}
					
					genExpect = data[res][U][i + 1];
					
				    sum = 0;
					for(gencount = 0; gencount < GENENUM; gencount++)
				    {
						sum = sum + genTest[gencount] * genWigh[res][gencount];
				    }
					value = sigmoidF(sum);
				    out = genExpect - value;
				    for(gencount = 0; gencount < GENENUM; gencount++)
					{
						casual = genTest[gencount];
				        genWighTemp[gencount] = genWighTemp[gencount] + (out * value *(1 - value) * casual);
					}
				}
				
				for(gencount = 0; gencount < GENENUM; gencount++) //update w
			    {
					genWigh[res][gencount] = genWigh[res][gencount] + BETA * genWighTemp[gencount] + MOMENT * (genWigh[res][gencount] - genWighYesterday[res][gencount]);
				    genWighYesterday[res][gencount] = genWigh[res][gencount];
			    }
			}
		}

		/*
		double add;
		for(gencount = 0; gencount < GENENUM; gencount++) //计算genWighMean
		{
			add = 0;
			for(res = 0; res < RESPONSE; res++)
			{
				add = add + genWigh[res][gencount];
			}
			genWighMean[gencount] = add / RESPONSE;
		}
		*/
		for(gencount = 0; gencount < GENENUM; gencount++){
			genWighMean[gencount] = genWigh[0][gencount]; //只对node0
		}
		
		FILE *fp;
		fp = fopen("weight.txt", "a");

		for(gencount = 0; gencount < GENENUM; gencount++)
		{
			fprintf(fp, "%lf ", genWighMean[gencount]);
		}
		fprintf(fp, "\n");
		fclose(fp);

		for(gencount = 0; gencount < GENENUM; gencount++)
		{
			input[gencount] = 0;
		}
		
		target = 0;
		output = 0;

		for(res = 0; res < RESPONSE; res++) //计算error
		{
			for(i = 0; i < (TIME - 1); i++)
			{
				for(gencount = 0; gencount < GENENUM; gencount++)
				{
					temp = populationMirror[icount][gencount];
					if(temp == 1)
					{
						input[gencount] = data[res][gencount][i];
					}
				    else
					{
						input[gencount] = 0.0;
					}
				}
				
				target = data[res][U][i + 1];
			
			    summary = 0;
			    for(gencount = 0; gencount < GENENUM; gencount++)
			    {
					summary = summary + input[gencount] * genWighMean[gencount];
			    }
				output = sigmoidF(summary);
			    pind[icount]->error[res][i] = target - output;
			}
		}
	}

	return 0;
}