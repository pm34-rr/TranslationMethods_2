#include "TableStorage.h"

#include "Tables/ChangeableTable.h"
#include "Tables/PermamentTable.h"

TableStorage * TableStorage::_storage = nullptr;

using namespace std;

TableStorage & TableStorage::getInstance()
{
	if ( _storage == nullptr )
		_storage = new TableStorage;

	return *_storage;
}

PermamentTable * TableStorage::getKeyWordsTable() const
{
	return _keyWords;
}

PermamentTable * TableStorage::getSeparatorsTable() const
{
	return _separators;
}

PermamentTable * TableStorage::getOperationsTable() const
{
	return _operations;
}

ChangeableTable * TableStorage::getIdentificatorsTable() const
{
	return _ids;
}

ChangeableTable * TableStorage::getConstsTable() const
{
	return _consts;
}

std::pair<int, int> TableStorage::findLexemByName( const string & lexem ) const
{
	return _ids->find( lexem );
}

std::pair<int,int> TableStorage::findConstByName( const string & name ) const
{
	return _consts->find( name );
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
	return _ids->name( token.rowNumber, token.posInRow );
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

const string & TableStorage::findConstByToken( const Token & token ) const
{
	return _consts->name( token.rowNumber, token.posInRow );
}

void TableStorage::printIdentificatorTable() const
{
	_ids->printTable();
}

void TableStorage::printConstTable() const
{
	_consts->printTable();
}



TableStorage::TableStorage()
{
	loadPermamentTables();

	_ids	= new ChangeableTable;
	_consts = new ChangeableTable;
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
