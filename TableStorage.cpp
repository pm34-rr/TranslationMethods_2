#include "TableStorage.h"

TableStorage * TableStorage::_storage = nullptr;

using namespace std;

TableStorage & TableStorage::getInstance()
{
	if ( _storage == nullptr )
		_storage = new TableStorage;

	return *_storage;
}

int TableStorage::findLexemByName( const string & lexem ) const
{

}

int TableStorage::findSeparatorByName( const string & sep ) const
{
	return _separators->find( sep );
}

int TableStorage::findKeyWordByName( const string & keyWord ) const
{
	return _keyWords->find( keyWord );
}

int TableStorage::findOperationByName( const string & op ) const
{
	return _operations->find( op );
}

const string & TableStorage::findLexemByToken( const Token & token ) const
{

}

const string & TableStorage::findSeparatorByToken( const Token & token ) const
{
	return _separators->name( token.rowNumber );
}

const string & TableStorage::findKeyWordByToken( const Token & token ) const
{
	return _keyWords->name( token.rowNumber );
}

const string & TableStorage::findOperationByToken( const Token & token ) const
{
	return _operations->name( token.rowNumber );
}

TableStorage::TableStorage()
{
	loadPermamentTables();
}

void TableStorage::loadPermamentTables()
{
	_keyWords = new PermamentTable;
	_keyWords->loadFromFile( "keyWords.txt" );

	_separators = new PermamentTable;
	_separators->loadFromFile( "separators.txt" );

	_operations = new PermamentTable;
	_operations->loadFromFile( "operations.txt" );
}
