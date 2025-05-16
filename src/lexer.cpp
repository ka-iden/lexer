#include "lexer.h"
#include <cctype>
#include <iostream>

std::vector<Token> Lexer::tokenizeAll()
{
	std::vector<Token> tokens;

	// Reset lexer state
	m_position = 0;
	m_line = 1;
	m_column = 1;

	while (!isAtEnd())
	{
		Token token = getNextToken();
		tokens.push_back(token);
		if (token.type == TokenType::TOKEN_EOF)
		{
			break;
		}
	}
	
	return tokens;
}

Token Lexer::getNextToken()
{
	if (isAtEnd())
		return Token(TokenType::TOKEN_EOF, "", m_line, m_column);
	
	
	// Skip whitespace and comments
	skipWhitespaceAndComments();
	
	if (isAtEnd())
		return Token(TokenType::TOKEN_EOF, "", m_line, m_column);
	
	
	char c = peek();
	
	if (isAlpha(c) || c == '_')
		return readIdentifier();
	
	
	if (isDigit(c))
		return readNumber();
	
	if (c == '"')
		return readString();
	
	// Handle operators and punctuation
	return readOperator();
}

void Lexer::skipWhitespaceAndComments()
{
	bool skippedSomething;
	
	do
	{
		skippedSomething = false;
		
		// Skip any whitespace
		size_t oldPosition = m_position;

		// Skip whitespace
		while (!isAtEnd() && isWhitespace(peek()))
			advance();
		

		if (oldPosition != m_position)
			skippedSomething = true;
		
		
		// Check for comments
		if (!isAtEnd() && peek() == '/' && m_position + 1 < m_source.size() &&
			(m_source[m_position + 1] == '/' || m_source[m_position + 1] == '*'))
		{
			
			// Skip comments
			if (peek() == '/' && m_position + 1 < m_source.size())
			{
				if (m_source[m_position + 1] == '/') // Single line comment
				{
					// Skip the //
					advance();
					advance();

					// Skip until end of line
					while (!isAtEnd() && peek() != '\n')
						advance();
				}
				else if (m_source[m_position + 1] == '*') // Multi-line comment
				{
					// Skip the /*
					advance();
					advance();

					// Skip until closing */
					while (!isAtEnd())
					{
						if (peek() == '*' && m_position + 1 < m_source.size() && m_source[m_position + 1] == '/')
						{
							// Skip the */
							advance();
							advance();
							break;
						}
						else
							advance();
					}
				}
			}
			skippedSomething = true;
		}
	}
	while (skippedSomething && !isAtEnd()); // Continue until no more whitespace or comments are found
}

Token Lexer::readIdentifier()
{
	int startColumn = m_column;
	std::string identifier;
	
	while (!isAtEnd() && (isAlphaNumeric(peek()) || peek() == '_'))
		identifier += advance();
	
	// Check if this is a keyword
	TokenType type = identifierType(identifier);
	
	return Token(type, identifier, m_line, startColumn);
}

TokenType Lexer::identifierType(const std::string& identifier)
{
	if (identifier == "func") return TokenType::TOKEN_FUNC;
	if (identifier == "return") return TokenType::TOKEN_RETURN;
	if (identifier == "type") return TokenType::TOKEN_TYPE;
	
	// If it's not a keyword, it's an identifier
	return TokenType::TOKEN_IDENTIFIER;
}

Token Lexer::readNumber()
{
	int startColumn = m_column;
	std::string number;
	bool hasDecimalPoint = false;
	
	while (!isAtEnd() && (isDigit(peek()) || (!hasDecimalPoint && peek() == '.')))
	{
		if (peek() == '.')
			hasDecimalPoint = true;
		
		number += advance();
	}
	
	return Token(TokenType::TOKEN_NUMBER, number, m_line, startColumn);
}

