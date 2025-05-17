#pragma once

#include "token.h"

#include <string>
#include <vector>

class Lexer
{
public:
	Lexer(const std::string& source) : m_source(source) {}

	std::vector<Token> tokenizeAll();

	Token getNextToken();

private:
	std::string m_source;

	size_t m_position = 0;
	int m_line = 1;
	int m_column = 1;
	
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