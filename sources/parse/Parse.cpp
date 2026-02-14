#include <iomanip>
#include <iostream>
#include "Irc.hpp"
#include "Parse.hpp"

Parse::Parse(std::string rawValue)
:
	_rawValue(rawValue)
{}

Parse::~Parse()
{}

std::vector<std::vector<std::string> >	Parse::parseCommand()
{
	std::vector<std::vector<std::string> > result;
	size_t start = 0;

	while (start < _rawValue.size())
	{
		size_t end_line = _rawValue.find("\r\n", start);
		if (end_line == std::string::npos)
			end_line = _rawValue.size();

		std::vector<std::string> words;
		size_t word_start = start;

		while (word_start < end_line)
		{
			while (word_start < end_line && _rawValue[word_start] == ' ')
				word_start++;

			if (word_start >= end_line)
				break;

			size_t word_end = _rawValue.find(' ', word_start);
			if (word_end == std::string::npos || word_end > end_line)
				word_end = end_line;
			if (_rawValue[word_start] != ':')
				words.push_back(_rawValue.substr(word_start, word_end - word_start));
			else
			{
				word_end = _rawValue.find("\r\n", word_start);
				words.push_back(_rawValue.substr(word_start, word_end  - word_start));
			}
			word_start = word_end;
		}
		result.push_back(words);
		start = end_line + 2;
	}
	return result;
}

void	Parse::display_vec(std::vector<std::vector<std::string> > val)
{
	for (size_t i = 0; i < val.size(); i++)
	{
		if (val.size() == 1 || i == val.size() / 2)
			std::cout << ircMacro::BOLD_BLUE << "VEC --->" << ircMacro::BOLD_CYAN << "|Sub Vector --->" << ircMacro::STOP_COLOR;

		else
			std::cout << std::setw(15) << ircMacro::BOLD_CYAN << "|Sub Vector --->";

		for (size_t j = 0; j < val[i].size(); j++)
		{
			std::cout << ircMacro::BOLD_YELLOW << "[" << val[i][j] << "]" << ircMacro::STOP_COLOR;
		}
		std::cout << '\n';
	}
}
