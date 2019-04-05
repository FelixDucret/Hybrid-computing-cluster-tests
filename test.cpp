#include <iostream>
#include <string>
using namespace std;

int main(void)
{
	string mot1("abc");
	string mot2("bcd");
	bool test_unit = true;
	
	for(int i=0;i<mot1.size();++i)
	{
		if(mot1[i]!=mot2[i])
		{
			test_unit=false;
			break;
		}
	}
	
	std::cout << test_unit << std::endl;

}//main

