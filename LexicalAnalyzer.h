#pragma once

#include "Token.h"

#include <vector>
#include <string>

class LexicalAnalyzer
{
public:
	LexicalAnalyzer();

	bool analyze( const std::string & programPath );

private:
	Token createToken( TokenType tokenType, uint rowNum, uint posInRow = 0 );
	void pushToken( const TokenType t, const std::string & tokenName, std::vector<Token> & tokens );
	void createErrorFile( const std::string & errorMessage );

	bool isDigit( char c )		const;
	bool isLetter( char c )		const;
	bool isSeparator( char c )	const;
	bool isOperation( char c )	const;
	bool isCorrect( char c )	const;
};

