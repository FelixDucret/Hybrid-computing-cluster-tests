#include <iostream>
#include <vector>
#include <error.h>
#include <argp.h>

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
    	int j;
    	sscanf(arg.c_str(), "%d", &j);
    	arguments->size=j;
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }//switch
  return 0;
}//parse_option


void print_args(struct arguments *p_arguments)
{
   printf (".size=%d\n"
  , p_arguments->size
  );
}//print_args

//! [argp] setup argp parser
static struct argp argp = { options, parse_option, args_doc, doc };

//}argp



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
        //CLI arguments
        struct arguments arguments;
        arguments.size=10;

        printf("command line option values:\n");
        print_args(&arguments);

        int L=arguments.size;
        vector<int> vec1(4,2);
        vector<int> vec2(5,3);

        vector<int> S=sum_vectors(vec1,vec2);
        
        if(L!=0)
        {
        	for(int i=0; i<L; i++)
        	        {	
        	        	cout << S[i] << endl;
        	        }
        }
        else{
        	for(int i=0; i<S.size(); i++)
        	{	
        	    	cout << S[i] << endl;
        	}
        }
        

        return 0;

}//main

