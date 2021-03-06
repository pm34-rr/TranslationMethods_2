#pragma once

#include <vector>
#include <string>

class PermamentTable
{
public:
	PermamentTable();

	void add( const std::string & elem );
	void finalize();
	void loadFromFile( const std::string & path );
	const std::string & name( uint pos ) const;

	int  find( const std::string & elem ) const;

	size_t size() const;

private:
	std::vector<std::string> _table;
};
