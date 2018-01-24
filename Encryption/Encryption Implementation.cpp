#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <string>

using namespace std;

int main ()
{
    string str;
	ifstream infile;
	infile.open("C:\\Users\\Susmit\\Desktop\\CryptoTemplar3\\Actual_text.txt"); //Plain text obtained by running decryption algorithm and adding spaces
        while(!infile.eof())
        {
	        getline(infile,str);
        }
	infile.close();
	ofstream output;
	for(int j=0; j < str.length(); j++)
	{
		if(str[j]==' ')
			str.erase(j,1);
	}

	string final ;
	string decipher;
	string str_s = str.substr(0,7);


	while(str.length()>0)
	{
		string block = str.substr(0,7);
		str.erase(0,7);
		char blk[1024];
		strcpy(blk, block.c_str());
		char encr[1024];
		encr[0]=blk[4]; //Key applied and transposition initiated
		encr[1]=blk[2];
		encr[2]=blk[5];
		encr[3]=blk[6];
		encr[4]=blk[1];
		encr[5]=blk[3];
		encr[6]=blk[0];

		stringstream buffer;
		for(int i=0;i<7;i++)
		{
			buffer<<encr[i];
		}
		decipher = buffer.str();
		final = final + decipher;

	}
	cout << final;  //display encrypted text
	output.open("C:\\Users\\Susmit\\Desktop\\CryptoTemplar3\\encrypted.txt",ios::app);  //save to file as well
	output << final;

}
