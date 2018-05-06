#include <iostream>
                                                                                    /* Karp Rabin */
#define REHASH(a,b,h) ((((h) - (a)*d) << 1) + (b))
//hy = REHASH(y[j],y[j + m], hy);
using namespace std; 

void KR(char *x,int m , char *y, int n);

void main(int argc, char *argv)
{
	KR("abbabab",7,"acbaabbabab",11);
	system("pause");
}
void KR(char *x,int m , char *y, int n)
{
	int d,hx,hy,i,j;

	/* Preprocessing */
	for(d = i = 1; i < m; ++i) {
		d = (d << 1); 
		printf("d = %d\n\n",d);
	} 

	for(hx = hy = i = 0; i < m; ++i){
		hx = ((hx << 1) + x[i]);  /* pattern */
		hy = ((hy << 1) + y[i]);  /* text */ 
		printf("hx = %d and x[%d] = %d\n",hx,i,x[i]);
		printf("hy = %d and y[%d] = %d\n",hy,i,y[i]);
	}
	printf("\n");
	/* Searching */
	j = 0;
	//hy = REHASH(y[j],y[j + m], hy);printf("hy = %d\n",hy);
	while(j <= n - m){
		if(hx == hy && memcmp(x, y + j, m) == 0)
			printf("Found at : %d \n",j);
		hy = REHASH(y[j],y[j + m], hy);
		printf("hy = %d\n",hy);
		++j;
	}
	
}