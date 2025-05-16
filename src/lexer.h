#pragma once

#include "token.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Lexer
{
public:
	// Constructor takes input source code
	Lexer(const std::string& source) : m_source(source), m_position(0), m_line(1), m_column(1) {}

	std::vector<Token> tokenizeAll();

	Token getNextToken();

private:
	std::string m_source;
	size_t m_position;

	int m_line;
	int m_column;
	
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
