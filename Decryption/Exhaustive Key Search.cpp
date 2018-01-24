
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>

using namespace std;

int main ()
{
    string str;
	ifstream infile;
	infile.open("C:\\Users\\Susmit\\Desktop\\CryptoTemplar3\\CipherText.txt");
        while(!infile.eof())
        {
	        getline(infile,str);  //Cipher text put in a string
        }
	infile.close();
	ofstream output;

	string final ;
	string decipher;
	string str_s = str.substr(0,7);  //first block of cipher text

	string input="Todayon";   //hard coded answer given. Semantic approach used in Dictionary Attack
	int arr[20];
	for(int i=0;i<input.length();i++)
	{
		if(i==1)
			arr[i]=4;
		else
		{
			int index = str_s.find(input[i]);  //index positions of characters searched throughout block
			arr[i]=index;
		}
	}

	while(str.length()>0)
	{
		string block = str.substr(0,7);
		str.erase(0,7);
		char blk[1024];
		strcpy(blk, block.c_str());
		char dcr[1024];
		dcr[0]=blk[arr[0]];    //Key applied and decryption initiated
		dcr[1]=blk[arr[1]];
		dcr[2]=blk[arr[2]];
		dcr[3]=blk[arr[3]];
		dcr[4]=blk[arr[4]];
		dcr[5]=blk[arr[5]];
		dcr[6]=blk[arr[6]];

		stringstream buffer;
		for(int i=0;i<7;i++)
		{
			buffer<<dcr[i];
		}
		decipher = buffer.str();
		final = final + decipher;

	}
	cout << final;  //deciphered text displayed
	output.open("C:\\Users\\Susmit\\Desktop\\CryptoTemplar3\\DecipheredText.txt",ios::app);  //deciphered text stored in file
	output << final;

}

