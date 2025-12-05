#ifndef MTL_PARSER_HPP
# define MTL_PARSER_HPP

# include "parser.hpp"
# include "Material.hpp"

typedef std::unordered_map<uint32_t, Material> MaterialList;

class MtlParser {

	private:
		MtlParser(void);
		size_t	countLines;

	public:
		static MaterialList	MtlParser::ImportMtl(std::string filename);

};

#endif // !MTL_PARSER_HPP
