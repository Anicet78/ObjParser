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
		void	SetDissolve(std::istringstream& ss, bool needInversion);
		void	SetShininess(std::istringstream& ss);
		void	SetSharpness(std::istringstream& ss);
		void	SetRefractiveIndex(std::istringstream& ss);

		bool	ParseOnOff(std::istringstream& ss, std::string& option, std::string& statement);
		void	SetBumpMultiplier(std::istringstream& ss, TextureMap& map, std::string& option, std::string& statement);
		void	SetImageChan(std::istringstream& ss, TextureMap& map, std::string& option, std::string& statement);
		void	SetBoost(std::istringstream& ss, TextureMap& map, std::string& option, std::string& statement);
		void	SetMapModifiers(std::istringstream& ss, TextureMap& map, std::string& option, std::string& statement);
		void	ParseOST(std::istringstream& ss, vec3& vec, std::string& option, std::string& statement);
		void	SetResolution(std::istringstream& ss, TextureMap& map, std::string& option, std::string& statement);
		void	ParseMapOptions(std::string& option, std::istringstream& ss, TextureMap& map, std::string& statement);
		void	SetAmbiantMap(std::istringstream& ss);

		void	ParseFile(std::ifstream& ifs);

	public:
		static MaterialList	ImportMtl(std::string filename);

};

#endif // !MTL_PARSER_HPP
