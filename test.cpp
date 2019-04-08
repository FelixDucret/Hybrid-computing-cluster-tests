#include <iostream>
#include <vector>

using namespace std;
 

vector<int> sum_vectors(vector<int> vec1, vector<int> vec2)
 {
	vector<int> sum(vec1.size());
	if(vec1.size()!=vec2.size())
	{
		printf("Vectors can't be sumed : different lengths\n);
		return  sum;
	}	
	for(int i=0; i<vec1.size(); i++)
 	{
		sum.push_back(vec1[i]+vec2[i]);
 	}
	

	return sum;
}
 

int main(void)
{
	vector<int> vec1(5,2);
	vector<int> vec2(5,3);
	
	cout << sum_vectors(vec1,vec2) << endl;

}//main

