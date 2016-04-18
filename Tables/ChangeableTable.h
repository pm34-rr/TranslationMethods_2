#pragma once

#include "Lexeme.h"

#include <vector>

typedef std::vector<Lexeme> vl;

class ChangeableTable
{
public:
	ChangeableTable( size_t size );
	ChangeableTable();

	void add( const std::string & name, Type type, bool isArray = false, size_t arraySize = 1 );
	void add ( const std::string & name );
	void setTypeByName( const std::string & name, Type type );
	void setArrayByName( const std::string & name );
	void setArraySizeByName( const std::string & name, size_t arraySize );
	void initializeLexeme( const std::string & name );
	const std::string & name( uint rowNum, uint posInRow ) const;

	std::pair<int, int> find( const std::string & name ) const;

	bool initialized( const std::string & name );

	size_t notNullSize() const;

	void printTable() const;

private:
	const size_t	_TABLE_SIZE;
	std::vector<vl>	_table;

	void addByHash( const Lexeme & lexeme, size_t hash );

	size_t getHash( const std::string & name ) const;
};
