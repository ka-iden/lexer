#include "lexer.h"

#include <iostream>
#include <fstream>
#include <sstream>

// Helper function to read a file into a string
std::string readFile(const std::string& filePath) {
	std::ifstream file(filePath);
	if (!file) {
		std::cerr << "Error: Could not open file: " << filePath << std::endl;
		return "";
	}
	
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

// Sample code to demonstrate lexer
const std::string sampleCode = R"(
function calculateArea(width, height) {
	let area = width * height;
	
	if (area > 100) {
		return "Large area: " + area;
	} else {
		return "Small area: " + area;
	}
}

let result = calculateArea(10.5, 20.3);
)";

void printToken(const Token& token) {
	std::cout << token << std::endl;
}

int main(int argc, char* argv[])
{
	std::string sourceCode;
	
	if (argc > 1) {
		// Read from file if filename is provided
		sourceCode = readFile(argv[1]);
	} else {
		// Use sample code for demonstration
		sourceCode = sampleCode;
		std::cout << "Using sample code for demonstration:" << std::endl;
		std::cout << "====================================" << std::endl;
		std::cout << sampleCode << std::endl;
		std::cout << "====================================" << std::endl;
	}
	
	if (sourceCode.empty()) {
		std::cerr << "Error: No source code to tokenize." << std::endl;
		std::cerr << "Usage: " << argv[0] << " [source_file]" << std::endl;
		return 1;
	}
	
	// Create lexer and tokenize
	Lexer lexer(sourceCode);
	std::vector<Token> tokens = lexer.tokenizeAll();
	
	// Print all tokens
	std::cout << "\nTokens:" << std::endl;
	std::cout << "=======" << std::endl;
	for (const Token& token : tokens) {
		printToken(token);
	}
	
	std::cout << "\nTotal tokens: " << tokens.size() << std::endl;
	
	return 0;
}