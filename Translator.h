#pragma once

class LexicalAnalyzer;

class Translator
{
public:
	Translator();

	void analyzeLexical();

private:
	void createAnalyzers();

	LexicalAnalyzer * _lexicalAnalyzer;
};

