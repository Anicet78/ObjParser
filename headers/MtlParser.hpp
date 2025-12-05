#ifndef MTL_PARSER_HPP
# define MTL_PARSER_HPP

# include "parser.hpp"
# include "Material.hpp"

typedef std::unordered_map<std::string, Material> MaterialList;

class MtlParser {

	private:
		MtlParser(void);

		std::string	fileName;
		size_t		countLines;

		std::string		currentMaterial;
		MaterialList	materials;

		void	NewMaterial(std::istringstream& ss);

		void	ParseFile(std::ifstream& ifs);

	public:
		static MaterialList	ImportMtl(std::string filename);

};

#endif // !MTL_PARSER_HPP
