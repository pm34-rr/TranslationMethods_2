#pragma once

#include "Token.h"

#define theTableStorage TableStorage::getInstance()

class PermamentTable;
class ChangeableTable;

class TableStorage
{
public:
	static TableStorage & getInstance();

	PermamentTable * getKeyWordsTable()			const;
	PermamentTable * getSeparatorsTable()		const;
	PermamentTable * getOperationsTable()		const;

	ChangeableTable * getIdentificatorsTable()	const;
	ChangeableTable * getConstsTable()			const;

	std::pair<int,int> findLexemByName( const std::string & lexem )	const;
	std::pair<int,int> findConstByName( const std::string & name )	const;
	int findSeparatorByName( const std::string & sep )				const;
	int findKeyWordByName( const std::string & keyWord )			const;
	int findOperationByName( const std::string & op )				const;

	const std::string & findLexemByToken( const Token & token )		const;
	const std::string & findSeparatorByToken( const Token & token ) const;
	const std::string & findKeyWordByToken( const Token & token )	const;
	const std::string & findOperationByToken( const Token & token ) const;
	const std::string & findConstByToken( const Token & token )		const;

	void printIdentificatorTable() const;
	void printConstTable() const;

protected:
	TableStorage();

private:
	void loadPermamentTables();

	static TableStorage * _storage;

	PermamentTable * _keyWords;
	PermamentTable * _separators;
	PermamentTable * _operations;

	ChangeableTable * _ids;
	ChangeableTable * _consts;
};