Token Lexer::readString()
{
	int startColumn = m_column;
	std::string str;
	
	// Skip the opening quote
	advance();
	
	while (!isAtEnd() && peek() != '"')
	{
		// Handle escape sequences if needed
		if (peek() == '\\' && m_position + 1 < m_source.size())
		{
			advance(); // Skip the backslash
			char next = advance();
			switch (next)
			{
				case 'n': str += '\n'; break;
				case 't': str += '\t'; break;
				case 'r': str += '\r'; break;
				case '\\': str += '\\'; break;
				case '"': str += '"'; break;
				default: str += next; break;
			}
		}
		else
			str += advance();
	}
	
	if (isAtEnd())
		std::cerr << "Error: Unterminated string at line " << m_line << ", column " << startColumn << std::endl;
	else
		advance(); // Skip the closing quote
	
	return Token(TokenType::TOKEN_STRING, str, m_line, startColumn);
}

Token Lexer::readOperator()
{
	int startColumn = m_column;
	char c = advance();
	std::string op(1, c);
	
	// Map characters to token types
	switch (c)
	{
		case '(': return Token(TokenType::TOKEN_LPAREN, op, m_line, startColumn);
		case ')': return Token(TokenType::TOKEN_RPAREN, op, m_line, startColumn);
		case '{': return Token(TokenType::TOKEN_LBRACE, op, m_line, startColumn);
		case '}': return Token(TokenType::TOKEN_RBRACE, op, m_line, startColumn);
		case ',': return Token(TokenType::TOKEN_COMMA, op, m_line, startColumn);
		case '+': return Token(TokenType::TOKEN_PLUS, op, m_line, startColumn);
		case '-': return Token(TokenType::TOKEN_MINUS, op, m_line, startColumn);
		case '*': return Token(TokenType::TOKEN_STAR, op, m_line, startColumn);
		case '/': return Token(TokenType::TOKEN_SLASH, op, m_line, startColumn);
		case '=': return Token(TokenType::TOKEN_EQUAL, op, m_line, startColumn);
		case '<': return Token(TokenType::TOKEN_LESSTHAN, op, m_line, startColumn);
		case '>': return Token(TokenType::TOKEN_GREATERTHAN, op, m_line, startColumn);
		case '.': return Token(TokenType::TOKEN_PERIOD, op, m_line, startColumn);
		case ';': return Token(TokenType::TOKEN_SEMI, op, m_line, startColumn);
		case '&': return Token(TokenType::TOKEN_AND, op, m_line, startColumn);
		case '|': return Token(TokenType::TOKEN_OR, op, m_line, startColumn);
		case '!': return Token(TokenType::TOKEN_NOT, op, m_line, startColumn);
		case '^': return Token(TokenType::TOKEN_XOR, op, m_line, startColumn);
		case '%': return Token(TokenType::TOKEN_MOD, op, m_line, startColumn);
		default:  return Token(TokenType::TOKEN_EOF, op, m_line, startColumn);
	}
}



bool Lexer::isWhitespace(char c) const
{
	return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool Lexer::isDigit(char c) const
{
	return std::isdigit(static_cast<unsigned char>(c));
}

bool Lexer::isAlpha(char c) const
{
	return std::isalpha(static_cast<unsigned char>(c));
}

bool Lexer::isAlphaNumeric(char c) const
{
	return isAlpha(c) || isDigit(c);
}

char Lexer::peek() const
{
	if (isAtEnd())
		return '\0';
	
	return m_source[m_position]; 
}

char Lexer::advance()
{
	char current = m_source[m_position++];
	if (current == '\n')
	{
		m_line++;
		m_column = 1;
	}
	else
		m_column++;
	
	return current;
}

bool Lexer::match(char expected)
{
	if (isAtEnd() || m_source[m_position] != expected)
		return false;
	
	m_position++;
	m_column++;
	return true;
}

bool Lexer::isAtEnd() const
{
	return m_position >= m_source.size();
}

