#ifndef MTL_PARSER_HPP
# define MTL_PARSER_HPP

# include "parser.hpp"
# include "Material.hpp"

class MtlParser {

	private:
		MtlParser(void);
		size_t	countLines;

	public:
		static void	ParseFile(std::string filename);

};

#endif // !MTL_PARSER_HPP
