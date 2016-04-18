#pragma once

#include "Token.h"

#include <vector>
#include <string>
#include <fstream>

class LexicalAnalyzer
{
public:
	LexicalAnalyzer();

	bool analyze( const std::string & programPath );

private:
	Token createToken( TokenType tokenType, uint rowNum, uint posInRow = 0 );
	void pushToken( const TokenType t, const std::string & tokenName, std::vector<Token> & tokens );
	void createErrorFile( const std::string & errorMessage );
	void saveTokensToFile( const std::vector<std::vector<Token>> & tokens, const std::string & path ) const;
	void clearErrorFile( const std::string & path ) const;
	bool removeComments( std::ifstream & input, std::string & currentLine, uint & linesRemoved ) const;
	bool removeEmptyLines( std::ifstream & input, std::string & currentLine, uint & linesRemoved ) const;

	bool isDigit( char c )		const;
	bool isLetter( char c )		const;
	bool isSeparator( char c )	const;
	bool isOperation( char c )	const;
	bool isCorrect( char c )	const;
};
