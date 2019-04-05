#include <iostream>
#include <string>
using namespace std;

int main(void)
{
	string word1("abc");
	string word2("bcd");
	bool test_unit = true;
	
	for(int i=0;i<word1.size();++i)
	{
		if(word1[i]!=word2[i])
		{
			test_unit=false;
			break;
		}
	}
	
	std::cout << test_unit << std::endl;

}//main

