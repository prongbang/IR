#include <iostream>
#include <fstream>        // เพื่อใช้ FILE 

						// argc คือ นับว่ามีค่าที่ใส่เข้ามาผ่าน Argument มีกี่ตัว
						// ArgumentSearch text.txt    abc       b
						// ชื่อไฟล์.exe        ไฟล์        pat     method 
						// argv[0]        argv[1]    argv[2]  argv[3]    
using namespace std;

void bruteForce(char text[],int n , char pat[],int m);
void preQsBc(char *x,int m,int qsBc[]);
void QS(char *x, int m, char *y, int n);
void main(int argc, char *argv[])
{
	FILE *fp;             // ตัวแปรของ file

	char szBuff[2048];    // เก็บตัวอักษร
	char fname[20];		  // เก็บชื่อ 
	char method[2];		  // เก็บค่าจากผู้ใช้ ว่าต้องการ search แบบไหน 
	char pat[20];         // เก็บค่าของ Pattern 
	char c;               // เก็บตัวอักษร จากการ ดึงค่ามาจากไฟล์
	int i;				  // เก็บตำแหน่ง Array

	// เขียนไฟล์
	ofstream myfile;               // เขียนไฟล์ ลง Text 
	myfile.open("text.txt");       // ชื่อไฟล์ จะเก็บไว้ใน Debug
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
	do       // เปิดไฟล์ ดึงค่า ตัวอักษร แต่ละตัว มาเก็บไว้ใน szBuff[i] = c 
	{ 
		i = 0;
		while( (i < 2048) && ((c = getc(fp))!= EOF) )
		{
			szBuff[i] = c; 
			printf("szBuff[%d] = %c\n",i,szBuff[i]);
			i++;
		}

	}while( c != EOF );
	fclose(fp);								// ปิดไฟล์

	printf("i = %d\n",i);
	printf("pat = %d \n",strlen(pat));      // strlen(pat) หาความยาว patt

	if(strcmp(method,"a") == 0)               // เปรียบเทียบ ค่า
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
		if(memcmp(x,y+j,m) == 0)          // เปรียบเทียบค่าเป็นชุด
			printf("Found = %d \n",j);
		j += qsBc[y[j+m]];
	}
	cout << "j = "<< j <<endl;
	cout << "y[5] = " << y[5] << "\n"; // = ฬ
	cout << "qsBc[ฬ] = " << qsBc[y[5]] << endl;
	cout << "qsBc[C] = " << qsBc['C'] << endl;
}