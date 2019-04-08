#include <iostream>
#include <vector>
#include <error.h>
#include <argp.h>
#include <cstdlib>

using namespace std;

#define VERSION "v0.0.0"

const char *argp_program_version=VERSION;

const char *argp_program_bug_adress="ducretf@ganil.fr";

static char doc[]=
	"Test_sum: vectors sumation program with CLI-defined sizes\
\n  ArgParse."VERSION"\\n\examples:\n\test --help\n\test -l 1000\n\\";

//! [argp] A description of the arguments
static char args_doc[] = "-l: size of the vectors you want to sum";

//! [argp] The options and its description
static struct argp_option options[]=
{
  {"size",  'l', "VALUE", 0,           "length of the sumed vectors"
  },
//default options
  { 0 }

};//options (CLI)

//! [argp] Used by main to communicate with parse_option
struct arguments
{
  //! size value
  int size;
};//arguments (CLI)

//! [argp] Parse a single option
static error_t parse_option(int key, char *arg, struct argp_state *state)
{
  //Get the input argument from argp_parse
  struct arguments *arguments=(struct arguments *)(state->input);
  switch (key)
  {
    case 'l':
    	arguments->size=atoi(arg);
    	break;
    default:
      return ARGP_ERR_UNKNOWN;
  }//switch
  return 0;
}//parse_option


void print_args(struct arguments *p_arguments)
{
   cout << "Size = " << p_arguments->size << endl << endl ;
  ;
}//print_args

//! [argp] setup argp parser
static struct argp argp = { options, parse_option, args_doc, doc };

//}argp


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
	
}//template


int main(int argc, char ** argv)
{
        //CLI arguments
        struct arguments arguments;
        arguments.size=0;

        cout << "command line option values:" << endl;
        print_args(&arguments);
        
        //! - Parse arguments (see parse_option) and eventually show$
        argp_parse(&argp, argc, argv, 0, 0, &arguments);


        int L=arguments.size;
        //cout << "L : " << L << endl;

	//ints
        vector<int> veci1(5,2);
        vector<int> veci2(5,3);
	vector<int> veci3(5,4);

        vector<int> Si=add(veci1,veci2,veci3);
        
        if(L>veci1.size())
        {
        	cout << "Vectors too short, last elements are not defined" << endl;
        }//if
        else
        {
        	if(L!=0)
        	{
        	  	for(int i=0; i<L; i++)
        	    {	
        	      	cout << Si[i] << endl;
        	    }//for
        	}//if
        	else
        	{
        	   	for(int i=0; i<Si.size(); i++)
        	   	{	
        	   		cout << Si[i] << endl;
        	    }//for
        	}//else2
        }//else1

	
	//floats
	vector<float> vecf1(5,2.3);
        vector<float> vecf2(5,3.4);
        vector<float> vecf3(5,4.5);

        vector<float> Sf=add(vecf1,vecf2,vecf3);
	
        if(L>vecf1.size())
        {
                cout << "Vectors too short, last elements are not defined" << endl;
        }//if
	else
	{
                if(L!=0)
                {
                        for(int i=0; i<L; i++)
                    {
                     	cout << Sf[i] << endl;
                    }//for
                }//if
                else
                {
                        for(int i=0; i<Sf.size(); i++)
                        {
                                cout << Sf[i] << endl;
                    }//for
                }//else2
        }//else1


        return 0;

}//main

