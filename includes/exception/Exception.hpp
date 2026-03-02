#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

# include <cstring>
# include <errno.h>
# include <string>

# define ERR_MSG std::strerror(errno), __FILE__, __FUNCTION__, __LINE__

class ExceptionPerror : public std::exception
{
	private:
		std::string _message;
		std::string _file;
		std::string _func;
		int _line;
		std::string _exception_msg;

	public: 

		ExceptionPerror(const char* err, const char* file, const char* func, int line);
		virtual ~ExceptionPerror() throw();

		virtual const char* what() const throw();
};

#endif
