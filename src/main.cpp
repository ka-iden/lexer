#include "lexer.h"

#include <iostream>
#include <fstream>
#include <sstream>

static std::string readFile(const std::string& filePath)
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
R"(func main() {
	int x = 5;
	return x + 5;
})";


int main(int argc, char* argv[])
{
	std::string sourceCode;
	
	if (argc > 1)
	{
		// Read from file if filename is provided
		std::cout << "Using code provided from " << argv[1] << ":\n";
		sourceCode = readFile(argv[1]);
	} else
	{
		// Use sample code
		std::cout << "Using sample code:\n";
		sourceCode = sampleCode;
	}

	std::cout << "====================================\n" << sampleCode << "\n====================================\n";

	if (sourceCode.empty())
	{
		std::cerr << "Error: No source code to tokenize." << std::endl << "Usage: " << argv[0] << " [source_file]" << std::endl;
		throw std::runtime_error("No source code to tokenize.");
	}
	
	Lexer lexer(sourceCode);
	std::vector<Token> tokens = lexer.tokenizeAll();
	
	std::cout << "\nTokens:\n=======" << std::endl;
	
	for (const Token& token : tokens)
	{
		switch (token.type)
		{
		case TokenType::TOKEN_EOF:          std::cout << "TOKEN_EOF"; break;
		case TokenType::TOKEN_LPAREN:       std::cout << "TOKEN_LPAREN"; break;
		case TokenType::TOKEN_RPAREN:       std::cout << "TOKEN_RPAREN"; break;
		case TokenType::TOKEN_LBRACE:       std::cout << "TOKEN_LBRACE"; break;
		case TokenType::TOKEN_RBRACE:       std::cout << "TOKEN_RBRACE"; break;
		case TokenType::TOKEN_COMMA:        std::cout << "TOKEN_COMMA"; break;
		case TokenType::TOKEN_PLUS:         std::cout << "TOKEN_PLUS"; break;
		case TokenType::TOKEN_MINUS:        std::cout << "TOKEN_MINUS"; break;
		case TokenType::TOKEN_STAR:         std::cout << "TOKEN_STAR"; break;
		case TokenType::TOKEN_SLASH:        std::cout << "TOKEN_SLASH"; break;
		case TokenType::TOKEN_EQUAL:        std::cout << "TOKEN_EQUAL"; break;
		case TokenType::TOKEN_LESSTHAN:     std::cout << "TOKEN_LESS_THAN"; break;
		case TokenType::TOKEN_GREATERTHAN:  std::cout << "TOKEN_GREATER_THAN"; break;
		case TokenType::TOKEN_PERIOD:       std::cout << "TOKEN_PERIOD"; break;
		case TokenType::TOKEN_SEMI:         std::cout << "TOKEN_SEMICOLON"; break;
		case TokenType::TOKEN_AND:          std::cout << "TOKEN_AND"; break;
		case TokenType::TOKEN_OR:           std::cout << "TOKEN_OR"; break;
		case TokenType::TOKEN_NOT:          std::cout << "TOKEN_NOT"; break;
		case TokenType::TOKEN_XOR:          std::cout << "TOKEN_XOR"; break;
		case TokenType::TOKEN_MOD:          std::cout << "TOKEN_MOD"; break;
		case TokenType::TOKEN_FUNC:         std::cout << "TOKEN_FUNC"; break;
		case TokenType::TOKEN_RETURN:       std::cout << "TOKEN_RETURN"; break;
		case TokenType::TOKEN_TYPE:         std::cout << "TOKEN_TYPE"; break;
		case TokenType::TOKEN_STRING:       std::cout << "TOKEN_STRING"; break;
		case TokenType::TOKEN_IDENTIFIER:   std::cout << "TOKEN_IDENTIFIER"; break;
		case TokenType::TOKEN_NUMBER:       std::cout << "TOKEN_NUMBER"; break;
		default:                            std::cout << "TOKEN_UNDEFINED"; break;
		}

		if (token.type == TokenType::TOKEN_IDENTIFIER || token.type == TokenType::TOKEN_STRING
			|| token.type == TokenType::TOKEN_NUMBER || token.type == TokenType::TOKEN_TYPE)
			std::cout << "(" << token.value << ")";

		std::cout << " Line: " << token.line << ", Column: " << token.column << "\n";
	}
	
	std::cout << "\nTotal tokens: " << tokens.size() << std::endl;
}