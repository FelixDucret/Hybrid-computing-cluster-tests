#include <iostream>
#include <vector>
#include <cmath>


int main(void)
{
	std::vector<float> vector1(3,M_PI);
	std::vector<float> vector2(3,M_E);
	bool test_unit = true;
	
	for(int i=0;i<vector1.size();++i)
	{
		if(vector1[i]!=vector2[i])
		{
			test_unit=false;
			break;
		}
	}
	
	std::cout << test_unit << std::endl;

}//main

