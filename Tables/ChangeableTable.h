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
	void initializeLexeme( const std::string & name );

	std::pair<int, int> find( const std::string & name ) const;

	bool initialized( const std::string & name );

	size_t notNullSize() const;

private:
	const size_t	_TABLE_SIZE;
	std::vector<vl>	_table;

	void addByHash( const Lexeme & lexeme, size_t hash );

	size_t getHash( const std::string & name ) const;
};
