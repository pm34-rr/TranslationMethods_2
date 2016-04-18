#include "Token.h"

Token::Token( TokenType t, uint row, uint pos ):
	tokenType( t ),
	rowNumber( row ),
	posInRow( pos )
{

}

std::ifstream & operator>>( std::ifstream & input, Token & token )
{
	char c;
	int t = (int) token.tokenType;
	input >> c >> t >> c >> token.rowNumber >> c >> token.posInRow >> c;
	return input;
}

std::ofstream & operator<<( std::ofstream & output, const Token & token )
{
	output << '(' << (int)token.tokenType << ',' << token.rowNumber << ',' << token.posInRow << ')';
	return output;
}
