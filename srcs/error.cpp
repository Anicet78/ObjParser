#include "ObjParser.hpp"

[[noreturn]] void	ThrowError(std::string error)
{
	throw std::runtime_error("An error as occured: " + error);
}

[[noreturn]] void	ThrowError(std::string error, std::string& fileName)
{
	throw std::runtime_error("An error as occured from '" + fileName +"': " + error);
}

[[noreturn]] void	ThrowError(std::string error, size_t line, std::string& fileName)
{
	throw std::runtime_error("An error as occured from '" + fileName +"': at line " + std::to_string(line) + ": " + error);
}

[[noreturn]] void	ThrowError(std::string error, std::string& token, size_t line, std::string& fileName)
{
	if (!token.empty() && token.back() == '\r')
		token.pop_back();
	throw std::runtime_error("An error as occured from '" + fileName +"': at line " + std::to_string(line) + ": " + error + " on token '" + token + "'");
}

[[noreturn]] void	ThrowError(std::string error, std::istringstream& ss, size_t line, std::string& fileName)
{
	ss.clear();
	std::string token;
	ss >> token;
	if (!token.empty() && token.back() == '\r')
		token.pop_back();
	throw std::runtime_error("An error as occured from '" + fileName +"': at line " + std::to_string(line) + ": " + error + " on token '" + token + "'");
}
