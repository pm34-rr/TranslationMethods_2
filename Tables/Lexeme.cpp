#include "Lexeme.h"

Lexeme::Lexeme( const std::string & name, Type type, bool isArray, size_t arrSize ):
	_name( name ),
	_type( type ),
	_isArray( isArray )
{
	if ( isArray && arrSize > 1 )
		throw 1;

	_initialize.resize( arrSize );
}

const std::string & Lexeme::name() const
{
	return _name;
}

Type Lexeme::type() const
{
	return _type;
}

bool Lexeme::isArray() const
{
	return _isArray;
}

size_t Lexeme::arraySize() const
{
	return _initialize.size();
}

void Lexeme::setInitialized( size_t num )
{
	if ( !isIndexCorrect( num ) )
		throw 1;

	_initialize[num] = 1;
}

bool Lexeme::initialized( size_t num ) const
{
	if ( !isIndexCorrect( num ) )
		throw 1;

	return _initialize[num];
}

bool Lexeme::isArrayInitialized() const
{
	if ( !isArray() )
		return initialized( 0 );

	for ( size_t i = 0, n = _initialize.size(); i < n; ++i ) {
		if ( !_initialize[i] )
			return false;
	}

	return true;
}

bool Lexeme::isIndexCorrect( size_t num ) const
{
	if ( _isArray && num > 0 )
		return false;

	if ( num > _initialize.size() )
		return false;

	return true;
}
