#define SIZEGROUP 500
#define TIME 10//���г���
#define GENENUM 5
#define RESPONSE 1//��Ӧ�ĸ���

#define EPOCHS 20//ANNѵ���ĵ�������
#define BETA 0.9//ANN��ѧϰ�ٶ�ϵ��
#define MOMENT 0.9//ANN BP ����Ȩֵ�еĶ�����

typedef struct groupGA
{
	int size;
	double probCross;   //0.9
	double probMutat; //0.1
	int generationCount;
	int generationMax;
} grpGA, *pgrpGA;

typedef struct geneGA
{
	double error[RESPONSE][TIME - 1];
	double fitness;
} genGA, *pgenGA;


int Initial(pgenGA pind[]);
int ErrorCmp(pgenGA pind[], double data[][GENENUM][TIME], int populationMirror[][GENENUM], double genTest[], double genWigh[][GENENUM], double genWighMean[], double genExpect, int *u);
double sigmoidF(double x);
int Fitness(pgenGA pind[]);
int Optimal(pgenGA pind[], int elite[], double *eliteFitness, int populationMirror[][GENENUM], double genWighMean[], double eliteWeight[]);
int Termination(pgrpGA pgrp);
int IndivCopy(pgenGA pindS, pgenGA pindD);
int IndivSwap(pgenGA pind[], int x, int y);
int BinaryTourment(pgenGA pind[], pgrpGA pgrp, int populationMirror[][GENENUM]);
int Crossover(pgenGA pind[], pgrpGA pgrp, int populationMirror[][GENENUM]);
int Mutation(pgenGA pind[], pgrpGA pgrp, int populationMirror[][GENENUM]);
int ResultOutput(pgenGA pind[], int elite[], pgrpGA pgrp, double eliteWeight[]);