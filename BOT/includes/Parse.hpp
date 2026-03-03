#ifndef PARSE_HPP
#define PARSE_HPP

# include <vector>
# include <string>

class Parse {

	private:
		std::string _rawValue;

	public:
		Parse(const std::string& rawValue);
		~Parse();

		std::vector<std::vector<std::string> >	parseCommand();
		void	display_vec(const std::vector<std::vector<std::string> >& val);
};

#endif
