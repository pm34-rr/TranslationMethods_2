#include "PermamentTable.h"

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

int PermamentTable::find( const string & elem ) const
{
	auto it = std::find( _table.begin(), _table.end(), elem );
	if ( it == _table.end() )
		return -1;

	return _table.end() - it;
}

size_t PermamentTable::size() const
{
	return _table.size();
}
