#include "lexer.h"

Token Lexer::getNextToken()
{
	if (isAtEnd())
		return Token{ TOKEN_EOF, "" };

	// Skip whitespace and comments
	skipWhitespaceAndComments();

	if (isAtEnd())
		return Token{ TOKEN_EOF, "" };

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
		size_t oldPosition = m_Position;

		// Skip whitespace
		while (!isAtEnd() && isWhitespace(peek()))
			advance();

		if (oldPosition != m_Position)
			skippedSomething = true;

		// Check for comments
		if (!isAtEnd() && peek() == '/' && m_Position + 1 < m_Source.size() &&
			(m_Source[m_Position + 1] == '/' || m_Source[m_Position + 1] == '*'))
		{
			// Skip comments
			if (peek() == '/' && m_Position + 1 < m_Source.size())
			{
				if (m_Source[m_Position + 1] == '/') // Single line comment
				{
					// Skip the //
					advance();
					advance();

					// Skip until end of line
					while (!isAtEnd() && peek() != '\n')
						advance();
				}
				else if (m_Source[m_Position + 1] == '*') // Multi-line comment
				{
					// Skip the /*
					advance();
					advance();

					// Skip until closing */
					while (!isAtEnd())
					{
						if (peek() == '*' && m_Position + 1 < m_Source.size() && m_Source[m_Position + 1] == '/')
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
	} while (skippedSomething && !isAtEnd()); // Continue until no more whitespace or comments are found
}

Token Lexer::readIdentifier()
{
	int startColumn = m_Column;
	std::string identifier;

	while (!isAtEnd() && (isAlphaNumeric(peek()) || peek() == '_'))
		identifier += advance();

	// Check if this is a keyword
	TokenType type = identifierType(identifier);

	return Token{ type, identifier };
}

TokenType Lexer::identifierType(const std::string& identifier)
{
	if (identifier == "func")	return TOKEN_FUNC;
	if (identifier == "return") return TOKEN_RETURN;
	if (identifier == "type")	return TOKEN_TYPE;

	// If it's not a keyword, it's an identifier
	return TOKEN_IDENTIFIER;
}

Token Lexer::readNumber()
{
	int startColumn = m_Column;
	std::string number;
	bool hasDecimalPoint = false;

	while (!isAtEnd() && (isDigit(peek()) || (!hasDecimalPoint && peek() == '.')))
	{
		if (peek() == '.')
			hasDecimalPoint = true;

		number += advance();
	}

	return Token{ TOKEN_NUMBER, number };
}

Token Lexer::readString()
{
	int startColumn = m_Column;
	std::string str;

	// Skip the opening quote
	advance();

	while (!isAtEnd() && peek() != '"')
	{
		// Handle escape sequences if needed
		if (peek() == '\\' && m_Position + 1 < m_Source.size())
		{
			advance(); // Skip the backslash
			char next = advance();
			switch (next)
			{
			case 'n':	str += '\n';	break;
			case 't':	str += '\t';	break;
			case 'r':	str += '\r';	break;
			case '\\':	str += '\\';	break;
			case '"':	str += '"';		break;
			default:	str += next;	break;
			}
		}
		else
			str += advance();
	}

	if (isAtEnd())
		throw("Error: Unterminated string at line " + std::to_string(m_Line) + ", column " + std::to_string(startColumn));
	else
		advance(); // Skip the closing quote

	return Token{ TOKEN_STRING, str };
}

Token Lexer::readOperator()
{
	int startColumn = m_Column;
	char c = advance();
	std::string op(1, c);

	// Map characters to token types
	switch (c)
	{
	case '(': return Token{ TOKEN_LPAREN,		op };
	case ')': return Token{ TOKEN_RPAREN,		op };
	case '{': return Token{ TOKEN_LBRACE,		op };
	case '}': return Token{ TOKEN_RBRACE,		op };
	case ',': return Token{ TOKEN_COMMA,		op };
	case '+': return Token{ TOKEN_PLUS,			op };
	case '-': return Token{ TOKEN_MINUS,		op };
	case '*': return Token{ TOKEN_STAR,			op };
	case '/': return Token{ TOKEN_SLASH,		op };
	case '=': return Token{ TOKEN_EQUAL,		op };
	case '<': return Token{ TOKEN_LESSTHAN,		op };
	case '>': return Token{ TOKEN_GREATERTHAN,	op };
	case '.': return Token{ TOKEN_PERIOD,		op };
	case ';': return Token{ TOKEN_SEMI,			op };
	case '&': return Token{ TOKEN_AND,			op };
	case '|': return Token{ TOKEN_OR,			op };
	case '!': return Token{ TOKEN_NOT,			op };
	case '^': return Token{ TOKEN_XOR,			op };
	case '%': return Token{ TOKEN_MOD,			op };
	default: throw ("Error: Unknown operator at line " + std::to_string(m_Line) + ", column " + std::to_string(startColumn));
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

	return m_Source[m_Position];
}

char Lexer::advance()
{
	char current = m_Source[m_Position++];
	if (current == '\n')
	{
		m_Line++;
		m_Column = 1;
	}
	else
		m_Column++;

	return current;
}

bool Lexer::match(char expected)
{
	if (isAtEnd() || m_Source[m_Position] != expected)
		return false;

	m_Position++;
	m_Column++;
	return true;
}

bool Lexer::isAtEnd() const
{
	return m_Position >= m_Source.size();
}