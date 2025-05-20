#include "lexer.h"

#include <iostream>
#include <fstream>
#include <sstream>

const std::string sampleCode =
R"(func main() {
	int x = 5;
	return x + 5;
})";

void printToken(Token token)
{
	switch (token.type)
	{
	case TOKEN_EOF:          std::cout << "TOKEN_EOF"; break;
	case TOKEN_LPAREN:       std::cout << "TOKEN_LPAREN"; break;
	case TOKEN_RPAREN:       std::cout << "TOKEN_RPAREN"; break;
	case TOKEN_LBRACE:       std::cout << "TOKEN_LBRACE"; break;
	case TOKEN_RBRACE:       std::cout << "TOKEN_RBRACE"; break;
	case TOKEN_COMMA:        std::cout << "TOKEN_COMMA"; break;
	case TOKEN_PLUS:         std::cout << "TOKEN_PLUS"; break;
	case TOKEN_MINUS:        std::cout << "TOKEN_MINUS"; break;
	case TOKEN_STAR:         std::cout << "TOKEN_STAR"; break;
	case TOKEN_SLASH:        std::cout << "TOKEN_SLASH"; break;
	case TOKEN_EQUAL:        std::cout << "TOKEN_EQUAL"; break;
	case TOKEN_LESSTHAN:     std::cout << "TOKEN_LESS_THAN"; break;
	case TOKEN_GREATERTHAN:  std::cout << "TOKEN_GREATER_THAN"; break;
	case TOKEN_PERIOD:       std::cout << "TOKEN_PERIOD"; break;
	case TOKEN_SEMI:         std::cout << "TOKEN_SEMICOLON"; break;
	case TOKEN_AND:          std::cout << "TOKEN_AND"; break;
	case TOKEN_OR:           std::cout << "TOKEN_OR"; break;
	case TOKEN_NOT:          std::cout << "TOKEN_NOT"; break;
	case TOKEN_XOR:          std::cout << "TOKEN_XOR"; break;
	case TOKEN_MOD:          std::cout << "TOKEN_MOD"; break;
	case TOKEN_FUNC:         std::cout << "TOKEN_FUNC"; break;
	case TOKEN_RETURN:       std::cout << "TOKEN_RETURN"; break;
	case TOKEN_TYPE:         std::cout << "TOKEN_TYPE"; break;
	case TOKEN_STRING:       std::cout << "TOKEN_STRING"; break;
	case TOKEN_IDENTIFIER:   std::cout << "TOKEN_IDENTIFIER"; break;
	case TOKEN_NUMBER:       std::cout << "TOKEN_NUMBER"; break;
	default:                            std::cout << "TOKEN_UNDEFINED"; break;
	}

	if (token.type == TOKEN_IDENTIFIER || token.type == TOKEN_STRING
		|| token.type == TOKEN_NUMBER || token.type == TOKEN_TYPE)
		std::cout << "(" << token.value << ")";

	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	std::string sourceCode;

	if (argc > 1)
	{
		// Read from file if filename is provided
		std::cout << "Using code provided from " << argv[1] << ":\n";
		std::ifstream file(argv[1]);

		if (!file)
			throw std::runtime_error("Error: Could not open file: " + std::string(argv[1]));

		std::stringstream buffer;
		buffer << file.rdbuf();

		sourceCode = buffer.str();
	}
	else
	{
		// Use sample code
		std::cout << "Using sample code:\n";
		sourceCode = sampleCode;
	}

	std::cout << "====================================\n" << sampleCode << "\n====================================\n";

	if (sourceCode.empty())
		throw std::runtime_error("No source code to tokenize.");

	Lexer lexer(sourceCode);

	std::cout << "\nTokens:\n=======" << std::endl;

	Token token = lexer.getNextToken();
	int tokenCount = 0; // Solely for debugging purposes
	while (token.type != TOKEN_EOF)
	{
		printToken(token);
		token = lexer.getNextToken();
		tokenCount++;
	}

	printToken(token);
	tokenCount++; // EOF token handled outside of loop

	std::cout << "\nTotal tokens: " << tokenCount << std::endl;
}