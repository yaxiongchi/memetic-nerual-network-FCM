#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"head.h"

double data[RESPONSE][GENENUM][TIME] = {0};
int populationMirror[SIZEGROUP][GENENUM] = {0};
double genExpect = 0;
double genTest[GENENUM] = {0};
double genWigh[RESPONSE][GENENUM] = {0};
double genWighMean[GENENUM] = {0};
	
int elite[GENENUM] = {0};
double eliteFitness = 0;
double eliteWeight[GENENUM] = {0};

int main()
{
	int icount = 0;  //指示
	int gencount = 0;
	int tim;   //指示TIME
	int res = 0;  //指示RESPONSE
	
	FILE *fp;
	fp = fopen("TimeSequence.txt","r+t");
	while(res < RESPONSE)
	{
		for(gencount = 0; gencount < GENENUM; gencount++)
		{
			for (tim = 0; tim < TIME; tim++)
		    {
				fscanf(fp, "%lf", &data[res][gencount][tim]);
		    }
		}
		res = res + 1;
	}
	fclose(fp);

	int flag = 0;
	srand((unsigned)time(NULL));  

	grpGA grp;
	pgrpGA pgrp = &grp;
	grp.generationCount = 0;
	grp.generationMax = 5000;  //遗传算法迭代次数
	grp.probCross = 0.9;     
	grp.probMutat = 0.1;    
	grp.size = SIZEGROUP;  //种群大小

	genGA ind[SIZEGROUP];
	pgenGA pind[SIZEGROUP];

	for(icount = 0; icount < SIZEGROUP; icount++)
	{
		pind[icount] = &ind[icount];
	}
	
	int u = 0;
	for(u = 0; u < GENENUM; u++)
	{
		printf("%d node learn\n", u);
		FILE *fp1;
		fp1 = fopen("Individuals.txt","r+t");
		icount = 0;
		while(icount < SIZEGROUP)
		{
			for (gencount = 0; gencount < GENENUM; gencount++)
			{
				fscanf(fp1, "%d", &populationMirror[icount][gencount]);
			}
			icount = icount + 1;
		}
		fclose(fp1);

		genExpect = 0;
		for(res = 0; res < RESPONSE; res++)
		{
			for(gencount = 0; gencount < GENENUM; gencount++)
			{
				genWigh[res][gencount] = 0;
			}
		}

		for(gencount = 0; gencount < GENENUM; gencount++)
		{
			genTest[gencount] = 0;
			genWighMean[gencount] = 0;
			elite[gencount] = 0;
			eliteWeight[gencount] = 0;
		}
	    
		eliteFitness = 0;

		do
		{
			Initial(pind);

			ErrorCmp(pind, data, populationMirror, genTest, genWigh, genWighMean, genExpect, &u);
			Fitness(pind);
			Optimal(pind, elite, &eliteFitness, populationMirror, genWighMean, eliteWeight);
			
			flag = Termination(pgrp);
			if(flag)
			{
				break;
			}

			BinaryTourment(pind, pgrp, populationMirror);
			Crossover(pind, pgrp, populationMirror);  
			Mutation(pind, pgrp, populationMirror); 
		
		}while(1);

		ResultOutput(pind, elite, pgrp, eliteWeight);
	}
	
	return 0;
}
