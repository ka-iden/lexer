#include "lexer.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::string readFile(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file)
	{
		std::cerr << "Error: Could not open file: " << filePath << std::endl;
		return "";
	}
	
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

const std::string sampleCode =
R"(
return 4 + 6;
)";


int main(int argc, char* argv[])
{
	std::string sourceCode;
	
	if (argc > 1)
	{
		// Read from file if filename is provided
		std::cout << "Using code provided:" << std::endl;
		sourceCode = readFile(argv[1]);
	} else
	{
		// Use sample code
		std::cout << "Using sample code:" << std::endl;
		sourceCode = sampleCode;
	}

	std::cout << "====================================" << std::endl;
	std::cout << sampleCode << std::endl;
	std::cout << "====================================" << std::endl;

	if (sourceCode.empty())
	{
		std::cerr << "Error: No source code to tokenize." << std::endl;
		std::cerr << "Usage: " << argv[0] << " [source_file]" << std::endl;
		throw std::runtime_error("No source code to tokenize.");
	}
	
	Lexer lexer(sourceCode);
	std::vector<Token> tokens = lexer.tokenizeAll();
	
	std::cout << "\nTokens:" << std::endl;
	std::cout << "=======" << std::endl;
	for (const Token& token : tokens)
		std::cout << token << std::endl;
	
	std::cout << "\nTotal tokens: " << tokens.size() << std::endl;
}