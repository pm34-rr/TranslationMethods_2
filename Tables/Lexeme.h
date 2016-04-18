#pragma once

#include <string>
#include <vector>

enum Type {
	UNDEFINED = -1,
	INT = 0,
	FLOAT
};

class Lexeme
{
public:
	Lexeme( const std::string & name, Type type, bool isArray = false, size_t arrSize = 1 );

	const std::string & name()		const;
	Type				type()		const;
	bool				isArray()	const;
	size_t				arraySize() const;

	void setType( Type t );
	void setArray();
	void setArraySize( size_t size );
	void setInitialized( size_t num = 0 );
	bool initialized(  size_t num = 0 )	const;
	bool isArrayInitialized()			const;

private:
	std::vector<char>	_initialize;
	std::string			_name;
	Type				_type;
	bool				_isArray;

	bool isIndexCorrect( size_t num ) const;
};
