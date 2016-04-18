#pragma once

#include <string>

class LexicalAnalyzer;

class Translator
{
public:
	Translator();

	void loadProgram( const std::string & path );

	void analyzeLexical();

private:
	void createAnalyzers();

	LexicalAnalyzer * _lexicalAnalyzer;
	std::string _programPath;
};

