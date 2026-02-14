#include "Exception.hpp"
#include <sstream>

ExceptionPerror::ExceptionPerror(const char* err, const char* file, const char* func, int line)
:
	_message(err),
	_file(file),
	_func(func),
	_line(line)
{
	std::ostringstream oss;
	
	oss << "Error: " << _message << " (in " << _func << " at " << _file << ":" << _line << ")";
	_exception_msg = oss.str();
}

ExceptionPerror::~ExceptionPerror() throw()
{}

const char* ExceptionPerror::what() const throw()
{
	return _exception_msg.c_str();
}
