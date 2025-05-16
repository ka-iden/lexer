#include "token.h"

std::ostream& operator<< (std::ostream& os, const Token& token)
{
	switch (token.type)
	{
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

	if (token.type == TokenType::TOKEN_IDENTIFIER || token.type == TokenType::TOKEN_STRING
		|| token.type == TokenType::TOKEN_NUMBER || token.type == TokenType::TOKEN_TYPE)
		os << "(" << token.value << ")";
	return os;
}