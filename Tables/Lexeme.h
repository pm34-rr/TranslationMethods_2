#pragma once

#include <string>
#include <vector>

enum Type {
	INT,
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

	void setInitialized( size_t num = 0 );
	bool initialized(	 size_t num = 0 )	const;
	bool isArrayInitialized()				const;

private:
	std::string			_name;
	Type				_type;
	bool				_isArray;
	std::vector<char>	_initialize;

	bool isIndexCorrect( size_t num ) const;
};
