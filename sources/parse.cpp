#include <vector>
#include <iostream>
#include <iomanip>

#define BOLD_GREEN "\e[1;32m"
#define BOLD_RED "\e[1;31m"
#define BOLD_BLUE "\e[1;34m"
#define BOLD_YELLOW "\e[1;33m"
#define BOLD_PURPLE "\e[1;35m"
#define BOLD_CYAN "\e[1;36m"
#define STOP_COLOR "\e[0m"



std::vector<std::vector<std::string> >	parseCommand(std::string raw_value)
{
	std::vector<std::vector<std::string> > result;
	size_t start = 0;

	while (start < raw_value.size())
	{
		size_t end_line = raw_value.find("\r\n", start);
		if (end_line == std::string::npos)
			end_line = raw_value.size();

		std::vector<std::string> words;
		size_t word_start = start;

		while (word_start < end_line)
		{
			while (word_start < end_line && raw_value[word_start] == ' ')
				word_start++;

			if (word_start >= end_line)
				break;

			size_t word_end = raw_value.find(' ', word_start);
			if (word_end == std::string::npos || word_end > end_line)
				word_end = end_line;
			if ((words.size() > 0 && words[0] == "PASS") || raw_value[word_start] == ':')
			{
				word_end = raw_value.find("\r\n", word_start);
				words.push_back(raw_value.substr(word_start, word_end  - word_start));
			}
			else
				words.push_back(raw_value.substr(word_start, word_end - word_start));
			word_start = word_end;
		}
		result.push_back(words);
		start = end_line + 2;
	}
	return result;
}

void	display_vec(std::vector<std::vector<std::string> > val)
{
	for (size_t i = 0; i < val.size(); i++)
	{
		if (val.size() == 1 || i == val.size() / 2)
			std::cout << BOLD_BLUE "VEC --->" << BOLD_CYAN << "|Sub Vector --->" STOP_COLOR;
		else
			std::cout << std::setw(15) << BOLD_CYAN << "|Sub Vector --->";
		for (size_t j = 0; j < val[i].size(); j++)
		{
			std::cout << BOLD_YELLOW "[" << val[i][j] << "]" STOP_COLOR;
		}
		std::cout << '\n';
	}
}

int	main()
{
	display_vec(parseCommand("PASS aklejfa akjefak sdh      dsd\r\nQUIT chan\r\n PRIVMSG user :coucou ca va ?\r\n"));
	return 0;
}
