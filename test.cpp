#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>


using namespace std;

/** 
*	@file test.cpp 
*	@brief This file will contain a vector sumation program
*	with multiple program options using the Boost Program_options
*	library.
*
*	@author		Felix Ducret
*
*	@date 4/10/2019
*/

/** 
*    This struct aims at returning both the bool that is used to see if the
*    user wants to calculate a vector sum and the length of the vectors he
*    wants to sum in case he uses the option "-l"
*    @author Felix Ducret
*    @date 04/11/2019
*/
struct ret{
	bool e;	/*!<Bool needed to see if the user wants to compute a sumation*/
	int l;	/*!<Used to return the length in the main function*/
};

/**
*	This method will be used to interpret the program options
*	going with the execution instructions
*	@author Felix Ducret
*	@param ac	The number of program options entered by the user
*	@param av	The table containing all program options entered by
*	the user
*	@return		A struct containing a bool to indicate if the user wants a calculation and an int to modify the size of the vectors if the user doesn't want to sum all the terms of the vectors
*	@date 4/10/2019
*/

ret prog_options(int ac, char* av[])
{
	namespace po = boost::program_options;
	
	ret result;	/*A ret that will return an instruction that the main function will execute */
	result.e = 0;	// Initialisation of both parameters of the result
	result.l=0;	// to 0. Default values are so interpreted as a 
			// calculation instruction (.e=0) that asks for the 
			// sum of the vectors in their entirety

	// Declare the supported options.

	po::options_description desc("Allowed options");	/*Options_description variable that will allow all the options specified below to have a meaning */
	desc.add_options()					// Adding of the options
    		("help", "produce help message")		// Help option to see all the possible program options
    		("length,l", po::value<int>(), "choose the length of vectors you want to sum")		// Length option to choose the size of the number of terms in the vector that will be sumed
	;

	po::variables_map vm;			/*Variables map to store the values of options*/
	po::store(po::parse_command_line(ac, av, desc), vm);

	po::notify(vm);    	// There, the values of options are effectively stored

	// Starts checking for the values of options in the vm
	if (vm.count("help")) {			
    		cout << desc << "\n";		// The user asks for the option help : prompt of the options_desciption
    		result.e = 1;			// No calculation resquested
	}//if

	if (vm.count("length")) {		// The user asks for the option length : he wants to change the number of terms that will be changed in the vector
    		result.l=vm["length"].as<int>();	// The new value is retieved by the .l value of the struct to be send to the main function
	}//if
    		
	
	return result;		// Info sent to the main function
}//prog_options


/**
*	This is a template for vectors sumation
*	@author Felix Ducret
*	@param a	First vector to be sumed
*	@param b	Second vector to be sumed
*	@param c	Third vector to be sumed
*	@return		Sum of the 3 vectors
*       @date 4/11/2019
*/
template <typename T>
vector<T> add(const vector<T> &a, const vector<T> &b, vector<T> &c)
{
	vector<T> sum;		/*Vector that will memorize the sum of the vectors */
	for(int i=0; i<a.size(); ++i)
   	{
       	sum.push_back(a[i]+b[i]+c[i]);		// The terms of the vectors are sumed according to their index
   	}

 	return sum;
}

vector<double> vector_file(string addr, int l)
{
	ifstream File(addr.c_str());
	vector<double> vect;
	if(File)
	{
		string number;
		if(l!=0)
		{
			for(int j=0; j<l; j++)
			{
				File >> number;
				vect.push_back(atof(number.c_str()));
			}
		}
		else
		{
			while(getline(File, number))
			{
				vect.push_back(atof(number.c_str()));
			}
		}
	}
	else
	{
		cout << "ERROR : The file can't be read" << endl;
	}
	return vect;
}

/**
*	Main function : chooses which elements to prompt 
*	@author Felix Ducret
*	@param ac       Number of arguments when the program is executed
*	@param av       Table containing all the execution arguments
*	@return         int that indicates if there was an error at some point
*	@date 4/11/2019
*/

int main(int ac, char* av[])
{
	ret s=prog_options(ac, av);	/*Call to the function that will parse the options input by the user */

	// If calulation is requested
	if(s.e==0)
	{	
		string addr1="numbers1.txt";
		string addr2="numbers2.txt";
		string addr3="numbers3.txt";

		vector<double> vec1=vector_file(addr1, 0);	

		// If the user asks for more terms than there are in the vectors, prompt of an error message
		if(s.l>vec1.size())
        	{
                	cout << "Vectors too short, last elements are not defined" << endl;
			s.l=0;
        	}//if	
		

		else
		{	
			vector<double> vec1=vector_file(addr1, s.l);	/*First vector that will be sumed */
			vector<double> vec2=vector_file(addr2, s.l);	/*Second vector that will be sumed */
			vector<double> vec3=vector_file(addr3, s.l);	/*Third vector that will be sumed */

			vector<double> S=add(vec1, vec2, vec3);
			for(int i=0; i<vec1.size(); i++)
			{
				cout << S[i] << endl;
			}
		}//else1
	}//if
	return 0;

}//main


