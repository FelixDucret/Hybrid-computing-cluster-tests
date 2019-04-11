#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>
#include <vector>

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
*	@param l	Int equal to the number of terms we'll calculate
*	@return		Sum of the 3 vectors
*       @date 4/11/2019
*/
template <typename T>
vector<T> add(const vector<T> &a, const vector<T> &b, vector<T> &c, int l)
{
	vector<T> sum;		/*Vector that will memorize the sum of the vectors */
        // Vectors can't be sumed if they have different lengths 
	if(a.size()!=b.size()||b.size()!=c.size())
        {
              cout << "Vectors can't be sumed : different lengths" << endl;	// An error message is prompted
              return sum;		// The calculation stops here
        }
	else
 	{
		for(int i=0; i<a.size(); ++i)
        	{
                	sum.push_back(a[i]+b[i]+c[i]);		// The terms of the vectors are sumed according to their index
        	}
	}
 	return sum;
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

	vector<int>vec1 (50,2);	/*The vectors that will be sumed */
	vector<int>vec2 (50,3);  
	vector<int>vec3 (50,4);  
	
	// If calulation is requested
	if(s.e==0)
	{	
		// If the user asks for more terms than there are in the vectors, prompt of an error message
		if(s.l>vec1.size())
        	{
                	cout << "Vectors too short, last elements are not defined" << endl;
        	}//if

		else
		{	
			//Length argument taken into account : l first terms of the sum will be prompted 
			if(s.l!=0)
        		{
        			for(int i=0; i<s.l; i++)
        	        		{	
						vector<int> S = add(vec1,vec2,vec3,s.l);	/*Call to the sumation function */
        	        			cout << S[i] << endl;
        	        		}//for
        		}//if
			// If no length argument : all the terms of the sum are prompted
        		else{
        			for(int i=0; i<vec1.size(); i++)
        			{	
					vector<int> S = add(vec1,vec2,vec3,vec1.size());	/*Call to the sumation function */
        	    			cout << S[i] << endl;
        			}//for
        		}//else2
		}//else1
	}//if
	return 0;

}//main


