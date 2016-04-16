#include "PermamentTable.h"

#include <fstream>
#include <algorithm>

using namespace std;

PermamentTable::PermamentTable()
{

}

void PermamentTable::add( const string & elem )
{
	if ( find( elem ) != -1 )
		return;

	_table.push_back( elem );
}

void PermamentTable::finalize()
{
	sort( _table.begin(), _table.end() );
}

void PermamentTable::loadFromFile( const string & path )
{
	ifstream input( path.c_str() );
	string currentElem;
	while ( input >> currentElem )
		add( currentElem );

	finalize();
}

int PermamentTable::find( const string & elem ) const
{
	auto it = std::find( _table.begin(), _table.end(), elem );
	if ( it == _table.end() )
		return -1;

	return it - _table.begin();
}

size_t PermamentTable::size() const
{
	return _table.size();
}
