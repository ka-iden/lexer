#pragma once

#include "token.h"

#include <string>
#include <vector>

class Lexer
{
public:
	Lexer(const std::string& source) : m_Source(source) {}

	Token getNextToken();

private:
	std::string m_Source;

	size_t m_Position = 0;
	int m_Line = 1;
	int m_Column = 1;
	
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