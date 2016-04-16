#pragma once

#include "Token.h"

#include "Tables/ChangeableTable.h"
#include "Tables/PermamentTable.h"

#define theTableStorage TableStorage::getInstance()

class TableStorage
{
public:
	static TableStorage & getInstance();

	int findLexemByName( const std::string & lexem )				const;
	int findSeparatorByName( const std::string & sep )				const;
	int findKeyWordByName( const std::string & keyWord )			const;
	int findOperationByName( const std::string & op )				const;

	const std::string & findLexemByToken( const Token & token )		const;
	const std::string & findSeparatorByToken( const Token & token ) const;
	const std::string & findKeyWordByToken( const Token & token )	const;
	const std::string & findOperationByToken( const Token & token ) const;

protected:
	TableStorage();

private:
	void loadPermamentTables();

	static TableStorage * _storage;

	PermamentTable * _keyWords;
	PermamentTable * _separators;
	PermamentTable * _operations;
};

