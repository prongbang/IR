#include <iostream>
#include <fstream>        // ������ FILE 

						// argc ��� �Ѻ����դ�ҷ���������Ҽ�ҹ Argument �ա����
						// ArgumentSearch text.txt    abc       b
						// �������.exe        ���        pat     method 
						// argv[0]        argv[1]    argv[2]  argv[3]    
using namespace std;

void bruteForce(char text[],int n , char pat[],int m);
void preQsBc(char *x,int m,int qsBc[]);
void QS(char *x, int m, char *y, int n);
void main(int argc, char *argv[])
{
	FILE *fp;             // ����âͧ file

	char szBuff[2048];    // �纵���ѡ��
	char fname[20];		  // �纪��� 
	char method[2];		  // �纤�Ҩҡ����� ��ҵ�ͧ��� search Ẻ�˹ 
	char pat[20];         // �纤�Ңͧ Pattern 
	char c;               // �纵���ѡ�� �ҡ��� �֧����Ҩҡ���
	int i;				  // �纵��˹� Array

	// ��¹���
	ofstream myfile;               // ��¹��� ŧ Text 
	myfile.open("text.txt");       // ������� �������� Debug
	myfile << "ababbbababcbcab";   // Text 
	myfile.close();   
 
	switch(argc){
		case 1: break;
		case 4 : strcpy(method,argv[3]);   
		case 3 : strcpy(pat,argv[2]);
		case 2 : strcpy(fname,argv[1]);
			break;
		default: printf("Please Enter Example >source example.txt abbababac a \n");
			break;
	}

	if((fp = fopen(fname,"rb"))== NULL){
		 perror("Not File.\n");
		 return;
	} 
	do       // �Դ��� �֧��� ����ѡ�� ���е�� �������� szBuff[i] = c 
	{ 
		i = 0;
		while( (i < 2048) && ((c = getc(fp))!= EOF) )
		{
			szBuff[i] = c; 
			printf("szBuff[%d] = %c\n",i,szBuff[i]);
			i++;
		}

	}while( c != EOF );
	fclose(fp);								// �Դ���

	printf("i = %d\n",i);
	printf("pat = %d \n",strlen(pat));      // strlen(pat) �Ҥ������ patt

	if(strcmp(method,"a") == 0)               // ���º��º ���
		bruteForce(szBuff,i,pat,strlen(pat));
	else if(strcmp(method,"b") == 0)
		QS(pat,strlen(pat),szBuff,i);
}

void bruteForce(char text[],int n , char pat[],int m)
{
	/* bruteForce */
	int i , k, j, limit, count = 0,found = 0; 
	limit = n - m +1;

	for( i = 0; i <= limit-1; i++) // 0 - 3  / 01
	{
		k = i; 
		if(text[k] != pat[0]) found++; 
		for(j = 0; j <= m-1 && text[k] == pat[j]; j++) // 2 
		{
			k++; 
			found++; ///    /
		} 
		if(j > m - 1)
		{ 
			printf("Found at = %d \n",i);
		}   
		if(i != 0)
			count++;
	}
	printf("count = %d \n",count);
	printf("Found = %d \n",found);
}

void preQsBc(char *x,int m,int qsBc[])
{
	int i;
	for(i = 0; i < 256; ++i)
		qsBc[i] = m+1;
	for(i = 0; i < m; ++i)
		qsBc[x[i]] = m-i;
}

void QS(char *x, int m, char *y, int n)
{
	int j,i,qsBc[256];
	/* Preprocessing */
	preQsBc(x,m,qsBc);
	/* Searching */
	j = 0;
	
	while(j <= n - m)
	{ 
		cout << "ej = "<< j <<endl;
		if(memcmp(x,y+j,m) == 0)          // ���º��º����繪ش
			printf("Found = %d \n",j);
		j += qsBc[y[j+m]];
	}
	cout << "j = "<< j <<endl;
	cout << "y[5] = " << y[5] << "\n"; // = �
	cout << "qsBc[�] = " << qsBc[y[5]] << endl;
	cout << "qsBc[C] = " << qsBc['C'] << endl;
}