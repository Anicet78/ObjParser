#include "ObjParser.hpp"

void	ThrowError(std::string error)
{
	std::cerr << COLOR_LIGHT_RED << "An error as occured: " << error << COLOR_NC << std::endl;
	throw std::runtime_error(error);
}

void	ThrowError(std::string error, size_t line)
{
	std::cerr << COLOR_LIGHT_RED << "An error as occured at line " << std::to_string(line) << ": " << error << COLOR_NC << std::endl;
	throw std::runtime_error(error);
}

void	ThrowError(std::string error, std::istringstream& ss, size_t line)
{
	std::cerr << COLOR_LIGHT_RED << "An error as occured at line " << std::to_string(line) << ": " << error << " on token" << ss.str() << COLOR_NC << std::endl;
	throw std::runtime_error(error);
}
