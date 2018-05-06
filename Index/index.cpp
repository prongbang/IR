#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

void main(int argc, char*argv[])
{
	FILE* fp;

	const int sizebuf = 1000;

	char fname[50];
	char *szBuf[sizebuf];
	char c[sizebuf];

	int size = 0;
	int z = 0,x = 0;
	int count[sizebuf];
	int known[sizebuf];
	int freq[sizebuf];

	int countbuf = 0; 
	char *dataBuf[sizebuf];
	const int sizeofword = 7;
	char *word[sizeofword];			// เก็บคำทั่วไป 
	char pat[50]; 

	word[0] = "is";  word[1] = "for";
	word[2] = "the"; word[3] = "this";
	word[4] = "of";  word[5] = "am";
	word[6] = "are";

	for(z = 0; z < sizebuf; z++ ) { count[z] = 0; known[z] = 1;}

	switch(argc)
	{
		case 3: strcpy(pat,argv[2]);
		case 2: strcpy(fname,argv[1]); break;
		default:cout<< "please enter file file.txt"; return;
	}
	if((fp = fopen(fname,"rb")) == NULL)
	{
		cout << "Error: Can't open file"; return;
	} 
	while((size < sizebuf ) && ((fscanf(fp,"%s",c)) != EOF))
	{
		szBuf[size] = (char*)malloc(strlen(c));
		strcpy(szBuf[size],c);  
		size++; 
	}
	fclose(fp); 
	/* Count */
	for(x = 0; x < size; x++) 
		for ( z = 0; z < size; z++ ) 
			if(strcmp(szBuf[x],szBuf[z]) == 0) count[z]++;
	 
	/* Known */
	for(x = 0; x < size; x++) 
		for ( z = x+1; z < size; z++ ) 
		{
			if(known[z] != -1)
				if(strcmp(szBuf[x],szBuf[z]) == 0) known[z] = -1;
		} // for z

	/* Print */
	for ( z = 0; z < size; z++ )
	{
		cout << setfill(' ') << "szBuf["<<z+1<<"] = " << szBuf[z];
		cout << setw(20) << "count["<<z+1<<"] = " << count[z];
		cout << setw(10) << "known["<<z+1<<"] = " << known[z] << "\n";
	}
	/* ตัดคำซ้ำ ออก known */
	for ( z = 0; z < size; z++ )
	{
		if(known[z] == 1)
		{
			dataBuf[countbuf] = szBuf[z];
			freq[countbuf] = count[z];
			countbuf++;
		}
	}cout << "\n"; 
	/* Print dataBuf freq */
	for ( z = 0; z < countbuf; z++ )
	{
		cout << setfill(' ') << "dataBuf["<<z<<"] = "<< dataBuf[z] << setw(15) << "freq["<<z<<"] = "<< freq[z] << "\n";
	} 

	/* ตัดคำทั่วไป ออก */
	for(x = 0; x < sizeofword; x++) // รอบของ word
		for ( z = 0; z < countbuf; z++ ) // รอบของ dataBuf
		{
			if(strcmp(word[x],dataBuf[z]) == 0)
			{
				dataBuf[z] = "";
				freq[z] = 0;
			} 
		} // for z
		cout << "\n";
	/* Print dataBuf freq */
	for ( z = 0; z < countbuf; z++ )
	{
		cout << setfill(' ') << "dataBuf["<<z<<"] = "<< dataBuf[z] << setw(15) << "freq["<<z<<"] = "<< freq[z] << "\n";
	}
	/* เก็บค่าเฉพาะที่ใช้ */
	char *tmpdata[sizebuf];
	int temfreq[sizebuf];
	x = 0;
	for ( z = 0; z < countbuf; z++ )
	{
		if(dataBuf[z] != "")
		{
			tmpdata[x] = dataBuf[z];
			temfreq[x] = freq[z];
			x++;
		}
	}
	/* Print dataBuf freq */
	cout<<endl;
	for ( z = 0; z < x; z++ )
	{
		cout << setfill(' ') << "dataBuf["<<z<<"] = "<< tmpdata[z] << setw(15) << "freq["<<z<<"] = "<< temfreq[z] << "\n";
	} 

	for ( z = 0; z < x; z++ )
	{
		if( strcmp(tmpdata[z],pat) == 0)
		{
			cout << "Found at " << tmpdata[z] << endl;
		}
	}
}