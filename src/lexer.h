#pragma once

#include "token.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Lexer {
public:
	// Constructor takes input source code
	Lexer(const std::string& source);

	// Tokenize the entire input and return all tokens
	std::vector<Token> tokenizeAll();

	// Get the next token from the input
	Token getNextToken();

	// Check if there are more tokens to process
	bool hasMoreTokens() const;

	// Reset the lexer to the beginning of input
	void reset();

private:
	// Input source code
	std::string m_source;
	
	// Current position in the source
	size_t m_position;
	
	// Current line number (for error reporting)
	int m_line;
	
	// Current column number (for error reporting)
	int m_column;
		// Helper methods
	void skipWhitespace();
	void skipComments();
	void skipWhitespaceAndComments();
	Token readIdentifier();
	Token readNumber();
	Token readString();
	Token readOperator();
	
	// Check if an identifier is a keyword
	TokenType identifierType(const std::string& identifier);
	
	// Character classification helpers
	bool isWhitespace(char c) const;
	bool isDigit(char c) const;
	bool isAlpha(char c) const;
	bool isAlphaNumeric(char c) const;
	
	// Current character access
	char peek() const;
	char advance();
	bool match(char expected);
	bool isAtEnd() const;
};
