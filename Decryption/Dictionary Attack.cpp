
#include<set>
#include<iostream>
#include <iterator>
#include<string.h>
#include<fstream>
#include<sstream>
using namespace std;

int CheckWord(char* str, int b)  //function to check if word is in the dictionary
{
    ifstream file("C:\\Users\\Susmit\\Downloads\\words.txt");  //path reference to list of words

    char aWord[1024];
    while (file.good())
    {
        file>>aWord;
        if (file.good() && strcasecmp(aWord, str) == 0)
        {
        	b = 1;
            return b; //found word
        }
    }
    b=0;
    return b;
}

void DecipherText(string key)
{
	string str;
	ifstream infile;
	infile.open("C:\\Users\\Susmit\\Desktop\\CryptoTemplar3\\CipherText.txt");
	while(!infile.eof())
	{
		getline(infile,str);
	}
	infile.close();
	ofstream output;

	string final ;
	string decipher;


	while(str.length()>0)
	{
		string block = str.substr(0,7);
		str.erase(0,7);
		char blk[1024];
		strcpy(blk, block.c_str());
		char dcr[1024];
		dcr[0]=blk[key[0]];
		dcr[1]=blk[key[1]];
		dcr[2]=blk[key[2]];
		dcr[3]=blk[key[3]];
		dcr[4]=blk[key[4]];
		dcr[5]=blk[key[5]];
		dcr[6]=blk[key[6]];

		stringstream buffer;
		for(int i=0;i<7;i++)
		{
			buffer<<dcr[i];
		}
		decipher = buffer.str();
		final = final + decipher;

	}
	cout << final;
	output.open("C:\\Users\\Susmit\\Desktop\\CryptoTemplar3\\DecipheredText.txt",ios::app);
	output << final;
}

void FindKey(set<string> final)   //function to find key by comparing all high potential combinations with cipher
{
	for(set<string>::iterator i=final.begin(); i!=final.end(); i++)
    {
		string first = *i; //permutation of the first block that we assume is correct plain text
		string str;
		ifstream infile;
		infile.open("C:\\Users\\Susmit\\Desktop\\CryptoTemplar3\\CipherText.txt");
		while(!infile.eof())
		{
			getline(infile,str);  //gets cipher text into string
		}
		infile.close();
		ofstream output;

		string str_s = str.substr(0,7);  //first block of cipher text

		cout<<str_s<<endl;
		char arr[20];
		for(int i=0;i<first.length();i++)  //compare positions of letters of the permutation and original cipher block
		{
			int index = str_s.find(first[i]);
			arr[i]=index;
		}

		string block = str.substr(7,7);  //second block of cipher text
		char blk[1024];
		strcpy(blk, block.c_str());
		char dcr[1024];
		dcr[0]=blk[arr[0]];
		dcr[1]=blk[arr[1]];
		dcr[2]=blk[arr[2]];
		dcr[3]=blk[arr[3]];
		dcr[4]=blk[arr[4]];
		dcr[5]=blk[arr[5]];
		dcr[6]=blk[arr[6]];
		string second(dcr);  //second block deciphered using key dervived
		string key(arr);   //key is stored as string
		string text = first + second;

		cout<<text;   //first two blocks deciphered using key and shown to user
		cout<<"Does this look correct to you? [y/n]";
		string answer;
		cin>> answer;
		if(answer=="y")
			DecipherText(key);  //key is returned
		else if(answer=="n")
			continue;
	}

}


void swap(char& a, char& b)  //function to swap two characters
{
    char temp;
    temp = a;
    a = b;
    b = temp;
}

void Start_permutation(string s,int i,int n)  //function to obtain permutations of string characters
										//and filter out potential correct ones
{
	set<string> anagrams;
    int j;
    if (i == n)
    {

    	anagrams.insert(s);    //insert all possible permutations into a set


    }
    else
    {
        for (j = i; j < s.length(); j++)
        {
            swap(s[i],s[j]);
            Start_permutation(s, i + 1, n);
            swap(s[i],s[j]);
        }
    }
    int no=0;
    int pts;
    set<string> final;
    int b;
    for(set<string>::iterator i=anagrams.begin(); i!=anagrams.end(); i++)
        {
        	string sb= *i;

        	for(int k=no;k<sb.length();k++)   //iterates the chars in a word to compare partial strings to words
        	{
        		string sub = sb.substr(n,k);
        		char *sc;
        		strcpy(sc,sub.c_str());

        		CheckWord(sc,b);

        		if(b==0)
        		{
        			pts = sub.length() + pts;   //if string is a word, give points acc to length
        			no = no + k;
        		}
        	}
        	if(pts>5)   //only strings with max potential filtered out
        		final.insert(sb);
        }
    	FindKey(final);
}



int main()
{
	string str;
	ifstream infile;
	infile.open("C:\\Users\\Susmit\\Desktop\\CryptoTemplar3\\CipherText.txt");  //get ciphertext into a string
	while(!infile.eof())
	{
		getline(infile,str);
	}
	infile.close();
	string first_block = str.substr(0,7);   //first block used to find key

    Start_permutation(first_block, 0, first_block.length()-1);  //to find all permutations of first block
    cout<<endl<<"finished!!";

}


