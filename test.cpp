#include <iostream>
#include <cmath>


using namespace std;

template <typename T>
T maximum(const T& a, const T& b)
{
	if(a>b)
		return a;
	else
		return b;
}

int main(void)
{
	float a = M_PI;
	float b = M_E;
	std::cout << maximum(a,b) << std::endl;

}//main

