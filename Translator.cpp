#include "Translator.h"

#include "LexicalAnalyzer.h"

Translator::Translator()
{
	createAnalyzers();
}

void Translator::loadProgram( const std::string & path )
{
	_programPath = path;
}

void Translator::analyzeLexical()
{
	_lexicalAnalyzer->analyze( _programPath );
}

void Translator::createAnalyzers()
{
	_lexicalAnalyzer = new LexicalAnalyzer;
}
