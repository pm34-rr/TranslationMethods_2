#include "LexicalAnalyzer.h"

#include "TableStorage.h"
#include "Token.h"

#include <vector>
#include <fstream>

using namespace std;

LexicalAnalyzer::LexicalAnalyzer()
{

}

bool LexicalAnalyzer::analyze( const string & programPath )
{
	ifstream input( programPath.c_str() );

	std::vector<Token> tokens;

	uint lineCount = 1;
	string currentLine;
	while( input >> currentLine ) {
		if ( currentLine.empty() )
			continue;

		char c		= currentLine[0];
		char cNext	= currentLine[1];

		string tokenName = { c };
		if ( c == '=' ) {
			if ( c == cNext ) {
				tokenName += cNext;
				pushToken( OPERATION, tokenName, tokens );
			}
			else {
				pushToken( SEPARATOR, tokenName, tokens );
			}
		}
		else if ( c == '!' ) {
			if ( cNext == '=' ) {
				pushToken( OPERATION, tokenName, tokens );
			}
			else {
				createErrorFile( "Incorrect symbol in line " + to_string( lineCount ) );
			}
		}
		else if ( isSeparator( c ) ) {
			pushToken( SEPARATOR, tokenName, tokens );
		}
		else if ( isOperation( c ) ) {
			pushToken( OPERATION, tokenName, tokens );
		}
		else if ( isLetter( c ) ) {
			int pos = 1;
			while ( isLetter( cNext ) || isDigit( cNext ) ) {
				tokenName += cNext;
				++pos;
				cNext = currentLine[pos];
			}
			if ( isCorrect( cNext ) ) {
				TokenType t = KEYWORD;
				if ( !theTableStorage.findKeyWordByName( tokenName ) ) {
					// It's a lexem
					// TODO_1: add lexem to LexemTable

					t = IDENTIFICATOR;
				}
				pushToken( t, tokenName, tokens );
				currentLine = currentLine.substr( pos, currentLine.length() - pos );
			}
			else {
				createErrorFile( "Incorrect symbol in line " + to_string( lineCount ) );
			}

		}
		else if ( isDigit( c ) ) {
			int dotCount = 0;
			int pos = 1;
			while( isDigit( cNext ) || ( cNext == '.' ) ) {
				tokenName += cNext;
				if ( cNext == '.' ) {
					if ( dotCount != 0 ) {
						createErrorFile( "Incorrect float constant " + to_string( lineCount ) );
					}
					else
						++dotCount;
				}
				++pos;
				cNext = currentLine[pos];
			}
			if ( isLetter( c ) || !isCorrect( c ) ) {
				createErrorFile( "Incorrect constant " + to_string( lineCount ) );
			}
			else {
				pushToken( CONST, tokenName, tokens );
				currentLine = currentLine.substr( pos, currentLine.length() - pos );
			}
		}
		else {
			createErrorFile( "Incorrect symbol in line " + to_string( lineCount ) );
		}

		++lineCount;
	}
}

Token LexicalAnalyzer::createToken( TokenType tokenType, uint rowNum, uint posInRow )
{
	return Token( tokenType, rowNum, posInRow );
}

void LexicalAnalyzer::pushToken( const TokenType t, const string & tokenName, std::vector<Token> & tokens )
{
	uint posInTable = 0;
	switch ( t ) {
	case KEYWORD:
		posInTable = theTableStorage.findKeyWordByName( tokenName );
		break;
	case OPERATION:
		posInTable = theTableStorage.findOperationByName( tokenName );
		break;
	case SEPARATOR:
		posInTable = theTableStorage.findSeparatorByName( tokenName );
		break;
	}

	tokens.push_back( createToken( t, posInTable ) );
}

void LexicalAnalyzer::createErrorFile( const string & errorMessage )
{
	ofstream output( "Error.txt" );
	output << errorMessage;
	output.close();
}

bool LexicalAnalyzer::isDigit( char c ) const
{
	return ( '0' <= c && c <= '9' );
}

bool LexicalAnalyzer::isLetter( char c ) const
{
	char cc = tolower( c );
	return ( 'a' <= cc && cc <= 'z' );
}

bool LexicalAnalyzer::isSeparator( char c ) const
{
	string sep = { c };
	return ( theTableStorage.findSeparatorByName( sep ) != -1 );
}

bool LexicalAnalyzer::isOperation( char c ) const
{
	string op = { c };
	return ( theTableStorage.findOperationByName( op ) != -1 );
}

bool LexicalAnalyzer::isCorrect( char c ) const
{
	return ( isLetter( c ) ||
			 isDigit( c ) ||
			 isSeparator( c ) ||
			 isOperation( c ) );
}
