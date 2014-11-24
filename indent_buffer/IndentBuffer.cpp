// IndentBuffer.cpp : Defines the entry point for the console application.
//

/*
	M.Dorman Feb 28, 2012
*/

#include "stdafx.h"
#include "IndentBuffer.h"
#include <string.h>

IndentBuffer::IndentBuffer(std::ostream &str): stream(str), my_buffer(BUFFER_SZ){
	char *p_base = &my_buffer.front();
    setp(p_base, p_base + my_buffer.size());
}
IndentStream::IndentStream(std::ostream &str):std::ostream(&buffer),buffer(str){}

IndentBuffer::int_type IndentBuffer::overflow(int_type c)
{
    if (stream!=NULL && c!=EOF){
		*pptr() = c;
        pbump(1);
        return c;
    }
    return EOF;
}

 std::ostream &indent(std::ostream &os){
	 indent_count++;
	 return os;
 }

 std::ostream &unindent(std::ostream &os){
	 if(indent_count>0)
		 indent_count--;
	 return os;
 }

int IndentBuffer::sync ( )
{
	int l_indent = indent_count*4;
	for(int i = 0; i< l_indent; i++){
				stream << " ";
	}
	return flush_ibuffer() ? 0 : -1;
}

bool IndentBuffer::flush_ibuffer(){
	std::ptrdiff_t p_diff = pptr() - pbase();
	pbump((p_diff*-1));
    return stream.write(pbase(), p_diff);
}