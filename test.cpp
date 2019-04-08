#include <iostream>
#include <vector>

using namespace std;
 

vector<int> sum_vectors(vector<int> vec1, vector<int> vec2)
 {
	vector<int> sum;
	if(vec1.size()!=vec2.size())
	{
		cout << "Vectors can't be sumed : different lengths" << endl;
		return  sum;
	}	
	for(int i=0; i<vec1.size(); ++i)
 	{
		sum.push_back(vec1[i]+vec2[i]);
 	}
	return sum;
}
 

int main(void)
{
	vector<int> vec1(4,2);
	vector<int> vec2(5,3);

	vector<int> S=sum_vectors(vec1,vec2);
	
	for(int i=0; i<S.size(); i++)
	{	
		cout << S[i] << endl;
	}

}//main

