#pragma once

#include <string>
#include <ostream>
#include <iomanip>

enum class TokenType { // Stole the list of tokens from wzid
	TOKEN_EOF,			// End of file
	TOKEN_LPAREN,		// (
	TOKEN_RPAREN,		// )
	TOKEN_LBRACE,		// {
	TOKEN_RBRACE,		// }
	TOKEN_COMMA,		// ,
	TOKEN_PLUS,			// +
	TOKEN_MINUS,		// -
	TOKEN_STAR,			// *
	TOKEN_SLASH,		// /
	TOKEN_EQUAL,		// =
	TOKEN_LESSTHAN,		// <
	TOKEN_GREATERTHAN,	// >
	TOKEN_PERIOD,		// .
	TOKEN_SEMI,			// ;
	TOKEN_AND,			// &
	TOKEN_OR,			// |
	TOKEN_NOT,			// !
	TOKEN_XOR,			// ^
	TOKEN_MOD,			// %
	TOKEN_FUNC,			// func
	TOKEN_RETURN,		// return
	TOKEN_TYPE,			// type
	TOKEN_STRING,		// string literals
	TOKEN_IDENTIFIER,	// identifiers
	TOKEN_NUMBER		// numeric literals
};

// Token structure to hold token information
struct Token {
	TokenType type;
	std::string value;
	int line;
	int column;

	Token(TokenType t, const std::string& v, int l, int c)
		: type(t), value(v), line(l), column(c) {}
	// Default constructor
	Token() : type(TokenType::TOKEN_EOF), value(""), line(0), column(0) {}

	// Friend operator to print token
	friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

std::ostream& operator<<(std::ostream& os, const TokenType& type) {
	switch (type) {
		case TokenType::TOKEN_EOF:          os << "TOKEN_EOF"; break;
		case TokenType::TOKEN_LPAREN:       os << "TOKEN_LPAREN"; break;
		case TokenType::TOKEN_RPAREN:       os << "TOKEN_RPAREN"; break;
		case TokenType::TOKEN_LBRACE:       os << "TOKEN_LBRACE"; break;
		case TokenType::TOKEN_RBRACE:       os << "TOKEN_RBRACE"; break;
		case TokenType::TOKEN_COMMA:        os << "TOKEN_COMMA"; break;
		case TokenType::TOKEN_PLUS:         os << "TOKEN_PLUS"; break;
		case TokenType::TOKEN_MINUS:        os << "TOKEN_MINUS"; break;
		case TokenType::TOKEN_STAR:         os << "TOKEN_STAR"; break;
		case TokenType::TOKEN_SLASH:        os << "TOKEN_SLASH"; break;
		case TokenType::TOKEN_EQUAL:        os << "TOKEN_EQUAL"; break;
		case TokenType::TOKEN_LESSTHAN:     os << "TOKEN_LESS_THAN"; break;
		case TokenType::TOKEN_GREATERTHAN:  os << "TOKEN_GREATER_THAN"; break;
		case TokenType::TOKEN_PERIOD:       os << "TOKEN_PERIOD"; break;
		case TokenType::TOKEN_SEMI:         os << "TOKEN_SEMICOLON"; break;
		case TokenType::TOKEN_AND:          os << "TOKEN_AND"; break;
		case TokenType::TOKEN_OR:           os << "TOKEN_OR"; break;
		case TokenType::TOKEN_NOT:          os << "TOKEN_NOT"; break;
		case TokenType::TOKEN_XOR:          os << "TOKEN_XOR"; break;
		case TokenType::TOKEN_MOD:          os << "TOKEN_MOD"; break;
		case TokenType::TOKEN_FUNC:         os << "TOKEN_FUNC"; break;
		case TokenType::TOKEN_RETURN:       os << "TOKEN_RETURN"; break;
		case TokenType::TOKEN_TYPE:         os << "TOKEN_TYPE"; break;
		case TokenType::TOKEN_STRING:       os << "TOKEN_STRING"; break;
		case TokenType::TOKEN_IDENTIFIER:   os << "TOKEN_IDENTIFIER"; break;
		case TokenType::TOKEN_NUMBER:       os << "TOKEN_NUMBER"; break;
		default:                            os << "TOKEN_UNDEFINED"; break;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const Token& token) {
	os << "Token: " << std::setw(12) << std::left << token.type
	   << " Line: " << std::setw(4) << std::left << token.line
	   << " Col: " << std::setw(4) << std::left << token.column
	   << " Value: \"" << token.value << "\"";
	return os;
}