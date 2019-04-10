#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

struct ret{
	bool e;	//Error bool
	int l;	//Used to return the length in the main function
};

ret prog_options(int ac, char* av[])
{
	namespace po = boost::program_options;
	
	ret result;
	//Error bool
	result.e = 0;
	result.l=0;

	// Declare the supported options.

	po::options_description desc("Allowed options");
	desc.add_options()
    		("help", "produce help message")
    		("length", po::value<int>(), "choose the length of vectors you want to sum")
	;
//	po::positional_options_description p;

//	p.add("length", -l);

	po::variables_map vm;
	po::store(po::parse_command_line(ac, av, desc), vm);
		 // options(desc).positional(p).run()


	po::notify(vm);    

	if (vm.count("help")) {
    		cout << desc << "\n";
    		result.e = 1;
	}//if

	if (vm.count("length")) {
    		result.l=vm["length"].as<int>();
	}//if
    		
	
	return result;
}//prog_options

//Template for vectors sumation
template <typename T>
vector<T> add(const vector<T> &a, const vector<T> &b, vector<T> &c)
{
	vector<T> sum;
        if(a.size()!=b.size()||b.size()!=c.size())
        {
              cout << "Vectors can't be sumed : different lengths" << endl;
              return sum;
        }
	else
 	{
		for(int i=0; i<a.size(); ++i)
        	{
                	sum.push_back(a[i]+b[i]+c[i]);
        	}
	}
 	return sum;
}

int main(int ac, char* av[])
{
	ret s=prog_options(ac, av);

	vector<int>vec1 (5,2);
	vector<int>vec2 (5,3);
	vector<int>vec3 (5,4);
	
	vector<int> S = add(vec1,vec2,vec3);
	if(s.e==0)
	{
		if(s.l>vec1.size())
        	{
                	cout << "Vectors too short, last elements are not defined" << endl;
        	}//if

		else
		{
			if(s.l!=0)
        		{
        			for(int i=0; i<s.l; i++)
        	        		{	
        	        			cout << S[i] << endl;
        	        		}//for
        		}//if
        		else{
        			for(int i=0; i<S.size(); i++)
        			{	
        	    			cout << S[i] << endl;
        			}//for
        		}//else2
		}//else1
	}//if
	return s.e;

}//main
