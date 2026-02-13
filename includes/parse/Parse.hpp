#ifndef PARSE_HPP
#define PARSE_HPP

#include <vector>
#include <iostream>
#include <iomanip>
#include "Irc.hpp"

class Parse {

	private:
		std::string _rawValue;

	public:
		Parse(std::string rawValue);
		~Parse();

		std::vector<std::vector<std::string> >	parseCommand();
		// void	display_vec(std::vector<std::vector<std::string> > val);
};

#endif