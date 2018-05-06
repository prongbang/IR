#include<iostream>
                                                          /* Boyer Moore */
using namespace std;

void preBmBc(char *x,int m,int bmBc[]);
void suffixes(char *x,int m, int *suff);
void preBmGs(char *x,int m, int bmGs[]);
void BM(char *x, int m, char *y, int n);
int MAX(int a, int b)
{
	if(a>b) return a;
	else return b;
}
void main()
{
	int a[255];
	BM("XANZYZBDCX",10,"ANPXYXANZYZBDCXYANDAN",21);
	system("pause");
}
void preBmBc(char *x,int m,int bmBc[])
{
	int i;
	for(i = 0; i < 255; i++)
		bmBc[i] = m;
	for(i = 0; i < m; i++)
		bmBc[x[i]] = (m-1)-i;
}
void suffixes(char *x,int m, int *suff)
{
	int f , g, i;
    
	suff[m-1] = m;
	
	g = m -1;
	for(i = m - 2; i >= 0; --i)
	{
		if(i > g && suff[i + m - 1 - f] < i - g)
			suff[i] = suff[i + m - 1 - f];
		else
		{
			if(i < g)
				g = i;
			f = i;
			while(g >= 0 && x[g] == x[g + m - 1 - f])
				--g;
			suff[i] = f - g;
		}
	}
	for(i = 0; i < m; i++)
		printf("x[%d] = %d\n",i,suff[i]);
}

void preBmGs(char *x,int m, int bmGs[])
{
	int i , j, suff[255];
	suffixes(x,m,suff);
	
	for(i = 0; i < m; ++i)
		bmGs[i] = m;
	j = 0;
	for(i = m -1; i >= -1; --i)
		if(i == -1 || suff[i] == i+1)
			for(; j < m-1 -i; ++j)
				if(bmGs[j] == m){v
					bmGs[j] = m -1 -i;
				}
	for(i = 0; i <= m-2; ++i)
		bmGs[m-1-suff[i]] = m -1 -i;

	for(i = 0; i < m ; ++i)
		printf("bmGs[%d] = %d \n",i,bmGs[i]);

}

void BM(char *x, int m, char *y, int n)
{
	int i , j ,bmGs[255],bmBc[255];

	preBmGs(x,m,bmGs);
	preBmBc(x,m,bmBc);

	j = 0;
	while(j <= n - m)
	{ 
		for(i = m - 1; i >= 0 && x[i] == y[i+j]; --i); 
		if(i < 0){
			printf("Found at = %d\n",j);
			j += bmGs[0];
		}
		else
		{
			j += MAX(bmGs[i],bmBc[y[i+j]] - m + 1 - i);
			//printf("j = %d\n",j);
			printf("bmGs[%d] = %d\n",i,bmGs[i]);
		}
	}
	printf("j = %d\n",j);
	/*
	printf("bmBc['A'] = %d\n",bmBc['A']);
	printf("bmBc['X'] = %d\n",bmBc['X']);
	printf("bmBc['P'] = %d\n",bmBc['P']);
	printf("bmBc['N'] = %d\n",bmBc['N']);
	printf("bmBc['M'] = %d\n",bmBc['M']);
	*/
}

 