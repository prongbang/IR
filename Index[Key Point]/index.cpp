#include<iostream>
#include<string>
using namespace std;
							/* ../Debug>Index index.txt windows  */
void main(int argc , char*argv[])			
{
	FILE* fp;
	char fname[50];			 /* จัด Keyword และ Point แล้วค้นหาจาก Pattent */
	char *szBuf[100];
	char c[50];

	string keyword[50];
	string point[50];
	char patt[50];

	int size = 0, x = 0; 

	switch (argc)
	{
		case 1 : break;
		case 3: strcpy(patt,argv[2]); 
		case 2: strcpy(fname,argv[1]); break; 
		default: printf("please enter >filename file.txt");
			return;
	}  
	if((fp = fopen(fname,"rb")) == NULL)
	{
		printf("Error:Can't open file\n");
		return;
	} 
						/*------- อ่านค่าจาก FILE มาไว่้ใน szBuf -------- */
	while (( size < sizeof(szBuf) ) && ((fscanf( fp,"%s", c )) != EOF ))
	{  
		szBuf[size] = (char*)malloc(strlen(c));
		strcpy(szBuf[size],c);   
		size++;
	} 
	fclose(fp);   
	printf("Total %d byte \n",size);

	int round = 0;
	string str="";						/* Format Keyword Point */
	for( x = 1; x <= size; x++ ) 
	{ 
		if(x%2 != 0)	// คู่
		{ 
			keyword[round] = szBuf[x-1];							 // string รับค่าจาก char szBuf
			cout << "keyword["<< round<<"] = "<<keyword[round] << endl; 
		}
		else			// คี่
		{ 
			point[round] = szBuf[x-1];
			cout << "point["<< round <<"] = "<<point[round] << endl; 
			round++;
		}  
	}	// for x%2
	for( x = 0; x < size; x++ )			// Search keyword 
	{
		if(keyword[x].compare(patt) == 0)	// เปรียบเทียบข้อตวาม
		{
			cout << "\nFound at : " << point[x] << "\n"; break;
		}
	} // for search
}