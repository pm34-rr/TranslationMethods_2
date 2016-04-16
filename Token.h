#pragma once

#include <fstream>

typedef unsigned int uint;

enum TokenType {
	IDENTIFICATOR = 0,
	CONST,
	KEYWORD,
	OPERATION,
	SEPARATOR
};

struct Token
{
	Token( TokenType t, uint row, uint pos );

	TokenType	tokenType;
	uint		rowNumber;
	uint		posInRow;

	friend std::ifstream & operator>>( std::ifstream & input, Token & token );
	friend std::ofstream & operator<<( std::ofstream & output, const Token & token );
};
