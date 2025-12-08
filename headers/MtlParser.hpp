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
		void	ParseColor(std::istringstream& ss, std::string statement, ParsedColor& color);
		void	SetIllumModel(std::istringstream& ss);
		void	SetDisolve(std::istringstream& ss);
		void	SetShininess(std::istringstream& ss);
		void	SetSharpness(std::istringstream& ss);
		void	SetRefractiveIndex(std::istringstream& ss);

		void	ParseFile(std::ifstream& ifs);

	public:
		static MaterialList	ImportMtl(std::string filename);

};

#endif // !MTL_PARSER_HPP
