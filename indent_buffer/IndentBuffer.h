
/*
	M.Dorman Feb 28, 2012
*/

#include <vector>
#include <streambuf>
#include <iostream>

static int BUFFER_SZ = 256;
static int indent_count = 0;

class IndentBuffer : public std::streambuf
{
		public:
			IndentBuffer(std::ostream &str);
		private:
			int sync ();
			bool flush_ibuffer();
			int_type overflow(int_type ch);
			std::ostream &stream;
			std::vector<char> my_buffer;
};

class IndentStream : public std::ostream
{
public:
	IndentStream(std::ostream &str);
	IndentBuffer buffer;
};

std::ostream &indent(std::ostream &os);
std::ostream &unindent(std::ostream &os);