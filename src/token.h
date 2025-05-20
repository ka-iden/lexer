#pragma once

#include <string>

typedef enum TokenType
{ // Stole the list of tokens from wzid
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
struct Token
{
	TokenType type;
	std::string value;
};