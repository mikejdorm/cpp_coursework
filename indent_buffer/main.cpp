#include "IndentBuffer.h"
/*
	M.Dorman Feb 28, 2012
*/
using namespace std;

int main()
{
IndentBuffer ib(cout);	std::ostream ins(&ib);

//Output from lecture slide:
ins << "int" << endl;
ins << "fib(int n) {" << indent << endl;
ins << "if (n == 0) " << indent << endl;
ins << "return 0;" << unindent << endl;
ins << "if (n == 1) " << indent << endl;
ins << "return 1;" << unindent << endl;
ins << "return fib(n-2) + fib(n-1);" << unindent << endl;
ins << "}" << endl;

return 0;
}