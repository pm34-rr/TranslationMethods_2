#include "LexicalAnalyzer.h"

#include "Tables/ChangeableTable.h"

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

	std::vector<std::vector<Token>> allTokens;
	theTableStorage;

	uint linesCount = 0;
	string currentLine;
	std::vector<Token> tokens;
	bool needExit = false;
	uint before = 0;

	ChangeableTable * ids		= theTableStorage.getIdentificatorsTable();
	ChangeableTable * consts	= theTableStorage.getConstsTable();

	while ( true ) {
		before = linesCount;
		needExit = removeEmptyLines( input, currentLine, linesCount );

		if ( ( before != linesCount ) && !tokens.empty() ) {
			allTokens.push_back( tokens );
			tokens.clear();
		}
		if ( needExit ) {
			if ( !tokens.empty() )
				allTokens.push_back( tokens );
			break;
		}

		size_t l = currentLine.length();

		char c		= currentLine[0];
		char cNext	= currentLine[1];

		string tokenName = { c };
		if ( c == ' ' || c == '\t' )
			currentLine = currentLine.substr( 1, l - 1 );
		else if ( c == '/' ) {
			if ( cNext == '/' )
				currentLine.clear();
			else if ( cNext == '*' ) {
				if ( removeComments( input, currentLine, linesCount ) ) {
					continue;
				}
				else {
					createErrorFile( "Not closed commentary, line " + to_string( linesCount ) );
					return false;
				}
			}
		}
		else if ( c == '=' ) {
			if ( c == cNext ) {
				tokenName += cNext;
				pushToken( OPERATION, tokenName, tokens );
				currentLine = currentLine.substr( 2, l - 2 );
			}
			else {
				pushToken( SEPARATOR, tokenName, tokens );
				currentLine = currentLine.substr( 1, l - 1 );
			}
		}
		else if ( c == '!' ) {
			if ( cNext == '=' ) {
				pushToken( OPERATION, tokenName, tokens );
				currentLine = currentLine.substr( 2, l - 2 );
			}
			else {
				createErrorFile( "Incorrect symbol in line " + to_string( linesCount ) );
				return false;
			}
		}
		else if ( isSeparator( c ) ) {
			pushToken( SEPARATOR, tokenName, tokens );
			currentLine = currentLine.substr( 1, l - 1 );
		}
		else if ( isOperation( c ) ) {
			pushToken( OPERATION, tokenName, tokens );
			currentLine = currentLine.substr( 1, l - 1 );
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
				if ( theTableStorage.findKeyWordByName( tokenName ) == -1 ) {
					ids->add( tokenName );
					t = IDENTIFICATOR;
				}
				pushToken( t, tokenName, tokens );
				currentLine = currentLine.substr( pos, currentLine.length() - pos );
			}
			else {
				createErrorFile( "Incorrect symbol in line " + to_string( linesCount ) );
				return false;
			}
		}
		else if ( isDigit( c ) ) {
			int dotCount = 0;
			int pos = 1;
			while( isDigit( cNext ) || ( cNext == '.' ) ) {
				tokenName += cNext;
				if ( cNext == '.' ) {
					if ( dotCount != 0 ) {
						createErrorFile( "Incorrect float constant " + to_string( linesCount ) );
						return false;
					}
					else
						++dotCount;
				}
				++pos;
				cNext = currentLine[pos];
			}
			if ( isLetter( c ) || !isCorrect( c ) ) {
				createErrorFile( "Incorrect constant " + to_string( linesCount ) );
				return false;
			}
			else {
				Type type = dotCount == 0 ? INT : FLOAT;
				consts->add( tokenName, type );
				pushToken( CONST, tokenName, tokens );
				currentLine = currentLine.substr( pos, currentLine.length() - pos );
			}
		}
		else {
			createErrorFile( "Undefined symbol in line " + to_string( linesCount ) );
			return false;
		}
	}
	saveTokensToFile( allTokens, "tokens.txt" );
	clearErrorFile( "Error.txt" );

	return true;
}

Token LexicalAnalyzer::createToken( TokenType tokenType, uint rowNum, uint posInRow )
{
	return Token( tokenType, rowNum, posInRow );
}

void LexicalAnalyzer::pushToken( const TokenType t, const string & tokenName, std::vector<Token> & tokens )
{
	uint posInTable = 0;
	uint posInRow = 0;
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
	case IDENTIFICATOR:
		pair<int, int> p = theTableStorage.findLexemByName( tokenName );
		posInTable	= p.first;
		posInRow	= p.second;
		break;
	}

	tokens.push_back( createToken( t, posInTable, posInRow ) );
}

void LexicalAnalyzer::createErrorFile( const string & errorMessage )
{
	ofstream output( "Error.txt" );
	output << errorMessage;
	output.close();

	output.open( "tokens.txt" );
	output.close();
}

void LexicalAnalyzer::saveTokensToFile( const std::vector<std::vector<Token> > & tokens, const string & path ) const
{
	ofstream output( path.c_str() );

	int j, nn;
	for ( int i = 0, n = tokens.size(); i < n; ++i ) {
		for ( j = 0, nn = tokens[i].size(); j < nn; ++j )
			output << tokens[i][j];
		output << endl;
	}

	output.close();
}

void LexicalAnalyzer::clearErrorFile( const string & path ) const
{
	ofstream output( path.c_str() );
	output << "No errors found";
	output.close();
}

bool LexicalAnalyzer::removeComments( ifstream & input, string & currentLine, uint & linesRemoved ) const
{
	while ( true ) {
		if ( removeEmptyLines( input, currentLine, linesRemoved ) )
			return false;

		size_t isClosed = currentLine.find( "*/" );
		if ( isClosed != string::npos ) {
			currentLine.erase( currentLine.begin(), currentLine.begin() + isClosed + 2 );
			return true;
		} else
			currentLine.clear();
	}
}

bool LexicalAnalyzer::removeEmptyLines( ifstream & input, string & currentLine, uint & linesRemoved ) const
{
	bool needExit = false;
	while ( true ) {
		if ( currentLine.empty() ) {
			if ( getline( input, currentLine ) )
				++linesRemoved;
			else {
				needExit = true;
				break;
			}
		}
		else
			break;
	}

	return needExit;
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
			 isOperation( c ) ||
			 (c == ' ') );
}
