#include<iostream>
#include<string>
#include <sstream>
using namespace std;
string toString(int n)
{ 
	stringstream ss;
	ss << n;
	return ss.str();
}
void print(char pat[]);

void main(int argc , char *argv[])
{
	char   buf[2048];
	char   pat[2048];					// ตัวแปร pat เก๊บอักษรได้ 50 ตัว : A--G
	string conv		 = "";				// เก็บค่า convert code
	string samenum   = "";
	string tmppat	 = "";				// เก็บ					   : AG
	string adj		 = "";				// เก็บคำที่ตัดคำซ้ำ
	string soundex   = "";

	string nchar_1   = "BPFV";
	string nchar_2   = "CSKGJQXZ";
	string nchar_3   = "DT";
	string nchar_4   = "L";
	string nchar_5   = "MN";
	string nchar_6   = "R";
	string aeiou_yhw = "AEIOUYHW"; 
	
	cout << "Enter word :";
	cin.getline(buf,2048);				// รับค่าทั้งแถว max : 2048  แบบ char
	int c = cin.gcount()-1;				// นับตัวอักษรที่รับมา
	cout << "count : " << c << "\n\n";
	cin.clear();

	//switch(argc)
	//{
	//	case 2 : strcpy(buf,argv[1]); break;
	//	default : cout << "Please enter word" << endl;
	//		return;
	//}// switch

	int i,n;				// ตัวแปรร่วม
	/* To Upper */			// แปลงให้เป็นตัวใหญ่
	cout << "Word : ";
	for( i = 0; i < strlen(buf); i++ ){
		if( towlower( buf[ i ] ) ){
			buf[i] = toupper( buf[i] );
			cout << buf[ i ];
		} // if tolower
	}// for i = 0
	cout << endl;

	/* Cut AEIOU and YHW */
	cout << "1.Cut AEIOU and YHW : ";
	strcpy(pat,buf);                        
	for( i = 1; i < strlen(buf);i++)
	{  
		for(n = 0; n < aeiou_yhw.length(); n++)
		{ 
			if(buf[ i ] == aeiou_yhw[ n ]) {           // char != string.c_str()
				pat[i] = '-';
			}
		}	// for buf[ i ]  
	} // for i =1
		     
	/* Cut - ออก */ 
	for(i = 0; i < strlen(pat);i++)
	{ 
		if(pat[i] != '-') {           
			tmppat += pat[i];
		}
		cout << pat[i];
	} // for i = 0
	//cout << tmppat << endl;						// Print string ที่ตัด - ออกแล้ว
	cout << endl;

	/* Cut adjacent character : ตัดตัวที่ซ้ำเอาแค่ตัวเดียว */ 
	cout << "2.Cut adjacent character : "; 
	int j = 0;											// ตัวชี้ตำแหน่งที่ไม่ซ้ำ
	//adj[0] = tmppat[0]; 
	for(i = 1; i < tmppat.length(); i++){ 
		if(tmppat[j] != tmppat[ i ]) {
			adj += tmppat.at(j);  
			j = i; 
		}  // if tmppat
		if(i == tmppat.length()-1) adj += tmppat.at(j);		// เพื่อให้เก็บ อักษรตัวสุดท้ายตาม ตำแหน่ง j
	} // for i = 1
	cout << adj << endl;

	/* Convert to numberic code ใส่รหัสตัวเลข */
	cout << "3.Convert to numeric code : ";
	int n1,n2,n3,n5;
	int found = 0;			        	// ถ้าเจอเแล้วไม่ให้ค้นหาอีก 
	int found_yhw_aeiou = 0;    // ถ้าเจอให้ ค่า เป็น 1 

	for( i = 0; i < adj.length(); i++)		// วน check ตามความยาวของ string เพื่อแปลงเป็น เลข 
	{
		if( found == 0 )						// เช็คเพื่อไม่ให้ไปทำ for ที่ ไม่พบตัวอักษร
		{
			for( n1 = 0; n1 < nchar_1.length(); n1++ )
			{
				if( adj[ i ] == nchar_1[n1] )
				{ 
					conv += '1';						// แทนค่า code Number ของตัวอักษร
					n1 = nchar_1.length();
					found = 1;
				}	// id adj
			}	// if found == 0
		}// for i
		if( found == 0 )
		{
			for( n2 = 0; n2 < nchar_2.length(); n2++ )
			{
				if( adj[ i ] == nchar_2[n2] )
				{
					conv += '2';
					n2 = nchar_2.length();
					found = 1;
				}	// if adj
			}	// for n2
		}// if found ==0
		if( found == 0 )
		{
			for( n3 = 0; n3 < nchar_3.length(); n3++ )
			{
				if(adj[ i ] == nchar_3[n3])
				{
					conv += '3';
					n3 = nchar_3.length();		// ทำให้ หลุด Loop เมื่อเจอแล้ว
					found = 1;
				}	// if adj 
			}	 // for n3 
		}// if found ==0
		if( found == 0 )
		{
			if(adj[ i ] == nchar_4[0])
			{
				conv += '4'; 
				found = 1;
			}	// if adj
		}// if found ==0
		if( found == 0 )
		{
			for(n5 = 0; n5 < nchar_5.length(); n5++) // ค้นหา
			{
				if(adj[ i ] == nchar_5[n5])
				{
					conv += '5';
					n5 = nchar_5.length();			// ทำให้ หลุด Loop เมื่อเจอแล้ว
					found = 1;
				}	// if adj
			}	// for n5
		}// if found ==0
		if( found == 0 )
		{
			if(adj[ i ] == nchar_6[0])
			{
				conv += '6'; 
				found = 1;
			}	// if adj 
		}// if found ==0

		if ( i == 0 && found == 0 ) {   // check ว่าตัวแรกเป็น YHWAEIOU มั้ย
			conv = adj[0];
			found_yhw_aeiou = 1;		// ถ้าเจอให้ค่าเป็น 1 
		}// if found ==0

		found = 0;						// กำหนดค่าเริ่มต้นให้ใหม่

	}	//  for i = 0
	cout << adj[0] << conv.substr(1) << endl; // เอา มาแสดง โดย เอามาต่อกัน
	
	/* Cut the same numeric code */        	 // ตัดรหัสตัวเลขเดียวกัน
	cout << "4.Cut the same numeric code : ";
	j = 0; 
	found = 1;
	int level = 0;
	string cuttmp = "";
	for( i = 1; i < conv.length(); i++)   	 // ค้นหาตัวเลขที่เหมือนกัน 
	{ 
		if(level == 0){                 
			if(conv[ j ] == conv[ i ]) {  	 // ตรวจสอบว่าตัวแรกกับตัวที่ 2,3.. เท่ากันมั้ย
				j = i;
				found++; 
			} //	if conv
		}// if level
		if(conv[ j ] != conv[ i ]){          // เก็บตัวที่ไม่ซ้ำใน cuttmp โดยการแลือกมา 1 ตัวจากตัวที่ซ้ำ
			level = 1;
			cuttmp += conv.at( j );			 // เอาตำแหน่งที่ เจอ มาเก็บไว้ที่ cuttmp
			j = i;
		} // if conv[ j ]
		if(i == conv.length()-1) cuttmp += conv.at( j );    // เพื่อให้เก็บ อักษรตัวสุดท้ายตาม ตำแหน่ง j
	}  // for i = 1 

	if(found_yhw_aeiou == 0){				 // แสดงว่าตัวแรก*ไม่เป็น AEIOUYHW
		samenum = adj[0];
		samenum += cuttmp.substr(1);	     // ตัดเอาตัวเลขตัวแรกออก เพื่อต่อกับตัว อักษรของตัวเลข ตัวที่เอาออก 
	} // found_yhw_aeiou == 0
	else if(found_yhw_aeiou == 1)			 // แสดงว่าตัวแรก*เป็น AEIOUYHW
	{
		samenum = cuttmp; 
	} // else if found_yhw_aeiou = 1
		cout << samenum << endl;			 // print

	/* Add Zero */            				// เพิ่ม 0 ถ้ามีหลักไม่ครบ
	cout << "5.Add Zero : ";
	if( samenum.length() <= 3 )
	{
		for( i = samenum.length(); i < 4; i++)
		{
			samenum += "0";
		} // for i = samenum.length()
	} // if samenum.length
	cout << samenum << endl;

	/* Soundex Code */
	soundex = samenum.substr(0,4);      // ตัด soundex มา 4 ตัว
	cout << "\nOutput Soundex Code : " << soundex << endl;
	system("pause");
}
void print(char pat[])
{
	cout << " : " << pat << endl;		// pat เป็น char สามารถแสดงแบบนี้ไดเเลย ไม่ต้องวน loop
}