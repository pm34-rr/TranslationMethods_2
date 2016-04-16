#include "ChangeableTable.h"

using namespace std;

ChangeableTable::ChangeableTable( size_t size ):
	_TABLE_SIZE( size )
{
	_table.resize( _TABLE_SIZE );
}

ChangeableTable::ChangeableTable():
	ChangeableTable( 100 )
{

}

void ChangeableTable::add( const string & name, Type type , bool isArray, size_t arraySize )
{
	if ( find( name ).second != -1 )
		return;

	Lexeme lexeme( name, type, isArray, arraySize );
	size_t hash = getHash( name );
	addByHash( lexeme, hash );
}

void ChangeableTable::initializeLexeme( const string & name )
{
	pair<int,int> placeToInitialize = find( name );
	if ( placeToInitialize.first != -1 ) {
		if ( placeToInitialize.second != -1 )
			_table[placeToInitialize.first][placeToInitialize.second].setInitialized();
	}
	else
		throw 1;
}

pair<int, int> ChangeableTable::find( const string & name ) const
{
	// pos in table, pos in chain
	pair<int, int> result;
	size_t hash = getHash( name );
	if ( _table[hash].size() > 0 ) {
		result.first = hash;
		for ( size_t i = 0, n = _table.at( hash ).size(); i < n; ++i ) {
			if ( _table.at( hash )[i].name() == name ) {
				result.second = i;
				return result;
			}
		}
		result.second = -1;
	}
	else {
		result.first	= -1;
		result.second	= -1;
	}

	return result;
}

bool ChangeableTable::initialized( const string & name )
{
	size_t hash = getHash( name );
	for ( auto lexeme : _table[hash] ) {
		if ( lexeme.name() == name ) {
			if ( lexeme.isArray() )
				return lexeme.isArrayInitialized();
			else
				return lexeme.initialized();
		}
	}

	throw 1;
}

size_t ChangeableTable::notNullSize() const
{
	size_t size = 0;
	for ( size_t i = 0; i < _TABLE_SIZE; ++i )
		size += _table.at( i ).size();

	return size;
}

void ChangeableTable::addByHash( const Lexeme & lexeme, size_t hash )
{
	_table[hash].push_back( lexeme );
}

size_t ChangeableTable::getHash( const string & name ) const
{
	size_t h = 0;
	for ( auto c : name )
		h += c;

	h %= _TABLE_SIZE;

	return h;
}
